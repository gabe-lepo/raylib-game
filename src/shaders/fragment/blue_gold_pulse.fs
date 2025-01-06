#version 330

out vec4 fragColor;

uniform float u_screenX;
uniform float u_screenY;
uniform float u_time;

// Inverse signed distance function
float iSDF(float glowConstraint, float dist, float freq, float speed)
{
   return glowConstraint / abs(sin(dist * freq + u_time * speed) / freq);
}

void main()
{
   vec2 screen = gl_FragCoord.xy / vec2(u_screenX, u_screenY); // Normalize to [0,1]
   screen = screen * 2.0 - 1.0; // Convert to [-1,1] (screen center is now 0,0)
   screen.x *= u_screenX / u_screenY; // Fix aspect ratio
   vec3 color = vec3(0.0); // Setup default color vec
   float sdfFreq = 8.0; // Frequency of oscillations in iSDF
   float pulseFreq = 0.5; // Frequency of pulsing

   // Do the fun radial effect
   float distance = length(screen) * exp(-length(screen));
   color.r = mix(iSDF(0.02, distance, sdfFreq, 0.5), iSDF(0.01, distance, sdfFreq*2.0, 2.0), 0.02/abs(sin(u_time*pulseFreq)));
   color.g = abs(sin(u_time));
   color.b = mix(iSDF(0.05, distance, sdfFreq, 0.5), iSDF(0.01, distance, sdfFreq*2.0, 2.0), 0.05/abs(sin(u_time*pulseFreq)));

   fragColor = vec4(color, 1.0);
}