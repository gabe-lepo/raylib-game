#ifndef COLOR_H
#define COLOR_H

#include "raylib.h"

void RGBToHSL(Color rgb, float *h, float *s, float *l);
Color HSLToRGB(float h, float s, float l);
Color GetRandomColor(int min, int max, int alpha);
Color GetComplimentaryColor(Color color);
Color GetAnalogousColor(Color baseColor, int hueShift);
void GetTriadicColors(Color baseColor, Color *color1, Color *color2);
Color BlendColors(Color c1, Color c2, float factor);
float GetContrast(Color c1, Color c2);
void GenerateGradient(Color *gradientArray, Color start, Color end, int steps);

#endif