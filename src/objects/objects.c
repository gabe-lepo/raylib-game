#include "objects.h"
#include "logging/log.h"
#include "utils/color_utils.h"

#include "string.h"
#include "stdlib.h"

void InitGameObject(GameObject *object, Shape shape, Color color, ObjectType type, const char *label)
{
   if (!object)
   {
      LogMessage(LOG_ERROR, "Object is null trying to InitObject");
      return;
   }

   LogMessage(LOG_INFO, "Initializing object...");

   // Init basic object members
   object->shape = shape;
   object->color = color;
   object->type = type;

   if (label)
   {
      object->label = malloc(strlen(label) + 1);
      if (object->label)
         strcpy(object->label, label);
   }
   else
   {
      object->label = NULL;
   }

   LogMessage(LOG_INFO,
              "Done initializing object {%s}, parameters:\n"
              "\tShape: {%d}\n"
              "\tType: {%s}\n"
              "\tColor: {R:%d, G:%d, B:%d, A:%d}\n"
              "\tPosition: {%.0fx%.0f}\n"
              "\tSize: {%.0fx%.0f}",
              object->label ? object->label : "NULL",
              object->shape.type,
              object->type == OBJECT_TYPE_COLLIDEABLE ? "Collideable" : "Non-collideable",
              object->color.r, object->color.g, object->color.b, object->color.a,
              object->shape.rectangle.x, object->shape.rectangle.y,
              object->shape.rectangle.width, object->shape.rectangle.height);
}

void UpdateGameObject(GameObject *object)
{
   // TODO
}

void DrawGameObject(GameObject *object)
{
   if (!object || !object->label)
   {
      LogMessage(LOG_ERROR, "Object or object label is null!");
      return;
   }

   // Setup label stuff
   int textSize = 20;
   int textWidth = MeasureText(object->label, textSize);
   Vector2 labelPosition = {0};

   // Draw object shapes, setup label positioning
   switch (object->shape.type)
   {
   case SHAPE_TYPE_RECTANGLE:
      DrawRectangleRec(object->shape.rectangle, object->color);
      labelPosition.x = object->shape.rectangle.x + (object->shape.rectangle.width / 2) - (textWidth / 2);
      labelPosition.y = object->shape.rectangle.y + (object->shape.rectangle.height / 2) - (textSize / 2);
      break;
   case SHAPE_TYPE_CIRCLE:
      DrawCircleV(object->shape.circle.center, object->shape.circle.radius, object->color);
      labelPosition.x = object->shape.circle.center.x - (textWidth / 2);
      labelPosition.y = object->shape.circle.center.y - (textSize / 2);
      break;
   case SHAPE_TYPE_TRIANGLE:
      DrawTriangle(object->shape.triangle.v1, object->shape.triangle.v2, object->shape.triangle.v3, object->color);
      Vector2 triangleCenter = {
          (object->shape.triangle.v1.x + object->shape.triangle.v2.x + object->shape.triangle.v3.x) / 3,
          (object->shape.triangle.v1.y + object->shape.triangle.v2.y + object->shape.triangle.v3.y) / 3};
      labelPosition.x = triangleCenter.x - (textWidth / 2);
      labelPosition.y = triangleCenter.y - (textSize / 2);
      break;
   default:
      LogMessage(LOG_WARNING, "Unsupported shape type {%d} in DrawGameObject", object->shape.type);
      break;
   }

   // Draw label
   DrawText(object->label, labelPosition.x, labelPosition.y, textSize, GetComplimentaryColor(object->color));
}

void CleanUpObject(GameObject *object)
{
   if (!object || !object->label)
   {
      LogMessage(LOG_ERROR, "Object or object label is null!");
      return;
   }
   else
   {
      free(object->label);
      object->label = NULL;
   }
}