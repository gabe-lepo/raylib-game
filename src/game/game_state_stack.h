#ifndef GAME_STATE_STACK_H
#define GAME_STATE_STACK_H

#include <stddef.h>

#define MAX_GAME_STATE_STACK 16

typedef enum GameState
{
   GAME_STATE_INIT = -1,
   GAME_STATE_PLAYING,
   GAME_STATE_START_MENU,
   GAME_STATE_PAUSE_MENU,
   GAME_STATE_SETTINGS_MENU,
   GAME_STATE_LOAD_MENU,
} GameState;

typedef struct GameStateStack
{
   GameState states[MAX_GAME_STATE_STACK];
   size_t top;
} GameStateStack;

extern GameState gameState;

void InitGameStateStack(void);
int PushGameState(GameState state);
int PopGameState(void);
GameState PeekGameState(void);
int ClearGameStateStack(void);

#endif