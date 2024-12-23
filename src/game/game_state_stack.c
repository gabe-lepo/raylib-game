#include "game_state_stack.h"
#include "log.h"

#include <stdlib.h>

static GameStateStack stateStack;

const char *StateToString(GameState state)
{
   switch (state)
   {
   case GAME_STATE_INIT:
      return "GAME_STATE_INIT";
   case GAME_STATE_PLAYING:
      return "GAME_STATE_PLAYING";
   case GAME_STATE_START_MENU:
      return "GAME_STATE_START_MENU";
   case GAME_STATE_PAUSE_MENU:
      return "GAME_STATE_PAUSE_MENU";
   case GAME_STATE_SETTINGS_MENU:
      return "GAME_STATE_SETTINGS_MENU";
   case GAME_STATE_LOAD_MENU:
      return "GAME_STATE_LOAD_MENU";
   case GAME_STATE_CONFIRM_MENU:
      return "GAME_STATE_CONFIRM_MENU";
   default:
      return "UNKNOWN STATE";
   }
}

void InitGameStateStack(void)
{
   stateStack.top = 0;
   PushGameState(GAME_STATE_INIT);
   LogMessage(LOG_DEBUG, "Initialized state stack, index is {%zu}", stateStack.top);
}

int PushGameState(GameState state)
{
   if (stateStack.top >= MAX_GAME_STATE_STACK)
   {
      LogMessage(LOG_ERROR,
                 "GameStateStack overflow trying to push state {%s} on stack at index {%zu}.",
                 StateToString(state),
                 stateStack.top);
      return EXIT_FAILURE;
   }

   // Push state on stack before incrementing stack index
   stateStack.states[stateStack.top] = state;
   stateStack.top++;
   LogMessage(LOG_DEBUG,
              "Pushed game state {%s} onto state stack at index {%zu} from index {%zu}",
              StateToString(state),
              stateStack.top,
              stateStack.top - 1);

   return EXIT_SUCCESS;
}

int PopGameState(void)
{
   if (stateStack.top < 1)
   {
      LogMessage(LOG_ERROR,
                 "GameStateStack underflow trying to pop state {%s} from stack at index {%zu}.",
                 StateToString(stateStack.states[stateStack.top]),
                 stateStack.top);
      return EXIT_FAILURE;
   }

   --stateStack.top;
   LogMessage(LOG_DEBUG,
              "Popped state, new state is {%s} at index {%zu}",
              StateToString(stateStack.states[stateStack.top - 1]),
              stateStack.top);

   if (stateStack.top == 0)
   {
      LogMessage(LOG_WARNING, "Game state stack is empty after pop {%zu}", stateStack.top);
   }
   return EXIT_SUCCESS;
}

GameState PeekGameState(void)
{
   if (stateStack.top < 0)
   {
      LogMessage(LOG_ERROR, "Can't peek at state of stack position {%zu}", stateStack.top);
      return EXIT_FAILURE;
   }
   if (stateStack.states[stateStack.top] < GAME_STATE_INIT)
   {
      LogMessage(LOG_ERROR, "Bad state {%s}", StateToString(stateStack.states[stateStack.top]));
      return EXIT_FAILURE;
   }

   return stateStack.states[stateStack.top - 1];
}

int ClearGameStateStack(void)
{
   if (stateStack.top < 0)
   {
      LogMessage(LOG_WARNING, "Nothing in the GameStateStack to clear");
      return EXIT_FAILURE;
   }

   stateStack.top = -1;
   LogMessage(LOG_DEBUG, "Game state stack cleared");
   return EXIT_SUCCESS;
}

const GameStateStack *getStateStack(void)
{
   return &stateStack;
}