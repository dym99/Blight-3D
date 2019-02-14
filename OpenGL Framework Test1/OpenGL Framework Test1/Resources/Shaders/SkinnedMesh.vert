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
	uniform uint uBoneCount;
};

void main()
{
	//vec4 skinned = 	weights.x * (uBones[groups.x+1] * vec4(position, 1.0)) +
	//				weights.y * (uBones[groups.y+1] * vec4(position, 1.0)) +
	//				weights.z * (uBones[groups.z+1] * vec4(position, 1.0)) +
	//				weights.w * (uBones[groups.w+1] * vec4(position, 1.0));

	vec4 nWeights = normalize(weights);
	
	vec4 skinned = vec4(position,1.0);
	
	if (groups.x<255 && groups.x >= 0) {
		skinned += nWeights.x * (uBones[groups.x+1] * vec4(position, 1.0));
	}
	if (groups.y<255 && groups.y >= 0) {
		skinned += nWeights.y * (uBones[groups.y+1] * vec4(position, 1.0));
	}
	if (groups.z<255 && groups.z >= 0) {
		skinned += nWeights.z * (uBones[groups.z+1] * vec4(position, 1.0));
	}
	if (groups.w<255 && groups.w >= 0) {
		skinned += nWeights.w * (uBones[groups.w+1] * vec4(position, 1.0));
	}
					
	gl_Position = uProj * uView * uModel * skinned;
    TexCoords = texCoord;    
	normal0 = mat3(uModel) * normal;
	fragPosition = (uModel * vec4(position, 1.0)).rgb;
}