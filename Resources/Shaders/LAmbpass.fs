#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;

uniform float ambientMult;

void main()
{

	vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
	vec3 light = Diffuse * ambientMult;
	FragColor = vec4(light,1.0);
	
}
