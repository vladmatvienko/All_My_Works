#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>

#include "brick_game/tetris/tetris_backend.h"

namespace {

void UseTempHighScoreFile() {
  std::remove("/tmp/brickgame_tetris_test_score.dat");
  setenv("BRICKGAME_HIGHSCORE_FILE", "/tmp/brickgame_tetris_test_score.dat", 1);
}

int CountFieldCells(const GameInfo_t &info) {
  int cells = 0;
  for (int row = 0; row < TETRIS_FIELD_HEIGHT; ++row) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; ++col) {
      cells += info.field[row][col] != 0;
    }
  }
  return cells;
}

}  // namespace

TEST(TetrisApi, StartCreatesValidState) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisSetSeedForTesting(1U);

  tetrisUserInput(Start, false);
  GameInfo_t info = tetrisUpdateCurrentState();

  ASSERT_NE(info.field, nullptr);
  ASSERT_NE(info.next, nullptr);
  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.pause, 0);
  EXPECT_EQ(tetrisGetStateForTesting(), TETRIS_TEST_STATE_MOVING);
  EXPECT_GE(CountFieldCells(info), 1);
}

TEST(TetrisApi, PauseTogglesState) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);

  tetrisUserInput(Pause, false);
  EXPECT_EQ(tetrisUpdateCurrentState().pause, 1);
  tetrisUserInput(Pause, false);
  EXPECT_EQ(tetrisUpdateCurrentState().pause, 0);
}

TEST(TetrisApi, LeftAndRightMovePiece) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, 0, 4);

  tetrisUserInput(Left, false);
  GameInfo_t left_info = tetrisUpdateCurrentState();
  EXPECT_EQ(left_info.field[0][4], 1);
  EXPECT_EQ(left_info.field[0][6], 0);

  tetrisUserInput(Right, false);
  GameInfo_t right_info = tetrisUpdateCurrentState();
  EXPECT_EQ(right_info.field[0][5], 1);
  EXPECT_EQ(right_info.field[0][6], 1);
}

TEST(TetrisApi, RotationChangesTPiece) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_T, 0, 0, 3);

  tetrisUserInput(Action, false);
  GameInfo_t info = tetrisUpdateCurrentState();

  EXPECT_EQ(info.field[0][4], 1);
  EXPECT_EQ(info.field[1][4], 1);
  EXPECT_EQ(info.field[1][5], 1);
  EXPECT_EQ(info.field[2][4], 1);
}

TEST(TetrisApi, DownLocksPieceOnBottom) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, 0, 4);

  tetrisUserInput(Down, false);

  EXPECT_EQ(tetrisGetBoardCellForTesting(18, 5), 1);
  EXPECT_EQ(tetrisGetBoardCellForTesting(19, 6), 1);
  EXPECT_EQ(tetrisGetStateForTesting(), TETRIS_TEST_STATE_MOVING);
}

TEST(TetrisApi, ClearLineAddsScoreAndHighScore) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);
  tetrisFillRowForTesting(19, -1);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_I, 1, 14, 0);

  tetrisLockCurrentPieceForTesting();
  GameInfo_t info = tetrisUpdateCurrentState();

  EXPECT_EQ(info.score, 100);
  EXPECT_EQ(info.high_score, 100);
  EXPECT_EQ(tetrisGetBoardCellForTesting(19, 0), 0);
}

TEST(TetrisApi, LevelGrowsEvery600Points) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);

  tetrisAddScoreForTesting(600);
  GameInfo_t info = tetrisUpdateCurrentState();

  EXPECT_EQ(info.score, 600);
  EXPECT_EQ(info.level, 2);
  EXPECT_LT(info.speed, 700);
}

TEST(TetrisApi, GameOverWhenTopIsTouched) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, -1, 4);

  tetrisLockCurrentPieceForTesting();

  EXPECT_EQ(tetrisGetStateForTesting(), TETRIS_TEST_STATE_GAME_OVER);
}

TEST(TetrisApi, TickShiftsPieceDown) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, 0, 4);

  tetrisForceTickForTesting();
  GameInfo_t info = tetrisUpdateCurrentState();

  EXPECT_EQ(info.field[1][5], 1);
  EXPECT_EQ(info.field[2][5], 1);
}

TEST(TetrisApi, TerminateSwitchesToGameOver) {
  UseTempHighScoreFile();
  tetrisResetForTesting();
  tetrisUserInput(Start, false);

  tetrisUserInput(Terminate, false);

  EXPECT_EQ(tetrisGetStateForTesting(), TETRIS_TEST_STATE_GAME_OVER);
}
