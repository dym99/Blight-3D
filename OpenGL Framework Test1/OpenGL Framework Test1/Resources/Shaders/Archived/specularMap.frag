#version 330 core
#extension GL_ARB_shading_language_420pack: enable

out vec4 FragColor;

struct Material {
	sampler2D specularTex;
};

in vec2 TexCoords;

uniform Material material;

void main()
{    	
	FragColor = vec4(vec3(texture(material.specularTex, TexCoords)), 1.0f);
}