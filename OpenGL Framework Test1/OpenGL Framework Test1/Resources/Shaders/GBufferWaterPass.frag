#version 420

layout(binding = 0)uniform sampler2D uAlbedoTex;
layout(binding = 2)uniform sampler2D uEmissiveTex;
layout(binding = 3)uniform sampler2D uMetalnessTex;
layout(binding = 4)uniform sampler2D uRoughnessTex;
uniform vec3 colorTint;

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

layout(location = 0) out vec4 outColors;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec3 outPositions;
layout(location = 3) out vec4 outEmissives;
layout(location = 4) out vec3 outMetalness;
layout(location = 5) out vec3 outRoughness;


void main()
{
    //Standard color output
    outColors.rgb = texture(uAlbedoTex, TexCoords).rgb;
    outColors.a = 1.0;

    //Pack normals
    //in -> [-1, 1]
    //out -> [0, 1]
    outNormals = normalize(normal0) * 0.5 + 0.5;

    //View space positions
    outPositions = fragPosition;

    vec4 emissiveColor = texture(uEmissiveTex, TexCoords);
    //Emissive Maps
    if (emissiveColor.a > 0.1)
        outEmissives = emissiveColor;

    outMetalness = texture(uMetalnessTex, TexCoords).rgb;

    outRoughness = texture(uRoughnessTex, TexCoords).rgb;
}