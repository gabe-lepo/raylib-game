#include "screen_chunks.h"
#include "logging/log.h"
#include "utils/color_utils.h"
#include "game/screen.h"

#include <stdlib.h>

static Chunk **screen_chunks = NULL;
static int chunkCount = 0;
static int xChunks = 0;
static int yChunks = 0;
static int divisor = 100;

void InitChunks(void)
{
   xChunks = SCREEN_DIMENSIONS.x / divisor;
   yChunks = SCREEN_DIMENSIONS.y / divisor;
   chunkCount = xChunks * yChunks;

   // Allocate memory
   screen_chunks = (Chunk **)malloc(xChunks * sizeof(Chunk *));
   for (int i = 0; i < xChunks; i++)
   {
      screen_chunks[i] = (Chunk *)malloc(yChunks * sizeof(Chunk));
   }

   // Init each chunk
   for (int i = 0; i < xChunks; i++)
   {
      for (int j = 0; j < yChunks; j++)
      {
         Shape chunkShape = {
             .type = SHAPE_TYPE_RECTANGLE,
             .rectangle = {
                 .x = i * divisor,
                 .y = j * divisor,
                 .width = divisor,
                 .height = divisor,
             }};

         Color chunkColor = GetRandomColor(0.0f, 255.0f, 255.0f);
         const char *chunkLabel = TextFormat("%dx%d", i, j);

         // Init the objects
         InitGameObject(
             &screen_chunks[i][j].object,
             chunkShape,
             chunkColor,
             OBJECT_TYPE_NON_COLLIDEABLE,
             chunkLabel);
      }
   }
}

void UpdateChunks(void)
{
   // TODO
}

void DrawChunks(void)
{
   for (int i = 0; i < xChunks; i++)
   {
      for (int j = 0; j < yChunks; j++)
      {
         DrawGameObject(&screen_chunks[i][j].object);
      }
   }
}

Chunk **GetChunks(int *countChunks, int *xCount, int *yCount)
{
   *countChunks = chunkCount;
   *xCount = xChunks;
   *yCount = yChunks;
   return screen_chunks;
}

void CleanUpChunks(void)
{
   if (screen_chunks)
   {
      // Cleanup labels
      for (int i = 0; i < xChunks; i++)
      {
         for (int j = 0; j < yChunks; j++)
         {
            CleanUpObject(&screen_chunks[i][j].object);
         }
      }

      // Free memory
      for (int i = 0; i < xChunks; i++)
      {
         free(screen_chunks[i]);
      }
      free(screen_chunks);
      screen_chunks = NULL;
   }
}