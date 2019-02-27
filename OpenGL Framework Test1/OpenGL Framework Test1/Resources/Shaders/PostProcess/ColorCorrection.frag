#version 420

layout(binding = 30) uniform sampler3D uTexColorGrade;

layout (binding = 0) uniform sampler2D uFinishedFrame;

in vec2 TexCoords;

out vec4 outColor;

void main()
{
    vec4 textureColor = texture(uFinishedFrame, TexCoords);

    vec3 scale = vec3((64.0 - 1.0) / 64.0);
    vec3 offset = vec3(1.0 / (2.0 * 64.0));

	outColor.rgb = texture(uTexColorGrade, scale * textureColor.rgb + offset).rgb;
	outColor.a = textureColor.a;
}