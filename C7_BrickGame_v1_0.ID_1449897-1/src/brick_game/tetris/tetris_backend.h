#ifndef SRC_BRICK_GAME_TETRIS_TETRIS_BACKEND_H
#define SRC_BRICK_GAME_TETRIS_TETRIS_BACKEND_H

#include "tetris.h"

enum {
  TETRIS_TEST_PIECE_I = 0,
  TETRIS_TEST_PIECE_O,
  TETRIS_TEST_PIECE_T,
  TETRIS_TEST_PIECE_S,
  TETRIS_TEST_PIECE_Z,
  TETRIS_TEST_PIECE_J,
  TETRIS_TEST_PIECE_L
};

enum {
  TETRIS_TEST_STATE_START = 0,
  TETRIS_TEST_STATE_SPAWN,
  TETRIS_TEST_STATE_MOVING,
  TETRIS_TEST_STATE_SHIFTING,
  TETRIS_TEST_STATE_ATTACHING,
  TETRIS_TEST_STATE_GAME_OVER
};

#ifdef S21_TETRIS_TEST
void tetrisResetForTesting(void);
void tetrisSetSeedForTesting(unsigned int seed);
void tetrisSetPieceForTesting(int piece, int rotation, int row, int col);
void tetrisFillRowForTesting(int row, int gap_col);
void tetrisAddScoreForTesting(int score);
void tetrisForceTickForTesting(void);
void tetrisLockCurrentPieceForTesting(void);
int tetrisGetStateForTesting(void);
int tetrisGetBoardCellForTesting(int row, int col);
#endif  // S21_TETRIS_TEST

#endif  // SRC_BRICK_GAME_TETRIS_TETRIS_BACKEND_H
