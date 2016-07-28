#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;

uniform vec3 ourPosition;

void main()
{
	gl_Position = vec4(position.x + ourPosition.x, position.y + ourPosition.y, position.z + ourPosition.z, 1.0);
	ourColor = color;
}