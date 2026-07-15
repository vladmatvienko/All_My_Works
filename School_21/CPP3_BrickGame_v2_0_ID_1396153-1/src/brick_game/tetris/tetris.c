#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tetris_backend.h"

#define TETRIS_PIECE_COUNT 7
#define TETRIS_ROTATION_COUNT 4
#define TETRIS_BASE_SPEED_MS 700
#define TETRIS_SPEED_STEP_MS 60
#define TETRIS_MIN_SPEED_MS 120
#define TETRIS_MAX_LEVEL 10
#define TETRIS_LEVEL_SCORE 600
#define TETRIS_HIGH_SCORE_FILE "tetris_high_score.dat"

typedef enum {
  kStateStart = TETRIS_TEST_STATE_START,
  kStateSpawn = TETRIS_TEST_STATE_SPAWN,
  kStateMoving = TETRIS_TEST_STATE_MOVING,
  kStateShifting = TETRIS_TEST_STATE_SHIFTING,
  kStateAttaching = TETRIS_TEST_STATE_ATTACHING,
  kStateGameOver = TETRIS_TEST_STATE_GAME_OVER
} TetrisState_t;

typedef struct {
  int id;
  int rotation;
  int row;
  int col;
} Piece_t;

typedef struct {
  bool is_initialized;
  GameInfo_t info;
  int field_storage[TETRIS_FIELD_HEIGHT][TETRIS_FIELD_WIDTH];
  int *field_rows[TETRIS_FIELD_HEIGHT];
  int next_storage[TETRIS_NEXT_SIZE][TETRIS_NEXT_SIZE];
  int *next_rows[TETRIS_NEXT_SIZE];
  int board[TETRIS_FIELD_HEIGHT][TETRIS_FIELD_WIDTH];
  Piece_t current_piece;
  int next_piece;
  TetrisState_t state;
  uint32_t rng;
  long long last_tick_ms;
} TetrisGame_t;

static TetrisGame_t *get_game(void);
static void initialize_game(TetrisGame_t *game);
static void prepare_matrix_links(TetrisGame_t *game);
static void reset_session(TetrisGame_t *game);
static void clear_board(TetrisGame_t *game);
static const char *get_piece_shape(int piece, int rotation);
static bool piece_cell_is_filled(int piece, int rotation, int row, int col);
static bool can_place_piece(const TetrisGame_t *game, const Piece_t *piece);
static bool can_place_at(const TetrisGame_t *game, const Piece_t *piece,
                         int row, int col, int rotation);
static void render_state(TetrisGame_t *game);
static void render_field(TetrisGame_t *game);
static void render_next_piece(TetrisGame_t *game);
static void process_pending_state(TetrisGame_t *game);
static void process_spawn_state(TetrisGame_t *game);
static void process_shift_state(TetrisGame_t *game);
static void process_attach_state(TetrisGame_t *game);
static bool attach_piece_to_board(TetrisGame_t *game);
static int clear_completed_lines(TetrisGame_t *game);
static bool row_is_full(const TetrisGame_t *game, int row);
static void remove_row(TetrisGame_t *game, int row);
static int score_for_lines(int lines);
static void add_score(TetrisGame_t *game, int points);
static int calculate_level(int score);
static int calculate_speed(int level);
static void save_high_score(const TetrisGame_t *game);
static void load_high_score(TetrisGame_t *game);
static const char *get_high_score_path(void);
static long long current_time_ms(void);
static bool timer_expired(const TetrisGame_t *game);
static void touch_timer(TetrisGame_t *game);
static int random_piece(TetrisGame_t *game);
static void move_piece(TetrisGame_t *game, int delta_row, int delta_col);
static void rotate_piece(TetrisGame_t *game);
static void hard_drop_piece(TetrisGame_t *game);
static void terminate_game(TetrisGame_t *game);

