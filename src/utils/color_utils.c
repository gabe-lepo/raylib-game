#include "color_utils.h"

#include "math.h"

// Util utils
/**
 * @brief Convert RGB Color structs to *HSL
 *
 * @param rgb RGB Color struct to convert
 * @param h Pointer to hue
 * @param s Pointer to saturation
 * @param l Pointer to luminance
 *
 * @return void - Sets referenced HSL values
 */
void RGBToHSL(Color rgb, float *h, float *s, float *l)
{
   float r = rgb.r / 255.0f;
   float g = rgb.g / 255.0f;
   float b = rgb.b / 255.0f;

   float min = fminf(r, fminf(g, b));
   float max = fmaxf(r, fmaxf(g, b));
   float delta = max - min;

   // Lightness
   *l = (max + min) / 2.0f;

   // Saturation
   if (delta == 0)
      *s = 0;
   else
      *s = delta / (1.0f - fabsf(2.0f * *l - 1.0f));

   // Hue
   if (delta == 0)
      *h = 0;
   else if (max == r)
      *h = fmodf((g - b) / delta, 6.0f);
   else if (max == g)
      *h = (b - r) / delta + 2.0f;
   else
      *h = (r - g) / delta + 4.0f;

   *h *= 60.0f; // Degrees
   if (*h < 0)
      *h += 360.0f; // Ensure hue is positive
}

/**
 * @brief Convert HSL to RGB
 *
 * @param h Hue float
 * @param s Saturation float
 * @param l luminance float
 *
 * @return RGB Color struct
 */
Color HSLToRGB(float h, float s, float l)
{
   float c = (1.0f - fabsf(2.0f * l - 1.0f)) * s;
   float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
   float m = l - c / 2.0f;

   float r, g, b;
   if (h >= 0 && h < 60)
      r = c, g = x, b = 0;
   else if (h >= 60 && h < 120)
      r = x, g = c, b = 0;
   else if (h >= 120 && h < 180)
      r = 0, g = c, b = x;
   else if (h >= 180 && h < 240)
      r = 0, g = x, b = c;
   else if (h >= 240 && h < 300)
      r = x, g = 0, b = c;
   else
      r = c, g = 0, b = x;

   r = (r + m) * 255.0f;
   g = (g + m) * 255.0f;
   b = (b + m) * 255.0f;

   return (Color){
       (unsigned char)r,
       (unsigned char)g,
       (unsigned char)b,
       255};
}

/**
 * @brief Generates a random color with each RGB component between the specified min and max values.
 *
 * @param min The minimum value for the RGB components.
 * @param max The maximum value for the RGB components.
 * @param alpha The alpha value for the color.
 *
 * @return A Color struct with random RGB values and the specified alpha.
 */
Color GetRandomColor(int min, int max, int alpha)
{
   // Clamping/corrections
   if (min < 0)
      min = 0;
   if (max > 255)
      max = 255;
   if (alpha < 0)
      alpha = 0;
   if (alpha > 255)
      alpha = 255;

   return (Color){GetRandomValue(min, max), GetRandomValue(min, max), GetRandomValue(min, max), alpha};
}

/**
 * @brief Get the Complimentary Color object
 *
 * @param color Color struct
 *
 * @return Color Complimentary Color struct
 */
Color GetComplimentaryColor(Color color)
{
   Color result = {255 - color.r,
                   255 - color.g,
                   255 - color.b,
                   color.a};
   return result;
}

/**
 * @brief Get the Analogous shifted Color struct
 *
 * @param baseColor Starting Color
 * @param hueShift Degrees to shift hue
 *
 * @return Shifted Color struct
 */
Color GetAnalogousColor(Color baseColor, int hueShift)
{
   float h, s, l;
   RGBToHSL(baseColor, &h, &s, &l);
   h += hueShift;

   if (h > 360.0f)
      h -= 360.0f;
   if (h < 0.0f)
      h += 360.0f;

   return HSLToRGB(h, s, l);
}

/**
 * @brief Get the Triadic colors for a given Color struct
 *
 * @param baseColor Used to find remaining triadic colors
 * @param color1 Reference to first triadic result
 * @param color2 Reference to second triadic result
 *
 * @return void - Sets referenced Color structs to triadic baseColor result
 */
void GetTriadicColors(Color baseColor, Color *color1, Color *color2)
{
   float h, s, l;
   RGBToHSL(baseColor, &h, &s, &l);

   *color1 = HSLToRGB(fmodf(h + 120.0f, 360.0f), s, l);
   *color2 = HSLToRGB(fmodf(h - 120.0f, 360.0f), s, l);
}

/**
 * @brief Compute blend between 2 Color structs
 *
 * @param c1 First Color struct
 * @param c2 Second Color struct
 * @param factor Float factor value
 *
 * @return Color Blended Color struct
 */
Color BlendColors(Color c1, Color c2, float factor)
{
   // Clamp/normalize
   if (factor < 0.0f)
      factor = 0.0f;
   if (factor > 1.0f)
      factor = 1.0f;

   return (Color){
       (unsigned char)(c1.r + factor * (c2.r - c1.r)),
       (unsigned char)(c1.g + factor * (c2.g - c1.g)),
       (unsigned char)(c1.b + factor * (c2.b - c1.b)),
       (unsigned char)(c1.a + factor * (c2.a - c1.a))};
}

/**
 * @brief Get the Contrast between 2 Color structs
 *
 * @cite https://en.wikipedia.org/wiki/Rec._709
 *
 * @param c1 First Color struct
 * @param c2 Second Color struct
 *
 * @return float Floating point contrast
 */
float GetContrast(Color c1, Color c2)
{
   float redPercepWeight = 0.2126f;
   float greenPercepWeight = 0.7152f;
   float bluePercepWeight = 0.0722f;

   float luminance1 = redPercepWeight * c1.r + greenPercepWeight * c1.g + bluePercepWeight * c1.b;
   float luminance2 = redPercepWeight * c2.r + greenPercepWeight * c2.g + bluePercepWeight * c2.b;

   return (luminance1 > luminance2) ? (luminance1 + 0.05f) / (luminance2 + 0.05f) : (luminance2 + 0.05f) / (luminance1 + 0.05f);
}

/**
 * @brief Insert array of gradient Color structs to the referenced gradientArray.
 *
 * @param gradientArray Pointer to array of Color structs
 * @param start Starting of gradient
 * @param end End of gradient
 * @param steps "Resolution" of gradient
 *
 * @return void - Assign gradient array to referenced object
 */
void GenerateGradient(Color *gradientArray, Color start, Color end, int steps)
{
   for (int i = 0; i < steps; i++)
   {
      float ratio = (float)i / (float)(steps - 1); // Normalize steps
      gradientArray[i].r = (unsigned char)(start.r * (1 - ratio) + end.r * ratio);
      gradientArray[i].g = (unsigned char)(start.g * (1 - ratio) + end.g * ratio);
      gradientArray[i].b = (unsigned char)(start.b * (1 - ratio) + end.b * ratio);
      gradientArray[i].a = 255;
   }
}