#if __has_include(<ncurses.h>)
#include "gui/cli/frontend.h"

#include <locale.h>
#include <ncurses.h>

#include <string>

#include "brick_game/snake/snake.h"
#include "brick_game/tetris/tetris.h"

namespace {

constexpr int kFieldOriginY = 1;
constexpr int kFieldOriginX = 2;
constexpr int kCellWidth = 2;
constexpr int kPanelX = 28;
constexpr int kFrameWidth = BRICK_GAME_FIELD_WIDTH * kCellWidth + 2;
constexpr int kFrameHeight = BRICK_GAME_FIELD_HEIGHT + 2;
constexpr int kLoopDelayMs = 50;

enum class ActiveGame { kTetris, kSnake };

void InitializeScreen();
void ShutdownScreen();
bool ReadAction(UserAction_t *action, ActiveGame *game);
void DispatchInput(ActiveGame game, UserAction_t action, bool hold);
GameInfo_t UpdateGame(ActiveGame game);
const char *GameTitle(ActiveGame game);
void DrawGame(GameInfo_t info, ActiveGame game);
void DrawField(GameInfo_t info);
void DrawNext(GameInfo_t info, int top, int left);
void DrawPanel(GameInfo_t info, ActiveGame game);
void DrawHelp(int top, int left);
void DrawGameMessage(GameInfo_t info);

void InitializeScreen() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

void ShutdownScreen() { endwin(); }

bool ReadAction(UserAction_t *action, ActiveGame *game) {
  bool has_action = true;
  int key = getch();

  if (key == '1') {
    *game = ActiveGame::kTetris;
    has_action = false;
  } else if (key == '2') {
    *game = ActiveGame::kSnake;
    has_action = false;
  } else if (key == 's' || key == 'S' || key == '\n' || key == KEY_ENTER) {
    *action = Start;
  } else if (key == 'p' || key == 'P') {
    *action = Pause;
  } else if (key == 'q' || key == 'Q' || key == 27) {
    *action = Terminate;
  } else if (key == KEY_LEFT) {
    *action = Left;
  } else if (key == KEY_RIGHT) {
    *action = Right;
  } else if (key == KEY_DOWN) {
    *action = Down;
  } else if (key == KEY_UP) {
    *action = Up;
  } else if (key == ' ') {
    *action = Action;
  } else {
    has_action = false;
  }

  return has_action;
}

void DispatchInput(ActiveGame game, UserAction_t action, bool hold) {
  if (game == ActiveGame::kTetris) {
    tetrisUserInput(action, hold);
  } else {
    snakeUserInput(action, hold);
  }
}

GameInfo_t UpdateGame(ActiveGame game) {
  if (game == ActiveGame::kTetris) {
    return tetrisUpdateCurrentState();
  }
  return snakeUpdateCurrentState();
}

const char *GameTitle(ActiveGame game) {
  return game == ActiveGame::kTetris ? "BrickGame Tetris" : "BrickGame Snake";
}

void DrawGame(GameInfo_t info, ActiveGame game) {
  erase();
  DrawField(info);
  DrawPanel(info, game);
  DrawGameMessage(info);
  refresh();
}

void DrawField(GameInfo_t info) {
  int frame_y = kFieldOriginY - 1;
  int frame_x = kFieldOriginX - 1;

  mvaddch(frame_y, frame_x, '+');
  mvaddch(frame_y, frame_x + kFrameWidth - 1, '+');
  mvaddch(frame_y + kFrameHeight - 1, frame_x, '+');
  mvaddch(frame_y + kFrameHeight - 1, frame_x + kFrameWidth - 1, '+');
  for (int col = 1; col < kFrameWidth - 1; ++col) {
    mvaddch(frame_y, frame_x + col, '-');
    mvaddch(frame_y + kFrameHeight - 1, frame_x + col, '-');
  }
  for (int row = 1; row < kFrameHeight - 1; ++row) {
    mvaddch(frame_y + row, frame_x, '|');
    mvaddch(frame_y + row, frame_x + kFrameWidth - 1, '|');
  }

  for (int row = 0; row < BRICK_GAME_FIELD_HEIGHT; ++row) {
    for (int col = 0; col < BRICK_GAME_FIELD_WIDTH; ++col) {
      const char *cell = "  ";
      if (info.field[row][col] == 1) {
        cell = "[]";
      } else if (info.field[row][col] == 2) {
        cell = "()";
      }
      mvprintw(kFieldOriginY + row, kFieldOriginX + col * kCellWidth, "%s",
               cell);
    }
  }
}

void DrawNext(GameInfo_t info, int top, int left) {
  for (int row = 0; row < BRICK_GAME_NEXT_SIZE; ++row) {
    for (int col = 0; col < BRICK_GAME_NEXT_SIZE; ++col) {
      const char *cell = info.next[row][col] ? "[]" : "  ";
      mvprintw(top + row, left + col * kCellWidth, "%s", cell);
    }
  }
}

void DrawPanel(GameInfo_t info, ActiveGame game) {
  mvprintw(1, kPanelX, "%s", GameTitle(game));
  mvprintw(3, kPanelX, "Score:      %d", info.score);
  mvprintw(4, kPanelX, "High score: %d", info.high_score);
  mvprintw(5, kPanelX, "Level:      %d", info.level);
  mvprintw(6, kPanelX, "Speed:      %d ms", info.speed);
  if (game == ActiveGame::kTetris) {
    mvprintw(8, kPanelX, "Next:");
    DrawNext(info, 9, kPanelX);
  } else {
    mvprintw(8, kPanelX, "Apple:      ()");
  }
  DrawHelp(15, kPanelX);
}

void DrawHelp(int top, int left) {
  mvprintw(top, left, "Controls:");
  mvprintw(top + 1, left, "1/2     - Tetris/Snake");
  mvprintw(top + 2, left, "S/Enter - start");
  mvprintw(top + 3, left, "P       - pause");
  mvprintw(top + 4, left, "Arrows  - move/turn");
  mvprintw(top + 5, left, "Space   - action/speed");
  mvprintw(top + 6, left, "Q/Esc   - quit");
}

void DrawGameMessage(GameInfo_t info) {
  if (info.pause) {
    mvprintw(kFieldOriginY + 9, kFieldOriginX + 4, "PAUSE");
  }
}

}  // namespace

