#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uTex;
uniform sampler2D uiTex;

void main() 
{
	vec4 source = texture(uTex, TexCoords);
	vec4 userInterface = texture(uiTex, TexCoords);

    FragColor.rgb = source.rgb;
    FragColor += userInterface;
}