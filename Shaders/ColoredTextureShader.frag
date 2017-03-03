#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D ourTexture;

void main()
{
	//outColor = vec4(ourColor, 1.0);
	outColor = texture(ourTexture, TexCoord);
}