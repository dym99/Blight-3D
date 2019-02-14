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
	vec4(-0.963056028, 1.500000060, -0.0385486856, 0.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.6, 0.2),
	32.0,
	1.0,
	0.1,
	0.01
);

uniform Light light2 = Light(
	vec4(-0.211108208, 1.500000060, 11.6930666, 0.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.2, 0.6, 0.6),
	32.0,
	1.0,
	0.1,
	0.01
);

uniform Material material;

void calculatePointLight(Light lightyBoi)
{
	//Account for interpolation
	vec3 normal = normalize(normal0);
	
	vec3 lightVec = lightyBoi.position.xyz - fragPosition;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;
	
	float NdotL = dot(normal, lightDir);
	
	if (NdotL > 0.0)
	{
		//Light affects this surface
		float attentuation = 0.5 / (lightyBoi.constant + (lightyBoi.linear * dist) + (lightyBoi.quadratic * (dist * dist)));
		
		//Calculate diffuse
		FragColor.rgb += lightyBoi.diffuse * NdotL * attentuation;
		
		//Blinn-Phong bullshit
		vec3 eye = normalize(-fragPosition);
		vec3 reflection = normalize(reflect(-lightDir, normal));
		float specularStrength = dot(reflection, eye);
		specularStrength = max(specularStrength, 0.0);

		//Calculate specular
		//FragColor.rgb += lightyBoi.diffuse * pow(specularStrength, lightyBoi.shininess) * attentuation;
	}
}

void main() 
{
	vec4 textureColor = texture(material.diffuseTex, TexCoords);
	FragColor.rgb = textureColor.rgb * light.ambience;
	FragColor.a = textureColor.a;

	calculatePointLight(light2);
	calculatePointLight(light);
}