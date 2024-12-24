#ifndef OBJECTS_H
#define OBJECTS_H

#include "raylib.h"

typedef enum ObjectType
{
   OBJECT_TYPE_COLLIDEABLE = 0,
   OBJECT_TYPE_NON_COLLIDEABLE,
} ObjectType;

typedef struct GameObject
{
   Rectangle rect;
   Vector2 size;
   Color color;
   ObjectType type;
} GameObject;

void InitGameObject(GameObject *object, Vector2 position, Vector2 size, Color color, ObjectType type);
void UpdateGameObject(GameObject *object);
void DrawGameObject(GameObject *object);

#endif