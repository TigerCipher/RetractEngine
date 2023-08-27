
#version 330

uniform mat4 WorldTransform;
uniform mat4 ViewProj;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;


out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragWorldPos;

void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	pos = pos * WorldTransform;
	fragWorldPos = pos.xyz;
	gl_Position = pos * ViewProj;

	fragNormal = (vec4(inNormal, 0.0f) * WorldTransform).xyz;

	fragTexCoord = inTexCoord;
}