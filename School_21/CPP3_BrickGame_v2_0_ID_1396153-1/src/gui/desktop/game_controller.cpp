#include "gui/desktop/game_controller.h"

#include "brick_game/snake/snake.h"
#include "brick_game/tetris/tetris.h"

void GameController::SetGame(DesktopGame game) { game_ = game; }

const char *GameController::Title() const {
  return game_ == DesktopGame::kTetris ? "BrickGame Tetris" : "BrickGame Snake";
}

void GameController::UserInput(UserAction_t action, bool hold) {
  if (game_ == DesktopGame::kTetris) {
    tetrisUserInput(action, hold);
  } else {
    snakeUserInput(action, hold);
  }
}

GameInfo_t GameController::UpdateCurrentState() const {
  if (game_ == DesktopGame::kTetris) {
    return tetrisUpdateCurrentState();
  }
  return snakeUpdateCurrentState();
}
