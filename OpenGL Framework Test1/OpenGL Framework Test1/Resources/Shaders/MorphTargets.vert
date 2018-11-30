#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

layout (location = 5) in vec3 target;
layout (location = 6) in vec3 handleA;
layout (location = 7) in vec3 handleB;

out vec2 TexCoords;
out vec3 normal0;
out vec3 fragPosition;

uniform float uInterp = 0;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

vec3 catmull(vec3 p0, vec3 p1, vec3 p2, vec3 p3, float t)
{
	return 0.5f *
		(t * t * t * (     -p0 + 3.0f*p1 - 3.0f*p2 + p3 ) +
		     t * t * ( 2.0f*p0 - 5.0f*p1 + 4.0f*p2 - p3 ) +
		         t * (     -p0			 +      p2      ) +
				     (			 2.0f*p1		        ));
}


void main()
{
	vec4 pos = uProj * uView * uModel * vec4(catmull(handleA,position,target,handleB,1.0-uInterp), 1.0);
	gl_Position = pos;//uProj * uView * uModel * vec4(position, 1.0);
    TexCoords = texCoord;    
	normal0 = mat3(uModel) * normal;
	fragPosition = (uModel * pos).rgb;
}