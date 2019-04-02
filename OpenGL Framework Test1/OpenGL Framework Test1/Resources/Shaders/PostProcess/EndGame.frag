#version 420 

out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 1) uniform sampler2D uTex;

void main() 
{
	vec4 source = texture(uTex, TexCoords);

    FragColor.rgb = source.rgb;
    FragColor.a = 1.0f;
}