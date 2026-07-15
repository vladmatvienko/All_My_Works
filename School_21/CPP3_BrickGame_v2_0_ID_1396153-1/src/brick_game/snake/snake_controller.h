#ifndef SRC_BRICK_GAME_SNAKE_SNAKE_CONTROLLER_H
#define SRC_BRICK_GAME_SNAKE_SNAKE_CONTROLLER_H

#include "brick_game/snake/snake_model.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController() = default;

  void UserInput(UserAction_t action, bool hold);
  GameInfo_t UpdateCurrentState();

  SnakeModel &model() { return model_; }
  const SnakeModel &model() const { return model_; }

 private:
  SnakeModel model_;
};

}  // namespace s21

#endif  // SRC_BRICK_GAME_SNAKE_SNAKE_CONTROLLER_H
