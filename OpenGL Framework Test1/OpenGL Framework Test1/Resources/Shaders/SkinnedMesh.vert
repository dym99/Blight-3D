#version 330 core
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

uniform mat4[255] uBones;

void main()
{
	vec3 skinned = 	weights.x * uBones[groups.x] * position +
					weights.y * uBones[groups.y] * position +
					weights.z * uBones[groups.z] * position +
					weights.w * uBones[groups.w] * position;

	gl_Position = uProj * uView * uModel * vec4(skinned, 1.0);
    TexCoords = texCoord;    
	normal0 = mat3(uModel) * normal;
	fragPosition = (uModel * vec4(position, 1.0)).rgb;
}