void tetrisUserInput(UserAction_t action, bool hold) {
  TetrisGame_t *game = get_game();
  initialize_game(game);
  (void)hold;

  if (action == Start) {
    reset_session(game);
    process_pending_state(game);
  } else if (action == Terminate) {
    terminate_game(game);
  } else if (action == Pause) {
    if (game->state != kStateStart && game->state != kStateGameOver) {
      game->info.pause = !game->info.pause;
      touch_timer(game);
    }
  } else if (game->state == kStateMoving && !game->info.pause) {
    if (action == Left) {
      move_piece(game, 0, -1);
    } else if (action == Right) {
      move_piece(game, 0, 1);
    } else if (action == Down) {
      hard_drop_piece(game);
      process_pending_state(game);
    } else if (action == Action) {
      rotate_piece(game);
    }
  }

  render_state(game);
}

GameInfo_t tetrisUpdateCurrentState(void) {
  TetrisGame_t *game = get_game();
  initialize_game(game);

  if (!game->info.pause && game->state == kStateMoving && timer_expired(game)) {
    game->state = kStateShifting;
  }

  if (!game->info.pause) {
    process_pending_state(game);
  }

  render_state(game);
  return game->info;
}

#ifndef S21_NO_COMPAT_API
// cppcheck-suppress unusedFunction
void userInput(UserAction_t action, bool hold) {
  tetrisUserInput(action, hold);
}

// cppcheck-suppress unusedFunction
GameInfo_t updateCurrentState(void) { return tetrisUpdateCurrentState(); }
#endif  // S21_NO_COMPAT_API

static TetrisGame_t *get_game(void) {
  static TetrisGame_t game;
  return &game;
}

static void initialize_game(TetrisGame_t *game) {
  if (!game->is_initialized) {
    memset(game, 0, sizeof(*game));
    prepare_matrix_links(game);
    game->state = kStateStart;
    game->info.level = 1;
    game->info.speed = calculate_speed(game->info.level);
    game->rng = (uint32_t)current_time_ms();
    if (game->rng == 0U) {
      game->rng = 1U;
    }
    load_high_score(game);
    game->next_piece = random_piece(game);
    game->is_initialized = true;
    render_state(game);
  }
}

static void prepare_matrix_links(TetrisGame_t *game) {
  for (int row = 0; row < TETRIS_FIELD_HEIGHT; row++) {
    game->field_rows[row] = game->field_storage[row];
  }
  for (int row = 0; row < TETRIS_NEXT_SIZE; row++) {
    game->next_rows[row] = game->next_storage[row];
  }
  game->info.field = game->field_rows;
  game->info.next = game->next_rows;
}

static void reset_session(TetrisGame_t *game) {
  clear_board(game);
  game->info.score = 0;
  game->info.level = 1;
  game->info.speed = calculate_speed(game->info.level);
  game->info.pause = 0;
  load_high_score(game);
  game->next_piece = random_piece(game);
  game->state = kStateSpawn;
  touch_timer(game);
}

static void clear_board(TetrisGame_t *game) {
  for (int row = 0; row < TETRIS_FIELD_HEIGHT; row++) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
      game->board[row][col] = 0;
    }
  }
}

static const char *get_piece_shape(int piece, int rotation) {
  static const char *const shapes[TETRIS_PIECE_COUNT][TETRIS_ROTATION_COUNT] = {
      {"0000111100000000", "0010001000100010", "0000111100000000",
       "0010001000100010"},
      {"0110011000000000", "0110011000000000", "0110011000000000",
       "0110011000000000"},
      {"0100111000000000", "0100011001000000", "0000111001000000",
       "0100110001000000"},
      {"0110110000000000", "0100011000100000", "0110110000000000",
       "0100011000100000"},
      {"1100011000000000", "0010011001000000", "1100011000000000",
       "0010011001000000"},
      {"1000111000000000", "0110010001000000", "0000111000100000",
       "0100010011000000"},
      {"0010111000000000", "0100010001100000", "0000111010000000",
       "1100010001000000"}};
  int safe_piece = piece;
  int safe_rotation = rotation % TETRIS_ROTATION_COUNT;

  if (safe_piece < 0 || safe_piece >= TETRIS_PIECE_COUNT) {
    safe_piece = 0;
  }
  if (safe_rotation < 0) {
    safe_rotation += TETRIS_ROTATION_COUNT;
  }
  return shapes[safe_piece][safe_rotation];
}

