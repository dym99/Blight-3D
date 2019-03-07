#version 420

out vec4 FragColor;

layout (binding = 0) uniform sampler2D uScene;
layout (binding = 1) uniform sampler2D uEmissiveMap;

in vec2 TexCoords;

void main()
{
    vec4 sceneColor = texture(uScene, TexCoords);
    vec4 emissiveColor = texture(uEmissiveMap, TexCoords);
	FragColor = sceneColor;
}