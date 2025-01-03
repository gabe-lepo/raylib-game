#version 330

in vec2 fragTexCoord;

out vec4 finalColor;

uniform sampler2D texture0;
uniform float time;

void main()
{
   vec4 texColor = texture(texture0, fragTexCoord);
   float wave = sin(fragTexCoord.y * 10.0 + time) * 0.1;
   finalColor = vec4(texColor.rgb + wave, texColor.a);
}