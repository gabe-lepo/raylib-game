#version 330

in vec3 vertexPosition;
in vec2 vertextTexCoord;

out vec2 fragTexCoord;

uniform mat4 mvp;

void main()
{
   fragTexCoord = vertextTexCoord;
   gl_Position = mvp * vec4(vertexPosition, 1.0);
}