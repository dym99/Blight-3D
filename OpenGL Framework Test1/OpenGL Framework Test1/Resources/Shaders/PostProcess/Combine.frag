#version 420

layout (binding = 0) uniform sampler2D uSceneTex;
layout (binding = 1) uniform sampler2D uSecondTex;

in vec2 TexCoords;

out vec4 outColor;

void main()
{
	vec3 colorA = texture(uSceneTex, TexCoords).rgb;
	vec3 colorB = texture(uSecondTex, TexCoords).rgb;

	outColor.rgb = (1.0 - (1.0 - colorA) * (1.0 - colorB)).rgb;
}

