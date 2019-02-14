#version 420

uniform sampler2D uTex; //Source image
uniform float uThreshold;

out vec3 FragColor;

in vec2 TexCoords;

void main() 
{
	vec3 color = texture(uTex, TexCoords).rgb;
	
	float luminance = (color.r + color.g + color.b) / 3.0;
	
	if (luminance > uThreshold) 
	{
		FragColor = color;
	}
	else 
	{
		FragColor = vec3(0.0, 0.0, 0.0);
	}

}