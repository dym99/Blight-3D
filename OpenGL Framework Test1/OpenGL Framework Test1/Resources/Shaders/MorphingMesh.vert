#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

layout (location = 7) in vec3 lastPos;
layout (location = 8) in vec3 lastNorm;

out vec2 TexCoords;
out vec3 normal0;
out vec3 fragPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

uniform float uT;

void main()
{
	vec3 pos = mix(lastPos, position, uT);
	gl_Position = uProj * uView * uModel * vec4(pos, 1.0);
    TexCoords = texCoord;    
	normal0 = mat3(uModel) * mix(lastNorm, normal, uT);
	fragPosition = (uModel * vec4(pos, 1.0)).rgb;
}