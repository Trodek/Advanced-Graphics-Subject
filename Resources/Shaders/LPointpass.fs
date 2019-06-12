#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

void main()
{
	vec3 position = texture(gPosition, TexCoords).xyz;
	vec3 normal = texture(gNormal,TexCoords).xyz;
	vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
	
	//ambient precalculated
	
	
}
