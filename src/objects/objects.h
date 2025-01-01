#ifndef OBJECTS_H
#define OBJECTS_H

#include "raylib.h"

typedef enum ObjectShapeType
{
   SHAPE_TYPE_RECTANGLE = 0,
   SHAPE_TYPE_CIRCLE,
   SHAPE_TYPE_TRIANGLE,
   SHAPE_TYPE_CUSTOM,
} ObjectShapeType;

typedef struct Shape
{
   ObjectShapeType type;
   union
   {
      Rectangle rectangle;
      struct
      {
         Vector2 center;
         float radius;
      } circle;
      struct
      {
         Vector2 v1;
         Vector2 v2;
         Vector2 v3;
      } triangle;
   };
} Shape;

typedef enum ObjectType
{
   OBJECT_TYPE_COLLIDEABLE = 0,
   OBJECT_TYPE_NON_COLLIDEABLE,
} ObjectType;

typedef struct GameObject
{
   ObjectType type;
   Shape shape;
   Color color;
   char *label;

   Vector2 corners[4]; // {top left, top right, bottom left, bottom right}
} GameObject;

void InitGameObject(GameObject *object, Shape shape, Color color, ObjectType type, const char *label);
void UpdateGameObject(GameObject *object);
void DrawGameObject(GameObject *object);
void CleanUpObject(GameObject *object);

#endif