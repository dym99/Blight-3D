#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 TexCoords;
out vec3 normal0;
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
    TexCoords = texCoord;    
	normal0 = mat3(model) * normal;
	fragPosition = (model * vec4(position, 1.0)).rgb;
}