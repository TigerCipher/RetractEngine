
#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragWorldPos;

out vec4 outColor;

uniform sampler2D Texture;

struct DirectionalLight
{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specularColor;
};

uniform vec3 CameraPos;
uniform float SpecularPower;
uniform vec3 AmbientLight;

uniform DirectionalLight DirLight;

void main()
{
	vec3 N = normalize(fragNormal);
	vec3 L = normalize(-DirLight.direction);
	vec3 V = normalize(CameraPos - fragWorldPos);
	vec3 R = normalize(reflect(-L, N));

	vec3 Phong = AmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = DirLight.diffuseColor * NdotL;
		vec3 Specular = DirLight.specularColor * pow(max(0.0, dot(R, V)), SpecularPower);
		Phong += Diffuse + Specular;
	}

    outColor = texture(Texture, fragTexCoord) * vec4(Phong, 1.0f);
}