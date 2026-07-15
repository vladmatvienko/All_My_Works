#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>

#include "brick_game/snake/snake.h"

namespace {

void UseTempHighScoreFile() {
  std::remove("/tmp/brickgame_snake_test_score.dat");
  setenv("BRICKGAME_SNAKE_HIGHSCORE_FILE",
         "/tmp/brickgame_snake_test_score.dat", 1);
}

int CountCells(const GameInfo_t &info, int value) {
  int count = 0;
  for (int row = 0; row < SNAKE_FIELD_HEIGHT; ++row) {
    for (int col = 0; col < SNAKE_FIELD_WIDTH; ++col) {
      if (info.field[row][col] == value) {
        ++count;
      }
    }
  }
  return count;
}

}  // namespace

TEST(SnakeApi, StartCreatesSnakeAndApple) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  snakeSetSeedForTesting(1U);

  snakeUserInput(Start, false);
  GameInfo_t info = snakeUpdateCurrentState();

  ASSERT_NE(info.field, nullptr);
  ASSERT_NE(info.next, nullptr);
  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.pause, 0);
  EXPECT_EQ(snakeGetStateForTesting(), 2);
  EXPECT_EQ(snakeGetLengthForTesting(), 4);
  EXPECT_EQ(CountCells(info, 1), 4);
  EXPECT_EQ(CountCells(info, 2), 1);
}

TEST(SnakeApi, TimerMovesSnakeForward) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  snakeUserInput(Start, false);
  int initial_col = snakeGetHeadColForTesting();

  snakeForceTickForTesting();
  snakeUpdateCurrentState();

  EXPECT_EQ(snakeGetHeadColForTesting(), initial_col + 1);
}

TEST(SnakeApi, LeftAndRightAreRelativeTurns) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  snakeUserInput(Start, false);
  int initial_row = snakeGetHeadRowForTesting();

  snakeUserInput(Left, false);
  snakeForceTickForTesting();
  snakeUpdateCurrentState();

  EXPECT_EQ(snakeGetHeadRowForTesting(), initial_row - 1);

  snakeUserInput(Right, false);
  snakeForceTickForTesting();
  snakeUpdateCurrentState();

  EXPECT_GT(snakeGetHeadColForTesting(), 0);
}

TEST(SnakeApi, EatingAppleAddsScoreAndLength) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  snakeUserInput(Start, false);
  int head_row = snakeGetHeadRowForTesting();
  int head_col = snakeGetHeadColForTesting();
  snakeSetAppleForTesting(head_row, head_col + 1);

  snakeForceTickForTesting();
  GameInfo_t info = snakeUpdateCurrentState();

  EXPECT_EQ(info.score, 1);
  EXPECT_EQ(info.high_score, 1);
  EXPECT_EQ(snakeGetLengthForTesting(), 5);
}

TEST(SnakeApi, LevelGrowsEveryFiveApples) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  snakeUserInput(Start, false);

  for (int i = 0; i < 5; ++i) {
    int rows[] = {10, 10, 10, 10};
    int cols[] = {5, 4, 3, 2};
    snakeSetSnakeForTesting(rows, cols, 4, 1);
    snakeSetAppleForTesting(10, 6);
    snakeForceTickForTesting();
    snakeUpdateCurrentState();
  }

  GameInfo_t info = snakeUpdateCurrentState();
  EXPECT_EQ(info.score, 5);
  EXPECT_EQ(info.level, 2);
  EXPECT_LT(info.speed, 600);
}

TEST(SnakeApi, WallCollisionFinishesGame) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  int rows[] = {0, 0, 0, 0};
  int cols[] = {9, 8, 7, 6};
  snakeSetSnakeForTesting(rows, cols, 4, 1);

  snakeForceTickForTesting();
  snakeUpdateCurrentState();

  EXPECT_EQ(snakeGetStateForTesting(), 5);
}

TEST(SnakeApi, SelfCollisionFinishesGame) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  int rows[] = {5, 5, 6, 6, 6, 5};
  int cols[] = {5, 4, 4, 5, 6, 6};
  snakeSetSnakeForTesting(rows, cols, 6, 2);

  snakeForceTickForTesting();
  snakeUpdateCurrentState();

  EXPECT_EQ(snakeGetStateForTesting(), 5);
}

TEST(SnakeApi, PauseStopsTimerMovement) {
  UseTempHighScoreFile();
  snakeResetForTesting();
  snakeUserInput(Start, false);
  int initial_col = snakeGetHeadColForTesting();

  snakeUserInput(Pause, false);
  snakeForceTickForTesting();
  GameInfo_t info = snakeUpdateCurrentState();

  EXPECT_EQ(info.pause, 1);
  EXPECT_EQ(snakeGetHeadColForTesting(), initial_col);
}
