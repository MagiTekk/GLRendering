#version 330 core

in vec3 ourColor;
in vec2 textCoord;

out vec4 outColor;

uniform sampler2D ourTexture;

void main()
{
	outColor = texture(ourTexture, textCoord);
}