int run_cli() {
  bool is_running = true;
  ActiveGame game = ActiveGame::kTetris;

  InitializeScreen();
  while (is_running) {
    UserAction_t action = Up;
    bool has_action = ReadAction(&action, &game);

    if (has_action) {
      DispatchInput(game, action, false);
      if (action == Terminate) {
        is_running = false;
      }
    }
    DrawGame(UpdateGame(game), game);
    napms(kLoopDelayMs);
  }
  ShutdownScreen();

  return 0;
}

#else

#include <iostream>
#include <string>

#include "brick_game/snake/snake.h"
#include "brick_game/tetris/tetris.h"
#include "gui/cli/frontend.h"

namespace {

enum class ActiveGame { kTetris, kSnake };

void PrintField(const GameInfo_t &info) {
  for (int row = 0; row < BRICK_GAME_FIELD_HEIGHT; ++row) {
    for (int col = 0; col < BRICK_GAME_FIELD_WIDTH; ++col) {
      if (info.field[row][col] == 1) {
        std::cout << "[]";
      } else if (info.field[row][col] == 2) {
        std::cout << "()";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << '\n';
  }
}

void Dispatch(ActiveGame game, UserAction_t action) {
  if (game == ActiveGame::kTetris) {
    tetrisUserInput(action, false);
  } else {
    snakeUserInput(action, false);
  }
}

GameInfo_t Update(ActiveGame game) {
  if (game == ActiveGame::kTetris) {
    return tetrisUpdateCurrentState();
  }
  return snakeUpdateCurrentState();
}

}  // namespace

int run_cli() {
  ActiveGame game = ActiveGame::kTetris;
  bool running = true;
  std::cout << "Ncurses headers were not found, using simple fallback CLI.\n";
  std::cout << "Commands: 1 Tetris, 2 Snake, s start, p pause, a/d left/right, "
               "w/s up/down, space action, q quit.\n";
  while (running) {
    GameInfo_t info = Update(game);
    PrintField(info);
    std::cout << "Score: " << info.score << " High: " << info.high_score
              << " Level: " << info.level << " Speed: " << info.speed
              << " ms\n> ";
    std::string line;
    if (!std::getline(std::cin, line)) {
      break;
    }
    char key = line.empty() ? ' ' : line[0];
    if (key == '1') {
      game = ActiveGame::kTetris;
    } else if (key == '2') {
      game = ActiveGame::kSnake;
    } else if (key == 's' || key == 'S') {
      Dispatch(game, Start);
    } else if (key == 'p' || key == 'P') {
      Dispatch(game, Pause);
    } else if (key == 'a' || key == 'A') {
      Dispatch(game, Left);
    } else if (key == 'd' || key == 'D') {
      Dispatch(game, Right);
    } else if (key == 'w' || key == 'W') {
      Dispatch(game, Up);
    } else if (key == 'x' || key == 'X') {
      Dispatch(game, Down);
    } else if (key == ' ') {
      Dispatch(game, Action);
    } else if (key == 'q' || key == 'Q') {
      Dispatch(game, Terminate);
      running = false;
    }
  }
  return 0;
}

#endif  // __has_include(<ncurses.h>)
