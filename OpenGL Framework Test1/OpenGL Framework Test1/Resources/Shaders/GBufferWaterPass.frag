#version 420

layout(binding = 0)uniform sampler2D uAlbedoTex;
layout(binding = 1)uniform sampler2D uNormalTex;
layout(binding = 2)uniform sampler2D uEmissiveTex;
layout(binding = 3)uniform sampler2D uMetalnessTex;
layout(binding = 4)uniform sampler2D uRoughnessTex;
layout(binding = 6)uniform sampler2D uDirectionTex;

uniform vec3 colorTint;
uniform int noNormMap;
uniform float uTime = 0.f;
uniform float uSpeed = 0.25f;
uniform float uTile = 1.f;
uniform float uFlowStrength = 0.15f;
uniform float uFlowOffset = -0.25f;

uniform float jumpX = 0.4;
uniform float jumpY = 0.2583;

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;
//in vec3 tangent0;
//in vec3 bitangent0;

layout(location = 0) out vec4 outColors;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec3 outPositions;
layout(location = 3) out vec4 outEmissives;
layout(location = 4) out vec3 outMetalness;
layout(location = 5) out vec3 outRoughness;

//Grabs just the fraction
float frac(float full)
{
    //Grabs the full number, minus the closest whole number
    return full - floor(full);
}

//Calculates the flowing UV coordinate according to the flow map
vec3 flowUV(vec2 uv, vec2 flowVec, vec2 jump, float tiling, float flowOffset, float time, bool flowTwo)
{
    //Offsets the flow based on if this is the first created uv or the second
    float phaseShift = flowTwo ? 0.5 : 0.0;
    //How far are you through the wave
    float progress = frac(time + phaseShift);
    //This allows us to hold a blend weight as well
    vec3 uvWeight;
    //Calculate the flowing uv based on the direction (flowVec) multiplied by the how far through you are (progress) with the flow offset 
    uvWeight.xy = uv - flowVec * (progress + flowOffset);
    uvWeight.xy *= tiling;
    uvWeight.xy += phaseShift;
    //JUMPS to another UV coordinate based
    uvWeight.xy += (time - progress) * jump;
    //Gets the blend weighting 
    uvWeight.z = 1 - abs(1 - 2 * progress);
    return uvWeight;
}

void main()
{
    //There is noise in the alpha of the texture that allows us to offset time :O
    float noise = texture(uDirectionTex, TexCoords).a;
    float disTime = uTime * uSpeed + noise;

    //Jump value, allows us to *jump* to a new offset instead of "sliding" to a new offset (would introduce a visual bias because you're sliding)
    vec2 jump = vec2(jumpX, jumpY);

    //Loads in the perlin-curl noise texture
    vec2 direction = normalize(texture(uDirectionTex, TexCoords).rg * 2.0 - 1.0);
    direction *= uFlowStrength;

    //flowed uv coordinates, for two separate offset phases
    vec3 texOffsetWeight = flowUV(TexCoords, direction, jump, uTile, uFlowOffset, disTime, false);
    vec3 texOffsetWeight2 = flowUV(TexCoords, direction, jump, uTile, uFlowOffset,disTime, true);
    
    //Blending two flowing waves
    vec3 color1 = texture(uAlbedoTex, texOffsetWeight.xy).rgb * texOffsetWeight.z;
    vec3 color2 = texture(uAlbedoTex, texOffsetWeight2.xy).rgb * texOffsetWeight2.z;
    
    //Blends the two flows together to remove the black waves
    outColors.rgb = (color1 + color2).rgb;
    outColors.a = 1.0;

    //Pack normals
    //in -> [-1, 1]
    //out -> [0, 1]
    //If there is no normal map, it'll multiply the regular normals by 1 and just add vec3(0.f, 0.f, 0.f) to the normals (as norm map will be black if there isn't one)
    //If there is a normal map, it'll multiply the regular normals by 0 and add the normal map to the normals
    //vec3 normals = normalize(normal0);
    //vec3 tangents = normalize(tangent0);
    //vec3 bitangents = normalize(bitangent0);
//
    //mat3 tangentSpaceToWorldSpace = mat3(tangent.x, bitangent.x, normal.x,
    //                                     tangent.y, bitangent.y, normal.y,
    //                                     tangent.z, bitangent.z, normal.z);

    vec3 normMap = texture(uNormalTex, TexCoords).rgb * 2.0 - 1.0;
   // normMap = normMap * tangentSpaceToWorldSpace;
    outNormals = normalize(normMap) * 0.5 + 0.5;

    //View space positions
    outPositions = fragPosition;

    vec4 emissiveColor = texture(uEmissiveTex, TexCoords);
    //Emissive Maps
    if (emissiveColor.a > 0.1)
        outEmissives = emissiveColor;

    outMetalness = texture(uMetalnessTex, TexCoords).rgb;

    outRoughness = texture(uRoughnessTex, TexCoords).rgb;
}