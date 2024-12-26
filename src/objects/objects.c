#include "objects.h"
#include "logging/log.h"

#include "string.h"
#include "stdlib.h"

void InitGameObject(GameObject *object, Vector2 position, Vector2 size, Color color, ObjectType type, const char *label)
{
   object->rect.x = position.x;
   object->rect.y = position.y;
   object->rect.width = size.x;
   object->rect.height = size.y;
   object->color = color;
   object->type = type;

   // Dynamic label allocation
   if (label)
   {
      object->label = malloc(strlen(label) + 1);
      if (object->label)
      {
         strcpy(object->label, label);
      }
   }
   else
   {
      object->label = NULL;
   }

   LogMessage(LOG_INFO,
              "Done initializing object {%s}, parameters:\n"
              "\tPosition: {%.0fx%.0f}\n"
              "\tType: {%s}\n"
              "\tSize: {%.0fx%.0f}\n"
              "\tColor: {R:%d, G:%d, B:%d, A:%d}",
              object->label ? object->label : "NULL",
              object->rect.x,
              object->rect.y,
              object->type == OBJECT_TYPE_COLLIDEABLE ? "Collideable" : "Non-collideable",
              object->rect.width,
              object->rect.height,
              object->color.r, object->color.g, object->color.b, object->color.a);
}

void UpdateGameObject(GameObject *object)
{
   // TODO
}

void DrawGameObject(GameObject *object)
{
   DrawRectangleRec(object->rect, object->color);
   if (object->label)
   {
      int textWidth = MeasureText(object->label, 20);
      int textSize = 20;
      float textX = object->rect.x + (object->rect.width / 2) - (textWidth / 2);
      float textY = object->rect.y + (object->rect.height / 2) - (textSize / 2);

      DrawText(object->label, textX, textY, textSize, BLACK);
   }
}

void CleanUpObject(GameObject *object)
{
   if (object->label)
   {
      free(object->label);
      object->label = NULL;
   }
}