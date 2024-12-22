#include "game_state_stack.h"
#include "log.h"

#include <stdlib.h>

void InitGameStateStack(GameStateStack *stack)
{
   stack->top = 0;
}

int PushGameState(GameStateStack *stack, GameState state)
{
   if (stack->top >= MAX_GAME_STATE_STACK)
   {
      LogMessage(LOG_ERROR, "GameStateStack overflow trying to push state.");
      return EXIT_FAILURE;
   }

   stack->states[stack->top++] = state;
   return EXIT_SUCCESS;
}

int PopGameState(GameStateStack *stack, GameState *state)
{
   if (stack->top == 0)
   {
      LogMessage(LOG_ERROR, "GameStateStack underflow trying to pop state.");
      return EXIT_FAILURE;
   }

   *state = stack->states[--stack->top];
   return EXIT_SUCCESS;
}

GameState PeekGameState(const GameStateStack *stack)
{
   if (stack->top == 0)
   {
      LogMessage(LOG_ERROR, "GameStateStack empty trying to peek state.");
      return EXIT_FAILURE;
   }

   return stack->states[stack->top - 1];
}

int ClearGameStateStack(GameStateStack *stack)
{
   if (stack->top < 0)
   {
      LogMessage(LOG_INFO, "Nothing in the GameStateStack to clear");
      return EXIT_FAILURE;
   }

   stack->top = -1;
   return EXIT_SUCCESS;
}