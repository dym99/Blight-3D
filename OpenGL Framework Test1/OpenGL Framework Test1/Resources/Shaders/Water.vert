#version 420 

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

layout(binding = 5)uniform sampler2D uWaveTex;
uniform float uTime = 0.f;

out vec2 TexCoords;
out vec3 normal0;
out vec3 fragPosition;
out vec3 tangent0;
out vec3 bitangent0;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    TexCoords = texCoord;
	float height = texture(uWaveTex, texCoord + (vec2(0.5f, 0.5f) * (uTime * 0.25))).r;
	height = height;
	vec3 tempPos = position;
	tempPos.y += height;
	normal0 = mat3(uModel) * normal;
	fragPosition = (uModel * vec4(tempPos, 1.0)).rgb;
	gl_Position = uProj * uView * uModel * vec4(tempPos, 1.0);
}