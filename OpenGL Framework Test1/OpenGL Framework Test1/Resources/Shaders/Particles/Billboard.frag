#version 420

uniform sampler2D uTex;

in vec2 texcoord;
in float frag_alpha;

out vec4 FragColor;

void main()
{
    FragColor = texture(uTex, texcoord).rgba;
    FragColor.a *= frag_alpha;
}