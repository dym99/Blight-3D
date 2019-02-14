#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uTex;

void main() 
{
	vec4 source = texture(uTex, TexCoords);

	FragColor.rgb = source.rgb;
}