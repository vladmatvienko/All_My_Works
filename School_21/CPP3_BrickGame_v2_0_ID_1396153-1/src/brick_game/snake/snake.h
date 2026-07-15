#ifndef SRC_BRICK_GAME_SNAKE_SNAKE_H
#define SRC_BRICK_GAME_SNAKE_SNAKE_H

#include "brick_game/common/game_info.h"

#define SNAKE_FIELD_WIDTH BRICK_GAME_FIELD_WIDTH
#define SNAKE_FIELD_HEIGHT BRICK_GAME_FIELD_HEIGHT
#define SNAKE_NEXT_SIZE BRICK_GAME_NEXT_SIZE

#ifdef __cplusplus
extern "C" {
#endif

void snakeUserInput(UserAction_t action, bool hold);
GameInfo_t snakeUpdateCurrentState(void);

#ifndef S21_NO_COMPAT_API
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);
#endif  // S21_NO_COMPAT_API

#ifdef S21_SNAKE_TEST
void snakeResetForTesting(void);
void snakeSetSeedForTesting(unsigned int seed);
void snakeSetAppleForTesting(int row, int col);
void snakeForceTickForTesting(void);
void snakeSetSnakeForTesting(const int *rows, const int *cols, int length,
                             int direction);
int snakeGetStateForTesting(void);
int snakeGetLengthForTesting(void);
int snakeGetHeadRowForTesting(void);
int snakeGetHeadColForTesting(void);
#endif  // S21_SNAKE_TEST

#ifdef __cplusplus
}
#endif

#endif  // SRC_BRICK_GAME_SNAKE_SNAKE_H
