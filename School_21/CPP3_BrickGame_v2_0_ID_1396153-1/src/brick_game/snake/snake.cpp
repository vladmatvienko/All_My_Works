#include "brick_game/snake/snake.h"

#include <deque>

#include "brick_game/snake/snake_controller.h"

namespace {

s21::SnakeController &GetController() {
  static s21::SnakeController controller;
  return controller;
}

#ifdef S21_SNAKE_TEST
s21::Direction DirectionFromInt(int direction) {
  s21::Direction result = s21::Direction::kRight;
  if (direction == 0) {
    result = s21::Direction::kUp;
  } else if (direction == 1) {
    result = s21::Direction::kRight;
  } else if (direction == 2) {
    result = s21::Direction::kDown;
  } else if (direction == 3) {
    result = s21::Direction::kLeft;
  }
  return result;
}
#endif  // S21_SNAKE_TEST

}  // namespace

extern "C" void snakeUserInput(UserAction_t action, bool hold) {
  GetController().UserInput(action, hold);
}

extern "C" GameInfo_t snakeUpdateCurrentState(void) {
  return GetController().UpdateCurrentState();
}

#ifndef S21_NO_COMPAT_API
extern "C" void userInput(UserAction_t action, bool hold) {
  snakeUserInput(action, hold);
}

extern "C" GameInfo_t updateCurrentState(void) {
  return snakeUpdateCurrentState();
}
#endif  // S21_NO_COMPAT_API

#ifdef S21_SNAKE_TEST
extern "C" void snakeResetForTesting(void) { GetController().model().Reset(); }

extern "C" void snakeSetSeedForTesting(unsigned int seed) {
  GetController().model().SetSeedForTesting(seed);
}

extern "C" void snakeSetAppleForTesting(int row, int col) {
  GetController().model().SetAppleForTesting(s21::Cell{row, col});
}

extern "C" void snakeForceTickForTesting(void) {
  GetController().model().ForceTickForTesting();
}

extern "C" void snakeSetSnakeForTesting(const int *rows, const int *cols,
                                        int length, int direction) {
  std::deque<s21::Cell> snake;
  for (int i = 0; i < length; ++i) {
    snake.push_back(s21::Cell{rows[i], cols[i]});
  }
  GetController().model().SetSnakeForTesting(snake,
                                             DirectionFromInt(direction));
}

extern "C" int snakeGetStateForTesting(void) {
  return static_cast<int>(GetController().model().state());
}

extern "C" int snakeGetLengthForTesting(void) {
  return GetController().model().length();
}

extern "C" int snakeGetHeadRowForTesting(void) {
  return GetController().model().head().row;
}

extern "C" int snakeGetHeadColForTesting(void) {
  return GetController().model().head().col;
}
#endif  // S21_SNAKE_TEST
