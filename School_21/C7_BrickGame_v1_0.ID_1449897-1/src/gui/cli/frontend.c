#include "gui/cli/frontend.h"

#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>

#define FIELD_ORIGIN_Y 1
#define FIELD_ORIGIN_X 2
#define CELL_WIDTH 2
#define PANEL_X 28
#define FRAME_WIDTH (TETRIS_FIELD_WIDTH * CELL_WIDTH + 2)
#define FRAME_HEIGHT (TETRIS_FIELD_HEIGHT + 2)
#define LOOP_DELAY_MS 50

static void initialize_screen(void);
static void shutdown_screen(void);
static bool read_action(UserAction_t *action);
static void draw_game(GameInfo_t info);
static void draw_field(GameInfo_t info);
static void draw_next(GameInfo_t info, int top, int left);
static void draw_panel(GameInfo_t info);
static void draw_help(int top, int left);
static void draw_game_message(GameInfo_t info);

int run_cli(void) {
  bool is_running = true;

  initialize_screen();
  while (is_running) {
    UserAction_t action = Up;
    bool has_action = read_action(&action);

    if (has_action) {
      userInput(action, false);
      if (action == Terminate) {
        is_running = false;
      }
    }
    draw_game(updateCurrentState());
    napms(LOOP_DELAY_MS);
  }
  shutdown_screen();

  return 0;
}

static void initialize_screen(void) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

static void shutdown_screen(void) { endwin(); }

static bool read_action(UserAction_t *action) {
  bool has_action = true;
  int key = getch();

  if (key == 's' || key == 'S' || key == '\n' || key == KEY_ENTER) {
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

static void draw_game(GameInfo_t info) {
  erase();
  draw_field(info);
  draw_panel(info);
  draw_game_message(info);
  refresh();
}

static void draw_field(GameInfo_t info) {
  int frame_y = FIELD_ORIGIN_Y - 1;
  int frame_x = FIELD_ORIGIN_X - 1;

  mvaddch(frame_y, frame_x, '+');
  mvaddch(frame_y, frame_x + FRAME_WIDTH - 1, '+');
  mvaddch(frame_y + FRAME_HEIGHT - 1, frame_x, '+');
  mvaddch(frame_y + FRAME_HEIGHT - 1, frame_x + FRAME_WIDTH - 1, '+');
  for (int col = 1; col < FRAME_WIDTH - 1; col++) {
    mvaddch(frame_y, frame_x + col, '-');
    mvaddch(frame_y + FRAME_HEIGHT - 1, frame_x + col, '-');
  }
  for (int row = 1; row < FRAME_HEIGHT - 1; row++) {
    mvaddch(frame_y + row, frame_x, '|');
    mvaddch(frame_y + row, frame_x + FRAME_WIDTH - 1, '|');
  }

  for (int row = 0; row < TETRIS_FIELD_HEIGHT; row++) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
      const char *cell = info.field[row][col] ? "[]" : "  ";
      mvprintw(FIELD_ORIGIN_Y + row, FIELD_ORIGIN_X + col * CELL_WIDTH, "%s",
               cell);
    }
  }
}

static void draw_next(GameInfo_t info, int top, int left) {
  for (int row = 0; row < TETRIS_NEXT_SIZE; row++) {
    for (int col = 0; col < TETRIS_NEXT_SIZE; col++) {
      const char *cell = info.next[row][col] ? "[]" : "  ";
      mvprintw(top + row, left + col * CELL_WIDTH, "%s", cell);
    }
  }
}

static void draw_panel(GameInfo_t info) {
  mvprintw(1, PANEL_X, "BrickGame Tetris");
  mvprintw(3, PANEL_X, "Score:      %d", info.score);
  mvprintw(4, PANEL_X, "High score: %d", info.high_score);
  mvprintw(5, PANEL_X, "Level:      %d", info.level);
  mvprintw(6, PANEL_X, "Speed:      %d ms", info.speed);
  mvprintw(8, PANEL_X, "Next:");
  draw_next(info, 9, PANEL_X);
  draw_help(15, PANEL_X);
}

static void draw_help(int top, int left) {
  mvprintw(top, left, "Controls:");
  mvprintw(top + 1, left, "S/Enter - start");
  mvprintw(top + 2, left, "P       - pause");
  mvprintw(top + 3, left, "Arrows  - move/drop");
  mvprintw(top + 4, left, "Space   - rotate");
  mvprintw(top + 5, left, "Q/Esc   - quit");
}

static void draw_game_message(GameInfo_t info) {
  if (info.pause) {
    mvprintw(FIELD_ORIGIN_Y + 9, FIELD_ORIGIN_X + 4, "PAUSE");
  }
  if (info.score == 0) {
    mvprintw(FIELD_ORIGIN_Y + 7, FIELD_ORIGIN_X + 2, "Press S");
    mvprintw(FIELD_ORIGIN_Y + 8, FIELD_ORIGIN_X + 2, "to start");
  }
}
