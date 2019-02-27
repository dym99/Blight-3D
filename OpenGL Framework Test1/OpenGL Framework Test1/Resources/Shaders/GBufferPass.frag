#version 420

layout(binding = 0)uniform sampler2D uTex;
uniform vec3 colorTint;

in vec2 TexCoords;
in vec3 normal0;
in vec3 fragPosition;

layout(location = 0) out vec4 outColors;
layout(location = 1) out vec3 outNormals;
layout(location = 2) out vec3 outPositions;


vec4 Slerp(vec4 p0, vec4 p1, float t)
{
  float dotp = dot(normalize(p0), normalize(p1));
  if ((dotp > 0.9999) || (dotp<-0.9999))
  {
    if (t<=0.5)
      return p0;
    return p1;
  }
  float theta = acos(dotp);
  vec4 P = ((p0*sin((1-t)*theta) + p1*sin(t*theta)) / sin(theta));
  P.w = 1;
  return P;
}

void main()
{
    //Standard color output
    outColors.rgb = texture(uTex, TexCoords).rgb;
    outColors.a = 1.0;

    //Pack normals
    //in -> [-1, 1]
    //out -> [0, 1]
    outNormals = normalize(normal0) * 0.5 + 0.5;

    //View space positions
    outPositions = fragPosition;
}