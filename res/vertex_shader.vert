#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec3 ourPosition;

void main()
{
	gl_Position = vec4(position.x + ourPosition.x, position.y + ourPosition.y, position.z + ourPosition.z, 1.0);
	ourColor = color;
	TexCoord = texCoord;
}