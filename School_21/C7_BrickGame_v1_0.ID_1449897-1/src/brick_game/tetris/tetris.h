#ifndef SRC_BRICK_GAME_TETRIS_TETRIS_H
#define SRC_BRICK_GAME_TETRIS_TETRIS_H

#include <stdbool.h>

#define TETRIS_FIELD_WIDTH 10
#define TETRIS_FIELD_HEIGHT 20
#define TETRIS_NEXT_SIZE 4

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

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);

#endif  // SRC_BRICK_GAME_TETRIS_TETRIS_H
