#version 420

uniform vec2 uPixelSize = vec2(1 / 1080.f, 1 / 720.f);

layout(binding = 0) uniform sampler2D uTexAlbedo;

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

out vec3 outColor;

uniform vec3 uSceneAmbience = vec3(0.15, 0.15, 0.15);

void main()
{
	vec4 albedoColor = texture(uTexAlbedo, TexCoords);
	outColor.rgb = albedoColor.rgb * uSceneAmbience;
}
