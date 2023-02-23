#version 410

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

uniform mat4 mvp;
uniform mat4 mv;

out vec3 fragNormal;
out vec2 fragUV;

out vec3 fragCamSpace;

void main()
{
	gl_Position = mvp * vec4(position, 1.0);

	fragNormal = normal;
	fragUV = vec2(uv.x, 1.0 - uv.y);

	fragCamSpace = (mv * vec4(position, 1.0)).xyz;
}