static bool piece_cell_is_filled(int piece, int rotation, int row, int col) {
  const char *shape = get_piece_shape(piece, rotation);
  return shape[row * TETRIS_NEXT_SIZE + col] == '1';
}

static bool can_place_piece(const TetrisGame_t *game, const Piece_t *piece) {
  return can_place_at(game, piece, piece->row, piece->col, piece->rotation);
}

static bool can_place_at(const TetrisGame_t *game, const Piece_t *piece,
                         int row, int col, int rotation) {
  bool can_place = true;

  for (int shape_row = 0; shape_row < TETRIS_NEXT_SIZE; shape_row++) {
    for (int shape_col = 0; shape_col < TETRIS_NEXT_SIZE; shape_col++) {
      if (piece_cell_is_filled(piece->id, rotation, shape_row, shape_col)) {
        int board_row = row + shape_row;
        int board_col = col + shape_col;
        bool outside_horizontal =
            board_col < 0 || board_col >= TETRIS_FIELD_WIDTH;
        bool outside_bottom = board_row >= TETRIS_FIELD_HEIGHT;
        bool occupied = false;

        if (!outside_horizontal && board_row >= 0 && !outside_bottom) {
          occupied = game->board[board_row][board_col] != 0;
        }
        if (outside_horizontal || outside_bottom || occupied) {
          can_place = false;
        }
      }
    }
  }

  return can_place;
}

static void render_state(TetrisGame_t *game) {
  render_field(game);
  render_next_piece(game);
}

static void render_field(TetrisGame_t *game) {
  for (int row = 0; row < TETRIS_FIELD_HEIGHT; row++) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
      game->field_storage[row][col] = game->board[row][col];
    }
  }

  if (game->state == kStateMoving || game->state == kStateShifting ||
      game->state == kStateAttaching) {
    Piece_t piece = game->current_piece;
    for (int shape_row = 0; shape_row < TETRIS_NEXT_SIZE; shape_row++) {
      for (int shape_col = 0; shape_col < TETRIS_NEXT_SIZE; shape_col++) {
        if (piece_cell_is_filled(piece.id, piece.rotation, shape_row,
                                 shape_col)) {
          int board_row = piece.row + shape_row;
          int board_col = piece.col + shape_col;
          bool visible = board_row >= 0 && board_row < TETRIS_FIELD_HEIGHT &&
                         board_col >= 0 && board_col < TETRIS_FIELD_WIDTH;
          if (visible) {
            game->field_storage[board_row][board_col] = 1;
          }
        }
      }
    }
  }
}

static void render_next_piece(TetrisGame_t *game) {
  for (int row = 0; row < TETRIS_NEXT_SIZE; row++) {
    for (int col = 0; col < TETRIS_NEXT_SIZE; col++) {
      game->next_storage[row][col] = 0;
      if (game->state != kStateStart) {
        game->next_storage[row][col] =
            piece_cell_is_filled(game->next_piece, 0, row, col) ? 1 : 0;
      }
    }
  }
}

static void process_pending_state(TetrisGame_t *game) {
  int guard = 0;

  while (guard < 4 && game->state != kStateStart &&
         game->state != kStateMoving && game->state != kStateGameOver) {
    if (game->state == kStateSpawn) {
      process_spawn_state(game);
    } else if (game->state == kStateShifting) {
      process_shift_state(game);
    } else if (game->state == kStateAttaching) {
      process_attach_state(game);
    }
    guard++;
  }
}

static void process_spawn_state(TetrisGame_t *game) {
  game->current_piece.id = game->next_piece;
  game->current_piece.rotation = 0;
  game->current_piece.row = -1;
  game->current_piece.col = (TETRIS_FIELD_WIDTH - TETRIS_NEXT_SIZE) / 2;
  game->next_piece = random_piece(game);

  if (can_place_piece(game, &game->current_piece)) {
    game->state = kStateMoving;
    touch_timer(game);
  } else {
    terminate_game(game);
  }
}

