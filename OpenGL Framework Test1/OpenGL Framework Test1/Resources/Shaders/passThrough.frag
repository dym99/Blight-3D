#version 330 core

out vec4 FragColor;

struct Material {
	sampler2D diffuseTex;
	sampler2D specularTex;
	sampler2D normalTex;
	
	float shininess;
};

struct Light {
	vec4 position;
	vec3 ambience;
	vec3 diffuse;
	vec3 specular;	
	
	float shininess;
	
	float constant;
	float linear;
	float quadratic;
};

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

uniform Light light;
uniform Material material;
uniform bool hasNormMap;

void main() 
{
	FragColor.rgb = light.ambience;
	
	//Account for interpolation
	vec3 normal = normalize(normal0);
	
	vec3 lightVec = light.position.xyz - fragPosition;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;
	
	float NdotL = dot(normal, lightDir);
	
	if (NdotL > 0.0)
	{
		//Light affects this surface
		float attentuation = 1.0 / (light.constant + (light.linear * dist) + (light.quadratic * (dist * dist)));
		
		//Calculate diffuse
		FragColor.rgb += light.diffuse * NdotL * attentuation;
		
		//Blinn-Phong bullshit
		float NdotHV = max(dot(normal, normalize(lightDir + normalize(-fragPosition))), 0.0);
		
		//Calculate specular
		FragColor.rgb += light.specular * pow(NdotHV, light.shininess) * attentuation;
	}
	
	vec4 textureColor = texture(material.diffuseTex, TexCoords);
	FragColor.rgb *= textureColor.rgb;
	FragColor.a = textureColor.a;
}