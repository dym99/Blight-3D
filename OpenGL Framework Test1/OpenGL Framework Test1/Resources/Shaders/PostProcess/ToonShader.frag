#version 420

layout (binding = 0) uniform sampler2D uFinishedFrame;
layout (binding = 1) uniform sampler2D uNormalMap;
layout (binding = 3) uniform sampler2D uToonRamp;

in vec2 TexCoords;

out vec4 outColor;

uniform vec4 ambience = vec4(0.15);

void main()
{
    vec4 textureColor = texture(uFinishedFrame, TexCoords);
    vec4 normalColor = texture(uNormalMap, TexCoords) * ambience;

    float intensity = dot(textureColor, normalColor);

    vec4 toonColor = texture(uToonRamp, vec2(intensity, 0.f));

    outColor = vec4(textureColor);
}