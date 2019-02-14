#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 TexCoords;
out vec3 normal0;
out vec3 fragPosition;


out mat3 TBN;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
	gl_Position = uProj * uView * uModel * vec4(position, 1.0);
    TexCoords = texCoord;
	normal0 = mat3(uModel) * normal;
	
	vec3 bitangent = cross(normal, tangent);
	
	//TBN matrix calculation
	vec3 T = normalize(vec3(uView * uModel * vec4(tangent, 0.0)));
	vec3 B = normalize(vec3(uView * uModel * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(uView * uModel * vec4(normal, 0.0)));
	TBN = mat3(T, B, N);
	
	fragPosition = (uModel * vec4(position, 1.0)).rgb;
}