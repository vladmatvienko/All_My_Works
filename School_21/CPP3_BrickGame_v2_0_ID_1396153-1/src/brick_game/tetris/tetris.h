#ifndef SRC_BRICK_GAME_TETRIS_TETRIS_H
#define SRC_BRICK_GAME_TETRIS_TETRIS_H

#include "brick_game/common/game_info.h"

#define TETRIS_FIELD_WIDTH BRICK_GAME_FIELD_WIDTH
#define TETRIS_FIELD_HEIGHT BRICK_GAME_FIELD_HEIGHT
#define TETRIS_NEXT_SIZE BRICK_GAME_NEXT_SIZE

#ifdef __cplusplus
extern "C" {
#endif

void tetrisUserInput(UserAction_t action, bool hold);
GameInfo_t tetrisUpdateCurrentState(void);

#ifndef S21_NO_COMPAT_API
void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState(void);
#endif  // S21_NO_COMPAT_API

#ifdef __cplusplus
}
#endif

#endif  // SRC_BRICK_GAME_TETRIS_TETRIS_H
