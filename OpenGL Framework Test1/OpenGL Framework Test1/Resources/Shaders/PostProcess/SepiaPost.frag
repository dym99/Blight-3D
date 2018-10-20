#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uTex;

void main() 
{
	vec4 source = texture(uTex, TexCoords);
	
	FragColor.r = (source.r * 0.393) + (source.g * 0.769) + (source.b * 0.189) * 1.5;
	FragColor.g = (source.r * 0.349) + (source.g * 0.686) + (source.b * 0.168) * 1.5;
	FragColor.b = (source.r * 0.272) + (source.g * 0.534) + (source.b * 0.131) * 1.5;
	FragColor.a = 1.0f;
}