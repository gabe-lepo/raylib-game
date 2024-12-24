#include "objects.h"

void InitGameObject(GameObject *object, Vector2 position, Vector2 size, Color color, ObjectType type)
{
   object->rect.x = position.x;
   object->rect.y = position.y;
   object->rect.width = size.x;
   object->rect.height = size.y;
   object->color = color;
   object->type = type;
}

void UpdateGameObject(GameObject *object)
{
   // TODO
}

void DrawGameObject(GameObject *object)
{
   DrawRectangleRec(object->rect, object->color);
}