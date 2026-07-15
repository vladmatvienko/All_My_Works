#ifndef SRC_GUI_DESKTOP_GAME_CONTROLLER_H
#define SRC_GUI_DESKTOP_GAME_CONTROLLER_H

#include "brick_game/common/game_info.h"

enum class DesktopGame { kTetris, kSnake };

class GameController {
 public:
  void SetGame(DesktopGame game);
  DesktopGame game() const { return game_; }
  const char *Title() const;
  void UserInput(UserAction_t action, bool hold = false);
  GameInfo_t UpdateCurrentState() const;

 private:
  DesktopGame game_ = DesktopGame::kTetris;
};

#endif  // SRC_GUI_DESKTOP_GAME_CONTROLLER_H
