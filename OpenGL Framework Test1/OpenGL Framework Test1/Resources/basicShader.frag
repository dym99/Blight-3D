#version 330 core
#extension GL_ARB_shading_language_420pack: enable

out vec4 FragColor;

struct Material {
	sampler2D diffuseTex;
	sampler2D specularTex;
	sampler2D normalTex;
};

in vec2 TexCoords;

uniform Material material;


void main()
{    
	// //Ambience stuffs
	// vec3 ambience = vec3(texture(material.diffuseTex, TexCoords));
	
	// //Diffusal stuffs
	// vec3 diffuse = vec3(texture(material.diffuseTex, TexCoords));
	
	// //Specular stuffs
	// vec3 specular = vec3(texture(material.specularTex, TexCoords));
	
	FragColor = vec4(0.5f, 1.0f, 0.3f, 1.0f);
}