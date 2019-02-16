#version 420

out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uTex;

void main() 
{
	vec4 source = texture(uTex, TexCoords);
	
	float luminence = 0.2989 * source.r + 0.587 * source.g + 0.114 * source.b;
	
	FragColor.rgb = vec3(luminence, luminence, luminence);
	FragColor.a = 1.0f;
}