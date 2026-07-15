#include "brick_game/snake/snake_controller.h"

namespace s21 {

void SnakeController::UserInput(UserAction_t action, bool hold) {
  if (action == Start) {
    model_.Start();
  } else if (action == Pause) {
    model_.TogglePause();
  } else if (action == Terminate) {
    model_.Terminate();
  } else if (action == Left) {
    model_.TurnLeft();
  } else if (action == Right) {
    model_.TurnRight();
  } else if (action == Action) {
    model_.Accelerate(hold);
  }
}

GameInfo_t SnakeController::UpdateCurrentState() { return model_.Update(); }

}  // namespace s21
