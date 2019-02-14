#version 330

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout(location = 0) in vec3 in_vert;
layout(location = 1) in vec2 in_uv;
layout(location = 2) in vec3 in_normal;

out vec3 pos;

void main()
{
	pos = (uView * uModel * vec4(in_vert, 1.0f)).xyz;

	gl_Position = uProj * vec4(pos, 1.0f);
}
