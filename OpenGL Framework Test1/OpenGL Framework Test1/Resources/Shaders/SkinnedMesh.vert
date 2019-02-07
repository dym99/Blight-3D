#version 420
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

layout (location = 5) in ivec4 groups;
layout (location = 6) in vec4 weights;

out vec2 TexCoords;
out vec3 normal0;
out vec3 fragPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout (std140, binding = 1) uniform bones
{
	uniform mat4[255] uBones;
};

void main()
{
	vec4 skinned = 	weights.x * uBones[groups.x] * vec4(position, 1.0) +
					weights.y * uBones[groups.y] * vec4(position, 1.0) +
					weights.z * uBones[groups.z] * vec4(position, 1.0) +
					weights.w * uBones[groups.w] * vec4(position, 1.0);

	gl_Position = uProj * uView * uModel * skinned;
    TexCoords = texCoord;    
	normal0 = mat3(uModel) * normal;
	fragPosition = (uModel * vec4(position, 1.0)).rgb;
}