#version 420

layout (binding = 0) uniform sampler2D uSceneTex;
layout (binding = 1) uniform sampler2D uSecondTex;

in vec2 TexCoords;

out vec4 outColor;

void main()
{
    vec4 sceneColor = texture(uSceneTex, TexCoords);
    vec4 secondColor = vec4(texture(uSecondTex, TexCoords).r);
    outColor = sceneColor * secondColor;
}

