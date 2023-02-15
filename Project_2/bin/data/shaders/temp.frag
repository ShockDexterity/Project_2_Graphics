#version 410

out vec4 outColor;
in vec3 fragNormal;
in vec2 fragUV;

void main()
{
	vec3 normal = normalize(fragNormal);
	outColor = vec4(normal * 0.5 + vec3(1.0), 1.0);
}