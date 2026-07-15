#ifndef SRC_BRICK_GAME_COMMON_GAME_INFO_H
#define SRC_BRICK_GAME_COMMON_GAME_INFO_H

#include <stdbool.h>

#define BRICK_GAME_FIELD_WIDTH 10
#define BRICK_GAME_FIELD_HEIGHT 20
#define BRICK_GAME_NEXT_SIZE 4

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif  // SRC_BRICK_GAME_COMMON_GAME_INFO_H
