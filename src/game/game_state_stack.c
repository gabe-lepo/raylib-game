#include "game_state_stack.h"
#include "log.h"

#include <stdlib.h>

static GameStateStack stateStack;

void InitGameStateStack(void)
{
   stateStack.top = 0;
   PushGameState(GAME_STATE_INIT);
   LogMessage(LOG_INFO, "Initialized state stack, index is {%zu}", stateStack.top);
}

int PushGameState(GameState state)
{
   if (stateStack.top >= MAX_GAME_STATE_STACK)
   {
      LogMessage(LOG_ERROR, "GameStateStack overflow trying to push state {%d} on stack position {%zu}.", state, stateStack.top);
      return EXIT_FAILURE;
   }

   stateStack.states[stateStack.top++] = state;
   LogMessage(LOG_INFO, "Pushed game state {%d} onto state stack at index {%zu}", state, stateStack.top);
   return EXIT_SUCCESS;
}

GameState PopGameState(void)
{
   if (stateStack.top <= GAME_STATE_INIT)
   {
      LogMessage(LOG_ERROR, "GameStateStack underflow trying to pop state {%d} from stack position {%zu}.", stateStack.states[stateStack.top - 1], stateStack.top);
      return GAME_STATE_INIT;
   }

   --stateStack.top;

   if (stateStack.top > GAME_STATE_INIT)
   {
      LogMessage(LOG_INFO, "Popped state, new state is {%d} at index {%zu}", stateStack.states[stateStack.top - 1], stateStack.top);
      return stateStack.states[stateStack.top - 1];
   }

   LogMessage(LOG_WARNING, "Game state stack is empty after pop");
   return GAME_STATE_INIT;
}

GameState PeekGameState(void)
{
   if (stateStack.top <= 0)
   {
      LogMessage(LOG_ERROR, "Error trying to peek at state of stack position {%zu}.", stateStack.top);
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
   LogMessage(LOG_INFO, "Game state stack cleared");
   return EXIT_SUCCESS;
}