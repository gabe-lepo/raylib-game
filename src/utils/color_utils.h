#ifndef COLOR_H
#define COLOR_H

#include "raylib.h"
#include "raymath.h"

#include "math.h"

/**
 * @brief HSL colors
 * @param h Hue [0.0 - 360.0]
 * @param s Saturation [0.0 - 1.0]
 * @param l Lightness [0.0 - 1.0]
 * @param a Alpha [0.0 - 255.0]
 */
typedef struct ColorHSL
{
   float h;
   float s;
   float l;
   float a;
} ColorHSL;

ColorHSL RGBToHSL(Color rgb);
Color HSLToRGB(ColorHSL hsl);
Color GetRandomColor(int min, int max, int alpha);
Color GetComplimentaryColor(Color color);
Color GetAnalogousColor(Color baseColor, int hueShift);
void GetTriadicColors(Color baseColor, Color *color1, Color *color2);
Color BlendColors(Color c1, Color c2, float factor);
float GetContrast(Color c1, Color c2);
void GenerateGradient(Color *gradientArray, Color start, Color end, int steps);

#endif