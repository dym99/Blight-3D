#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform float windowWidth = 800.0;
uniform float windowHeight = 600.0;
float normInnerRadius = 200.0;
float normOuterRadius = 300.0;
uniform float uTime;

uniform sampler2D uTex;

vec3 backgroundColor = vec3(0.0, 0.05, 0.1);

float invLerp(const float v, const float v0, const float v1)
{
	return ((v - v0) / (v1 - v0));
}

void main() 
{
	vec4 source = texture(uTex, TexCoords);

	vec2 centerVector = vec2(windowWidth/2.0, windowHeight/2.0);
	vec2 fixedTexCoords = vec2(mix(0.0, windowWidth, TexCoords.x), mix(0.0, windowHeight, TexCoords.y));
	
	vec2 vectorToCenter = centerVector - fixedTexCoords;
	
	float innerRadius = (0.5 *sin(uTime) + 0.8) * normInnerRadius;
	float outerRadius = (0.5 * sin(uTime) + 0.9) * normOuterRadius;
	
	if (length(vectorToCenter) < innerRadius + 1.0 && length(vectorToCenter) > innerRadius - 1.0)
	{
		//Creates a line where the inner radius is
		FragColor.rgb = vec3(1.0, 0.0, 0.0);
	}
	else if (length(vectorToCenter) < innerRadius)
	{
		FragColor.rgb = source.rgb;
	}
	else if (length(vectorToCenter) < outerRadius + 1.0 && length(vectorToCenter) > outerRadius - 1.0)
	{
		//Creates a line where the outer radius is
		FragColor.rgb = vec3(0.0, 1.0, 0.0);
	}
	else if (length(vectorToCenter) > innerRadius && length(vectorToCenter) < outerRadius)
	{
		//if the current coordinate is between the inner and outer cutoff
		//it will lerp from the source color towards the color of your choise
		float tVal = invLerp(length(vectorToCenter), innerRadius, outerRadius);
		
		FragColor.rgb = mix(source.rgb, backgroundColor, tVal);
	}
	else 
	{
		FragColor.rgb = backgroundColor;
	}
	
	FragColor.a = 1.0;
}