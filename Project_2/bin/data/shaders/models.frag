#version 410

out vec4 outColor;
in vec3 fragNormal;
in vec2 fragUV;

in vec3 fragCamSpace;

void main()
{
	vec3 normal = normalize(fragNormal);

	float alpha = smoothstep(7.5, 5.0, length(fragCamSpace));

	outColor = vec4(normal * 0.5 + vec3(0.5), alpha);
}
