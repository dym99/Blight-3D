#version 420

out vec4 FragColor;

in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uTex;
uniform float uTime;

void main() 
{
	vec4 textureColor = texture(uTex, TexCoords);
	vec3 invertTexture = vec3(1.0) - textureColor.rgb;

	FragColor.rgb = invertTexture;
	FragColor.a = 1.0f;
}