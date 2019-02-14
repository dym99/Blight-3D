#version 330 core
#extension GL_ARB_shading_language_420pack: enable

out vec4 FragColor;

struct Material {
	sampler2D specularTex;
	sampler2D normalTex;
};

in vec2 TexCoords;
in vec3 normal0;

uniform Material material;
uniform int hasNormMap;
vec3 normals;


void main()
{    
	//Normal stuffs
	if (hasNormMap == 1) {
		normals = texture(material.normalTex, TexCoords).rgb;
		normals = normalize(normals * 2.0 - 1.0);
	}
	else {
		normals = normal0;
	}
	
	FragColor = vec4(normals + vec3(texture(material.specularTex, TexCoords)), 1.0f);
}