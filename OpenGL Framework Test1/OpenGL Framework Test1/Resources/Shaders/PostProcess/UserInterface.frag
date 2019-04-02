#version 420 

out vec4 FragColor;

in vec2 TexCoords;

uniform float uHealth;
uniform float uHealth2;
uniform float uScore;
uniform int uWave;
uniform float ;

layout(binding = 0) uniform sampler2D uTex;
layout(binding = 1) uniform sampler2D uiTex;
layout(binding = 2) uniform sampler2D uiMask;

void main() 
{
	vec4 source = texture(uTex, TexCoords);
	vec4 userInterface = texture(uiTex, TexCoords);

	float unit = 1.f/32.f;
	float healthX = min(((uHealth / 10 * unit) + unit ) - TexCoords.x, 1);
	float healthYellowX = min(((uHealth2 / 10 * unit) + unit) - TexCoords.x, 1);

	vec3 healthColor = vec3(ceil(healthX),0, 0);
	vec3 healthYellowColor = vec3(0, ceil(healthYellowX), 0);

	healthColor = (healthYellowColor == vec3(0.f, 1.f, 0.f)) ? 
				(healthColor == vec3(1.f, 0.f, 0.f)) ? vec3(1.f, 0.f, 0.f) : vec3(1.f, 1.f, 0.f) 
				: 
				vec3(0.f, 0.f, 0.f);

	float alpha = texture(uiMask, TexCoords).r;
	float modifier = (healthColor == vec3(0.f, 0.f, 0.f)) ? 0.f : 1.f;

	FragColor.rgb = mix(source.rgb, healthColor.rgb, alpha * modifier);
	


	//MINIMAP HAS BEEN CUT
	//float scale = 3f;
	//float ratio = 1024.f / 330.f;
	//vec2 miniMapCoords = vec2(TexCoords.x * ratio * scale, TexCoords.y * scale);
	//vec4 miniMap = texture(uMapTex, miniMapCoords);
	
	//float modif = floor(clamp(miniMapCoords.x, 0, 1)) * floor(clamp(miniMapCoords.y, 0, 1));
	//FragColor.rgb = mix(source.rgb, miniMap.rgb, 1 - modif);
}