#version 420

layout (binding = 0) uniform sampler2D uNormalMap;
layout (binding = 1) uniform sampler2D uDepthMap;

uniform vec2 uPixel = vec2(1.0 / 1000, 1.0 / 1000);
uniform float edgeThreshNormal = 1.f;
uniform float edgeThreshDepth = 0.00005;

in vec2 TexCoords;

out float edgeOut;

float computeHorizontalNorm(sampler2D normal, vec2 texcoords)
{
    vec3 sum = vec3(0.0);

    sum += texture(normal, vec2(texcoords.x + uPixel.x, texcoords.y - uPixel.y)).rgb;
    sum += texture(normal, vec2(texcoords.x + uPixel.x, texcoords.y           )).rgb * 2.0;
    sum += texture(normal, vec2(texcoords.x + uPixel.x, texcoords.y + uPixel.y)).rgb;

    sum -= texture(normal, vec2(texcoords.x - uPixel.x, texcoords.y - uPixel.y)).rgb;
    sum -= texture(normal, vec2(texcoords.x - uPixel.x, texcoords.y           )).rgb * 2.0;
    sum -= texture(normal, vec2(texcoords.x - uPixel.x, texcoords.y + uPixel.y)).rgb;

    float factor = dot(sum, sum);

    if (factor < edgeThreshNormal)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}

float computeHorizontalDepth(sampler2D depth, vec2 texcoords)
{
    float sum = 0.0;

    sum += texture(depth, vec2(texcoords.x + uPixel.x, texcoords.y - uPixel.y)).r;
    sum += texture(depth, vec2(texcoords.x + uPixel.x, texcoords.y           )).r * 2.0;
    sum += texture(depth, vec2(texcoords.x + uPixel.x, texcoords.y + uPixel.y)).r;

    sum -= texture(depth, vec2(texcoords.x - uPixel.x, texcoords.y - uPixel.y)).r;
    sum -= texture(depth, vec2(texcoords.x - uPixel.x, texcoords.y           )).r * 2.0;
    sum -= texture(depth, vec2(texcoords.x - uPixel.x, texcoords.y + uPixel.y)).r;

    if (abs(sum) < edgeThreshDepth)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}

float computeVerticalNorm(sampler2D normal, vec2 texcoords)
{
    vec3 sum = vec3(0.0);

    sum += texture(normal, vec2(texcoords.x - uPixel.x, texcoords.y + uPixel.y)).rgb;
    sum += texture(normal, vec2(texcoords.x           , texcoords.y + uPixel.y)).rgb * 2.0;
    sum += texture(normal, vec2(texcoords.x + uPixel.x, texcoords.y + uPixel.y)).rgb;

    sum -= texture(normal, vec2(texcoords.x - uPixel.x, texcoords.y - uPixel.y)).rgb;
    sum -= texture(normal, vec2(texcoords.x           , texcoords.y - uPixel.y)).rgb * 2.0;
    sum -= texture(normal, vec2(texcoords.x + uPixel.x, texcoords.y - uPixel.y)).rgb;

    float factor = dot(sum, sum);

    if (factor < edgeThreshNormal)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}


float computeVerticalDepth(sampler2D depth, vec2 texcoords)
{
    float sum = 0.0;

    sum += texture(depth, vec2(texcoords.x - uPixel.x, texcoords.y + uPixel.y)).r;
    sum += texture(depth, vec2(texcoords.x           , texcoords.y + uPixel.y)).r * 2.0;
    sum += texture(depth, vec2(texcoords.x + uPixel.x, texcoords.y + uPixel.y)).r;

    sum -= texture(depth, vec2(texcoords.x - uPixel.x, texcoords.y - uPixel.y)).r;
    sum -= texture(depth, vec2(texcoords.x           , texcoords.y - uPixel.y)).r * 2.0;
    sum -= texture(depth, vec2(texcoords.x + uPixel.x, texcoords.y - uPixel.y)).r;

    if (abs(sum) < edgeThreshDepth)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}


void main()
{
    float sobelNormal = computeHorizontalNorm(uNormalMap, TexCoords) * computeVerticalNorm(uNormalMap, TexCoords);
    float sobelDepth = computeVerticalDepth(uDepthMap, TexCoords) * computeHorizontalDepth(uDepthMap, TexCoords);
    edgeOut = sobelDepth * sobelNormal;
}