static void process_shift_state(TetrisGame_t *game) {
  if (can_place_at(game, &game->current_piece, game->current_piece.row + 1,
                   game->current_piece.col, game->current_piece.rotation)) {
    game->current_piece.row++;
    game->state = kStateMoving;
    touch_timer(game);
  } else {
    game->state = kStateAttaching;
  }
}

static void process_attach_state(TetrisGame_t *game) {
  bool top_touched = attach_piece_to_board(game);
  int cleared_lines = clear_completed_lines(game);

  add_score(game, score_for_lines(cleared_lines));
  if (top_touched) {
    terminate_game(game);
  } else {
    game->state = kStateSpawn;
  }
}

static bool attach_piece_to_board(TetrisGame_t *game) {
  bool top_touched = false;
  Piece_t piece = game->current_piece;

  for (int shape_row = 0; shape_row < TETRIS_NEXT_SIZE; shape_row++) {
    for (int shape_col = 0; shape_col < TETRIS_NEXT_SIZE; shape_col++) {
      if (piece_cell_is_filled(piece.id, piece.rotation, shape_row,
                               shape_col)) {
        int board_row = piece.row + shape_row;
        int board_col = piece.col + shape_col;
        bool inside_board = board_row >= 0 && board_row < TETRIS_FIELD_HEIGHT &&
                            board_col >= 0 && board_col < TETRIS_FIELD_WIDTH;

        if (board_row <= 0) {
          top_touched = true;
        }
        if (inside_board) {
          game->board[board_row][board_col] = 1;
        }
      }
    }
  }

  return top_touched;
}

static int clear_completed_lines(TetrisGame_t *game) {
  int lines = 0;
  int row = TETRIS_FIELD_HEIGHT - 1;

  while (row >= 0) {
    if (row_is_full(game, row)) {
      remove_row(game, row);
      lines++;
    } else {
      row--;
    }
  }

  return lines;
}

static bool row_is_full(const TetrisGame_t *game, int row) {
  bool is_full = true;

  for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
    if (game->board[row][col] == 0) {
      is_full = false;
    }
  }

  return is_full;
}

static void remove_row(TetrisGame_t *game, int row) {
  for (int current = row; current > 0; current--) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
      game->board[current][col] = game->board[current - 1][col];
    }
  }
  for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
    game->board[0][col] = 0;
  }
}

static int score_for_lines(int lines) {
  int score = 0;

  if (lines == 1) {
    score = 100;
  } else if (lines == 2) {
    score = 300;
  } else if (lines == 3) {
    score = 700;
  } else if (lines >= 4) {
    score = 1500;
  }

  return score;
}

static void add_score(TetrisGame_t *game, int points) {
  if (points > 0) {
    game->info.score += points;
    game->info.level = calculate_level(game->info.score);
    game->info.speed = calculate_speed(game->info.level);
    if (game->info.score > game->info.high_score) {
      game->info.high_score = game->info.score;
      save_high_score(game);
    }
  }
}

static int calculate_level(int score) {
  int level = score / TETRIS_LEVEL_SCORE + 1;

  if (level > TETRIS_MAX_LEVEL) {
    level = TETRIS_MAX_LEVEL;
  }

  return level;
}

static int calculate_speed(int level) {
  int speed = TETRIS_BASE_SPEED_MS - (level - 1) * TETRIS_SPEED_STEP_MS;

  if (speed < TETRIS_MIN_SPEED_MS) {
    speed = TETRIS_MIN_SPEED_MS;
  }

  return speed;
}

static void save_high_score(const TetrisGame_t *game) {
  FILE *file = fopen(get_high_score_path(), "w");

  if (file != NULL) {
    fprintf(file, "%d\n", game->info.high_score);
    fclose(file);
  }
}

static void load_high_score(TetrisGame_t *game) {
  FILE *file = fopen(get_high_score_path(), "r");
  int loaded_score = 0;

  if (file != NULL) {
    if (fscanf(file, "%d", &loaded_score) != 1 || loaded_score < 0) {
      loaded_score = 0;
    }
    fclose(file);
  }
  game->info.high_score = loaded_score;
}

