#define _POSIX_C_SOURCE 200809L
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "brick_game/tetris/tetris_backend.h"

static void use_temp_high_score_file(void) {
  remove("/tmp/brickgame_tetris_test_score.dat");
  setenv("BRICKGAME_HIGHSCORE_FILE", "/tmp/brickgame_tetris_test_score.dat", 1);
}

static int count_field_cells(GameInfo_t info) {
  int cells = 0;

  for (int row = 0; row < TETRIS_FIELD_HEIGHT; row++) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
      cells += info.field[row][col] != 0;
    }
  }

  return cells;
}

START_TEST(api_start_creates_valid_state) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  tetrisSetSeedForTesting(1U);

  userInput(Start, false);
  GameInfo_t info = updateCurrentState();

  ck_assert_ptr_nonnull(info.field);
  ck_assert_ptr_nonnull(info.next);
  ck_assert_int_eq(info.score, 0);
  ck_assert_int_eq(info.level, 1);
  ck_assert_int_eq(info.pause, 0);
  ck_assert_int_eq(tetrisGetStateForTesting(), TETRIS_TEST_STATE_MOVING);
  ck_assert_int_ge(count_field_cells(info), 1);
}
END_TEST

START_TEST(api_pause_toggles_state) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);

  userInput(Pause, false);
  ck_assert_int_eq(updateCurrentState().pause, 1);
  userInput(Pause, false);
  ck_assert_int_eq(updateCurrentState().pause, 0);
}
END_TEST

START_TEST(api_left_and_right_move_piece) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, 0, 4);

  userInput(Left, false);
  GameInfo_t left_info = updateCurrentState();
  ck_assert_int_eq(left_info.field[0][4], 1);
  ck_assert_int_eq(left_info.field[0][6], 0);

  userInput(Right, false);
  GameInfo_t right_info = updateCurrentState();
  ck_assert_int_eq(right_info.field[0][5], 1);
  ck_assert_int_eq(right_info.field[0][6], 1);
}
END_TEST

START_TEST(api_rotation_changes_t_piece) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_T, 0, 0, 3);

  userInput(Action, false);
  GameInfo_t info = updateCurrentState();

  ck_assert_int_eq(info.field[0][4], 1);
  ck_assert_int_eq(info.field[1][4], 1);
  ck_assert_int_eq(info.field[1][5], 1);
  ck_assert_int_eq(info.field[2][4], 1);
}
END_TEST

START_TEST(api_down_locks_piece_on_bottom) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, 0, 4);

  userInput(Down, false);

  ck_assert_int_eq(tetrisGetBoardCellForTesting(18, 5), 1);
  ck_assert_int_eq(tetrisGetBoardCellForTesting(19, 6), 1);
  ck_assert_int_eq(tetrisGetStateForTesting(), TETRIS_TEST_STATE_MOVING);
}
END_TEST

START_TEST(api_clear_line_adds_score_and_high_score) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);
  tetrisFillRowForTesting(19, -1);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_I, 1, 14, 0);

  tetrisLockCurrentPieceForTesting();
  GameInfo_t info = updateCurrentState();

  ck_assert_int_eq(info.score, 100);
  ck_assert_int_eq(info.high_score, 100);
  ck_assert_int_eq(tetrisGetBoardCellForTesting(19, 0), 0);
}
END_TEST

START_TEST(api_level_grows_every_600_points) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);

  tetrisAddScoreForTesting(600);
  GameInfo_t info = updateCurrentState();

  ck_assert_int_eq(info.score, 600);
  ck_assert_int_eq(info.level, 2);
  ck_assert_int_lt(info.speed, 700);
}
END_TEST

START_TEST(api_game_over_when_top_is_touched) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, -1, 4);

  tetrisLockCurrentPieceForTesting();

  ck_assert_int_eq(tetrisGetStateForTesting(), TETRIS_TEST_STATE_GAME_OVER);
}
END_TEST

START_TEST(api_tick_shifts_piece_down) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);
  tetrisSetPieceForTesting(TETRIS_TEST_PIECE_O, 0, 0, 4);

  tetrisForceTickForTesting();
  GameInfo_t info = updateCurrentState();

  ck_assert_int_eq(info.field[1][5], 1);
  ck_assert_int_eq(info.field[2][5], 1);
}
END_TEST

START_TEST(api_terminate_switches_to_game_over) {
  use_temp_high_score_file();
  tetrisResetForTesting();
  userInput(Start, false);

  userInput(Terminate, false);

  ck_assert_int_eq(tetrisGetStateForTesting(), TETRIS_TEST_STATE_GAME_OVER);
}
END_TEST

static Suite *tetris_suite(void) {
  Suite *suite = suite_create("BrickGame Tetris");
  TCase *core = tcase_create("Core");

  tcase_add_test(core, api_start_creates_valid_state);
  tcase_add_test(core, api_pause_toggles_state);
  tcase_add_test(core, api_left_and_right_move_piece);
  tcase_add_test(core, api_rotation_changes_t_piece);
  tcase_add_test(core, api_down_locks_piece_on_bottom);
  tcase_add_test(core, api_clear_line_adds_score_and_high_score);
  tcase_add_test(core, api_level_grows_every_600_points);
  tcase_add_test(core, api_game_over_when_top_is_touched);
  tcase_add_test(core, api_tick_shifts_piece_down);
  tcase_add_test(core, api_terminate_switches_to_game_over);
  suite_add_tcase(suite, core);

  return suite;
}

int main(void) {
  Suite *suite = tetris_suite();
  SRunner *runner = srunner_create(suite);
  int failed = 0;

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
