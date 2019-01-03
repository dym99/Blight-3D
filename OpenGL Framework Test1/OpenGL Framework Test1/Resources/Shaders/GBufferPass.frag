#version 420

uniform sampler2D uTex;

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

layout(location = 0) out vec4 outColors;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec3 outPositions;

void main()
{
    //Standard color output
    outColors.rgb = texture(uTex, TexCoords).rgb;
    outColors.a = 1.0;

    //Pack normals
    //in -> [-1, 1]
    //out -> [0, 1]
    outNormals = normalize(normal0) * 0.5 + 0.5;

    //View space positions
    outPositions = fragPosition;
}