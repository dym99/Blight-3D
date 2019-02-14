#version 330 core
#extension GL_ARB_shading_language_420pack: enable

out vec4 FragColor;

struct Material {
	sampler2D diffuseTex;
	sampler2D specularTex;
	sampler2D normalTex;
	
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambience;
	vec3 diffuse;
	vec3 specular;	
	
	float constant;
	float linear;
	float quadratic;
};

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;
uniform vec3 objectColor;
uniform int hasNormMap;
vec3 normals;


void main()
{    
	//Normal stuffs
	if (hasNormMap == 1) {
		normals = texture(material.normalTex, TexCoords).rgb;
		normals = normalize(normals * 2.0 - 1.0);
	}
	else {
		normals = normal0;
	}
	//Distance stuffs
	 float distance = length(light.position - fragPosition);
	 float attenuation = 1.0 / (light.constant + (light.linear * distance) + (light.quadratic * (distance * distance)));
	
	 //Ambience stuffs
	 vec3 ambience = light.ambience * vec3(texture(material.diffuseTex, TexCoords));
	 ambience = ambience * attenuation;

	 //Diffusal stuffs
	 vec3 norm = normalize(normals);
	 vec3 lightDirection = normalize(light.position - fragPosition);
	 float diff = max(dot(norm, lightDirection), 0.0);
	 vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTex, TexCoords));
	 diffuse = diffuse * attenuation;

	 //Specular stuffs
	 vec3 viewDirection = normalize(viewPosition - fragPosition);
	 vec3 reflectionDirection = reflect(-lightDirection, norm);
	 float spec = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);
	 vec3 specular = light.specular * spec * vec3(texture(material.specularTex, TexCoords));
	 specular = specular * attenuation;
	
	vec3 result = (ambience + diffuse + specular);
	FragColor = vec4(result, 1.0f);
}