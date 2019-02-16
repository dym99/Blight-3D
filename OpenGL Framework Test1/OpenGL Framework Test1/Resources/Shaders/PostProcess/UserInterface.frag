#version 420 

out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uTex;
layout(binding = 1) uniform sampler2D uiTex;

void main() 
{
	vec4 source = texture(uTex, TexCoords);
	vec4 userInterface = texture(uiTex, TexCoords);

	FragColor.rgb = mix(source.rgb, userInterface.rgb, userInterface.a);
}