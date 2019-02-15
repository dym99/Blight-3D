#version 420

layout (binding = 0) uniform sampler2D uSceneTex;
layout (binding = 1) uniform sampler2D uEdgeTex;

in vec2 TexCoords;

out vec4 outColor;

void main()
{
    vec4 sceneColor = texture(uSceneTex, TexCoords);
    vec4 edgeColor = vec4(texture(uEdgeTex, TexCoords).r);
    outColor = sceneColor * edgeColor;
}

