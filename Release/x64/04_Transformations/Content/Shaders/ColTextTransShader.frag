#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float alphaBlend;

void main()
{
	outColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2( 1.0 - TexCoord.x, TexCoord.y)), alphaBlend);
}