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
	
	float shininess;
	
	float constant;
	float linear;
	float quadratic;
};

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

uniform Light light = Light(
	vec4(0.0, 0.0, 0.0, 0.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.7, 0.7, 0.7),
	32.0,
	1.0,
	0.1,
	0.01
);
uniform Material material;

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
		vec3 eye = normalize(-fragPosition);
		vec3 reflection = reflect(-lightDir, normal);
		float specularStrength = dot(reflection, eye);
		specularStrength = max(specularStrength, 0.0);
		
		//Calculate specular
		FragColor.rgb += light.diffuse * pow(specularStrength, light.shininess) * attentuation;
	}
	
	vec4 textureColor = texture(material.diffuseTex, TexCoords);
	FragColor.rgb *= textureColor.rgb;
	FragColor.a = textureColor.a;
}