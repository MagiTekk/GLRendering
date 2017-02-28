#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float xOffset;
out vec3 ourColor;

void main()
{
	ourColor = color;
	gl_Position = vec4(position.x + xOffset, -position.y, position.z, 1.0);
}