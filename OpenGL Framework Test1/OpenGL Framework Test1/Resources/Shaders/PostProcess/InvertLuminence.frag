#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D uTex;
uniform float uTime;

vec3 rgbToHSV(vec3 rgb)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(rgb.bg, K.wz), vec4(rgb.gb, K.xy), step(rgb.b, rgb.g));
    vec4 q = mix(vec4(p.xyw, rgb.r), vec4(rgb.r, p.yzx), step(p.x  , rgb.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsvToRGB(vec3 hsv)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(hsv.xxx + K.xyz) * 6.0 - K.www);
    return hsv.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), hsv.y);
}

void main() 
{
	vec4 textureColor = texture(uTex, TexCoords);
	vec3 invertTexture = vec3(1.0) - textureColor.rgb;

    vec3 hueSaturationValue = rgbToHSV(invertTexture);

    float hueShift = hueSaturationValue.r + 0.5;

    hueSaturationValue.r = hueShift;

    invertTexture = hsvToRGB(hueSaturationValue);

	FragColor.rgb = vec3(invertTexture);
	FragColor.a = 1.0f;
}