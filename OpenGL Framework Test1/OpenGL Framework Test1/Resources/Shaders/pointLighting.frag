#version 420

layout (std140, binding = 2) uniform PointLight
{
    uniform vec3 uLightColor;
    uniform vec3 uLightPosition;
    uniform vec4 uLightAttenuation;
};

#define uLightConstantAttenuation uLightAttenuation.x
#define uLightLinearAttenuation uLightAttenuation.y
#define uLightQuadAttenuation uLightAttenuation.z
#define uLightRadius uLightAttenuation.w

uniform vec2 uPixelSize = vec2(1 / 1080.f, 1 / 720.f);

layout(binding = 0) uniform sampler2D uTexAlbedo;
layout(binding = 1) uniform sampler2D uTexNormal;
layout(binding = 2) uniform sampler2D uTexPosition;

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

out vec3 outColor;

void main()
{
	vec2 texOffset = gl_FragCoord.xy * uPixelSize;

	vec4 position = texture(uTexPosition, texOffset);
	position /= position.w;

	vec4 albedoColor = texture(uTexAlbedo, texOffset);
	outColor.rgb = vec3(0); 

	vec3 normal = normalize(texture(uTexNormal, texOffset).rgb * 2 - 1);

	vec3 lightVec = uLightPosition - position.xyz;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;

	// the dot product of the normal and light direction determines how much light there is
	float NdotL = dot(normal, lightDir);
	
	// Calculate attenuation (falloff)
	// Add a small number to avoid divide by zero.
	float attenuation = 1.0 / (uLightConstantAttenuation + dist * uLightLinearAttenuation + dist * dist * uLightQuadAttenuation);

	NdotL = max(NdotL, 0.0);
	// Calculate the diffuse contribution
	outColor.rgb += albedoColor.rgb * uLightColor * NdotL * attenuation;

	// Normalized vector pointing towards the camera
	vec3 eye = normalize(position.xyz);
	vec3 reflection = reflect(lightDir, normal);
	float specularStrength = dot(reflection, eye);
	specularStrength = max(specularStrength, 0.0); // don't let it fall before zero

	// Calculate the specular contribution
	outColor.rgb += uLightColor * pow(specularStrength, 32.f) * attenuation;
}
