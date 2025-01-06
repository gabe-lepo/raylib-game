#version 330

uniform float u_time;
uniform float u_screenHeight;
out vec4 fragColor;

float yOffset = u_screenHeight * 0.5;
float amplitude = u_screenHeight * 0.45;
float frequency = 0.05;
float lineThickness = 20.0;

void main()
{
   float red_wave = sin(gl_FragCoord.x * (frequency * 0.1) + u_time) * amplitude + yOffset;
   float red = smoothstep(1.0, 0.0, abs(gl_FragCoord.y - red_wave) - lineThickness);

   float green_wave = sin(gl_FragCoord.x * (frequency * 0.33) + u_time) * amplitude + yOffset;
   float green = smoothstep(1.0, 0.0, abs(gl_FragCoord.y - green_wave) - lineThickness);

   float blue_wave = sin(gl_FragCoord.x * (frequency * 1.0) + u_time) * amplitude + yOffset;
   float blue = smoothstep(1.0, 0.0, abs(gl_FragCoord.y - blue_wave) - lineThickness);

   fragColor = vec4(red, green, blue, 1.0);
}