static const char *get_high_score_path(void) {
  const char *path = getenv("BRICKGAME_HIGHSCORE_FILE");

  if (path == NULL || path[0] == '\0') {
    path = TETRIS_HIGH_SCORE_FILE;
  }

  return path;
}

static long long current_time_ms(void) {
  struct timespec current_time;

  timespec_get(&current_time, TIME_UTC);
  return (long long)current_time.tv_sec * 1000LL +
         (long long)current_time.tv_nsec / 1000000LL;
}

static bool timer_expired(const TetrisGame_t *game) {
  long long elapsed = current_time_ms() - game->last_tick_ms;
  return elapsed >= game->info.speed;
}

static void touch_timer(TetrisGame_t *game) {
  game->last_tick_ms = current_time_ms();
}

static int random_piece(TetrisGame_t *game) {
  game->rng = game->rng * 1103515245U + 12345U;
  return (int)((game->rng >> 16U) % TETRIS_PIECE_COUNT);
}

static void move_piece(TetrisGame_t *game, int delta_row, int delta_col) {
  int new_row = game->current_piece.row + delta_row;
  int new_col = game->current_piece.col + delta_col;

  if (can_place_at(game, &game->current_piece, new_row, new_col,
                   game->current_piece.rotation)) {
    game->current_piece.row = new_row;
    game->current_piece.col = new_col;
  }
}

static void rotate_piece(TetrisGame_t *game) {
  int next_rotation =
      (game->current_piece.rotation + 1) % TETRIS_ROTATION_COUNT;

  if (can_place_at(game, &game->current_piece, game->current_piece.row,
                   game->current_piece.col, next_rotation)) {
    game->current_piece.rotation = next_rotation;
  }
}

static void hard_drop_piece(TetrisGame_t *game) {
  while (can_place_at(game, &game->current_piece, game->current_piece.row + 1,
                      game->current_piece.col, game->current_piece.rotation)) {
    game->current_piece.row++;
  }
  game->state = kStateAttaching;
}

static void terminate_game(TetrisGame_t *game) {
  game->state = kStateGameOver;
  game->info.pause = 0;
  if (game->info.score > game->info.high_score) {
    game->info.high_score = game->info.score;
  }
  save_high_score(game);
}

#ifdef S21_TETRIS_TEST
void tetrisResetForTesting(void) {
  TetrisGame_t *game = get_game();

  memset(game, 0, sizeof(*game));
  initialize_game(game);
}

void tetrisSetSeedForTesting(unsigned int seed) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  game->rng = seed == 0U ? 1U : seed;
}

void tetrisSetPieceForTesting(int piece, int rotation, int row, int col) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  game->current_piece.id = piece;
  game->current_piece.rotation = rotation;
  game->current_piece.row = row;
  game->current_piece.col = col;
  game->state = kStateMoving;
  render_state(game);
}

void tetrisFillRowForTesting(int row, int gap_col) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  if (row >= 0 && row < TETRIS_FIELD_HEIGHT) {
    for (int col = 0; col < TETRIS_FIELD_WIDTH; col++) {
      game->board[row][col] = col == gap_col ? 0 : 1;
    }
  }
  render_state(game);
}

void tetrisAddScoreForTesting(int score) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  add_score(game, score);
}

void tetrisForceTickForTesting(void) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  game->last_tick_ms = 0;
}

void tetrisLockCurrentPieceForTesting(void) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  game->state = kStateAttaching;
  process_pending_state(game);
  render_state(game);
}

int tetrisGetStateForTesting(void) {
  TetrisGame_t *game = get_game();

  initialize_game(game);
  return game->state;
}

int tetrisGetBoardCellForTesting(int row, int col) {
  TetrisGame_t *game = get_game();
  int value = 0;

  initialize_game(game);
  if (row >= 0 && row < TETRIS_FIELD_HEIGHT && col >= 0 &&
      col < TETRIS_FIELD_WIDTH) {
    value = game->board[row][col];
  }

  return value;
}
#endif  // S21_TETRIS_TEST
