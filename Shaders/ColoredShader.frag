#version 330 core

in vec4 vertexPosition;
in vec3 ourColor;
out vec4 outColor;

void main()
{
	outColor = vec4(ourColor, 1.0);
}