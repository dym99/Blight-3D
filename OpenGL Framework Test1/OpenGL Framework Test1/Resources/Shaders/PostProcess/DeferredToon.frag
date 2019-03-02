#version 420

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

struct DirLight {
	vec4 position;
	vec3 ambience;
	vec3 color;
	vec3 direction;

	float shininess;
};

in vec2 TexCoords;

uniform DirLight directionLight =  {
	vec4(0.0, 0.0, 0.0, 0.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.5, 0.5, 0.5),
	vec3(-0.3, 0.95, 0.0),
	32.0,
};

uniform Light light[48] = { 
	Light(
	vec4(-44.633648, 0.500000, 5.672839, 0.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-44.090328, 0.500000, -6.341741, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-26.775608, 0.500000, 9.505545, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-26.590355, 0.500000, -6.158344, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-20.662336, 0.500000, 13.387436, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-19.626617, 0.500000, -14.462436, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-2.028160, 0.500000, -20.524620, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-2.043056, 0.500000, -27.361380, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-8.776593, 0.500000, -35.394379, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(8.868602, 0.500000, -35.207016, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-13.200074, 0.500000, -40.927586, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-20.744389, 0.500000, -41.195820, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-19.371952, 0.500000, -49.894417, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-0.732033, 0.500000, -45.884380, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-0.732033, 0.500000, -52.130676, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(19.899551, 0.500000, -50.202072, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(19.737904, 0.500000, -42.220512, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(14.181462, 0.500000, -42.111050, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(18.004396, 0.500000, -20.646599, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(12.796072, 0.500000, -20.646599, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(2.245983, 0.500000, -20.821217, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(32.002598, 0.500000, -1.914401, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(32.002598, 0.500000, 1.469780, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(28.118650, 0.500000, 1.469780, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(28.118650, 0.500000, -1.914401, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(28.118650, 0.500000, -5.344815, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(32.002598, 0.500000, -5.344815, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(28.118650, 0.500000, 5.344815, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(32.002598, 0.500000, 5.344815, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(61.330212, 0.500000, -6.199307, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(61.330212, 0.500000, 6.199307, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(53.128838, 0.500000, 0.000000, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(43.614162, 0.500000, 13.970689, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(43.614162, 0.500000, -13.970689, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(13.018315, 0.500000, 45.338821, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(16.903147, 0.500000, 49.881462, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-13.018315, 0.500000, 45.338821, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-16.903147, 0.500000, 49.881462, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(21.690195, 0.500000, 38.013233, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-21.690195, 0.500000, 38.013233, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-2.287966, 0.500000, 44.972633, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(2.287966, 0.500000, 44.972633, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(13.638598, 0.500000, 28.890642, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(16.099287, 0.500000, 25.178598, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-13.638598, 0.500000, 28.890642, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-16.099287, 0.500000, 25.178598, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(9.315192, 0.500000, 20.322336, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
	Light(
	vec4(-9.315192, 0.500000, 20.322336, 1.0),
	vec3(0.15, 0.15, 0.15),
	vec3(0.6, 0.3, 0.1),
	32.0,
	1.0,
	0.1,
	0.01
	),
};

layout(binding = 0) uniform sampler2D uScene;
layout(binding = 1) uniform sampler2D uNormalMap;
layout(binding = 2) uniform sampler2D uPositionMap;
layout(binding = 3) uniform sampler2D uTexToonRamp;

uniform Material material;

void calculatePointLight(Light lightyBoi, vec3 fragPosition, vec3 normal0, vec4 _textureColor)
{
	//Account for interpolation
	vec3 normal = normalize(normal0);
	
	vec3 lightVec = lightyBoi.position.xyz - fragPosition;
	float dist = length(lightVec);
	vec3 lightDir = lightVec / dist;
	
	float NdotL = dot(normal, lightDir);
	
	{
		//Light affects this surface
		float attentuation = 0.5 / (lightyBoi.constant + (lightyBoi.linear * dist) + (lightyBoi.quadratic * (dist * dist)));
		
		//Calculate diffuse
		FragColor.rgb += (lightyBoi.diffuse * 2.0)* texture(uTexToonRamp, vec2(NdotL, 0.5)).rgb *  attentuation * vec3(_textureColor * vec4(0.5));
		
		//Blinn-Phong bullshit
		vec3 eye = normalize(-fragPosition);
		vec3 reflection = normalize(reflect(-lightDir, normal));
		float specularStrength = dot(reflection, eye);
		specularStrength = max(specularStrength, 0.0);

		//Calculate specular
		//FragColor.rgb += lightyBoi.diffuse * pow(specularStrength, lightyBoi.shininess) * attentuation;
	}
}

void calculateDirectionalLight(DirLight lightyBoi, vec3 fragPosition, vec3 normal0, vec4 _textureColor)
{
	//Account for interpolation
	vec3 normal = normalize(normal0);

		// the dot product of the normal and light direction determines how much light there is
	float NdotL = dot(normal, lightyBoi.direction);
	
	// Calculate attenuation (falloff)
	// Add a small number to avoid divide by zero

	NdotL = max(NdotL, 0.0);
	// Calculate the diffuse contribution
	FragColor.rgb += (lightyBoi.color * NdotL) * vec3(_textureColor * vec4(0.5));
}

void main() 
{
	vec4 textureColor = texture(uScene, TexCoords);
    vec3 normal0 = texture(uNormalMap, TexCoords).xyz * 2.0 - 1.0;

    vec3 fragPosition = texture(uPositionMap, TexCoords).xyz;
	FragColor.rgb = textureColor.rgb * light[0].ambience;
	FragColor.a = textureColor.a;

	//calculatePointLight(light[47], fragPosition, normal0, textureColor);
	//calculatePointLight(light[46], fragPosition, normal0, textureColor);
	//calculatePointLight(light[45], fragPosition, normal0, textureColor);
	//calculatePointLight(light[44], fragPosition, normal0, textureColor);
	//calculatePointLight(light[43], fragPosition, normal0, textureColor);
	//calculatePointLight(light[42], fragPosition, normal0, textureColor);
	//calculatePointLight(light[41], fragPosition, normal0, textureColor);
	//calculatePointLight(light[40], fragPosition, normal0, textureColor);
	//calculatePointLight(light[39], fragPosition, normal0, textureColor);
	//calculatePointLight(light[38], fragPosition, normal0, textureColor);
	//calculatePointLight(light[37], fragPosition, normal0, textureColor);
	//calculatePointLight(light[36], fragPosition, normal0, textureColor);
	//calculatePointLight(light[35], fragPosition, normal0, textureColor);
	//calculatePointLight(light[34], fragPosition, normal0, textureColor);
	//calculatePointLight(light[33], fragPosition, normal0, textureColor);
	//calculatePointLight(light[32], fragPosition, normal0, textureColor);
	//calculatePointLight(light[31], fragPosition, normal0, textureColor);
	//calculatePointLight(light[30], fragPosition, normal0, textureColor);
	//calculatePointLight(light[29], fragPosition, normal0, textureColor);
	//calculatePointLight(light[28], fragPosition, normal0, textureColor);
	//calculatePointLight(light[27], fragPosition, normal0, textureColor);
	//calculatePointLight(light[26], fragPosition, normal0, textureColor);
	//calculatePointLight(light[25], fragPosition, normal0, textureColor);
	//calculatePointLight(light[24], fragPosition, normal0, textureColor);
	//calculatePointLight(light[23], fragPosition, normal0, textureColor);
	//calculatePointLight(light[22], fragPosition, normal0, textureColor);
	//calculatePointLight(light[21], fragPosition, normal0, textureColor);
	//calculatePointLight(light[20], fragPosition, normal0, textureColor);
	//calculatePointLight(light[19], fragPosition, normal0, textureColor);
	//calculatePointLight(light[18], fragPosition, normal0, textureColor);
	//calculatePointLight(light[17], fragPosition, normal0, textureColor);
	//calculatePointLight(light[16], fragPosition, normal0, textureColor);
	//calculatePointLight(light[15], fragPosition, normal0, textureColor);
	//calculatePointLight(light[14], fragPosition, normal0, textureColor);
	//calculatePointLight(light[13], fragPosition, normal0, textureColor);
	//calculatePointLight(light[12], fragPosition, normal0, textureColor);
	//calculatePointLight(light[11], fragPosition, normal0, textureColor);
	//calculatePointLight(light[10], fragPosition, normal0, textureColor);
	//calculatePointLight(light[9], fragPosition, normal0, textureColor);
	//calculatePointLight(light[8], fragPosition, normal0, textureColor);
	//calculatePointLight(light[7], fragPosition, normal0, textureColor);
	//calculatePointLight(light[6], fragPosition, normal0, textureColor);
	//calculatePointLight(light[5], fragPosition, normal0, textureColor);
	//calculatePointLight(light[4], fragPosition, normal0, textureColor);
	//calculatePointLight(light[3], fragPosition, normal0, textureColor);
	//calculatePointLight(light[2], fragPosition, normal0, textureColor);
	//calculatePointLight(light[0], fragPosition, normal0, textureColor);
	calculatePointLight(light[1], fragPosition, normal0, textureColor);
	//calculateDirectionalLight(directionLight, fragPosition, normal0, textureColor);
}