#ifndef GAME_H
#define GAME_H

typedef enum GameState
{
   GAME_STATE_PLAYING,
   GAME_STATE_START_MENU,
   GAME_STATE_PAUSE_MENU,
   GAME_STATE_SETTINGS_MENU,
   GAME_STATE_LOAD_MENU,
} GameState;

extern GameState currentGameState;
extern int gameShouldClose;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void CloseGame(void);

#endif // GAME_H