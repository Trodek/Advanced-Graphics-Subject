#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gAlbedoSpec;
uniform sampler2D ssao;

uniform bool useSSAO;

uniform float ambientMult;

void main()
{

	vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
	vec3 light = Diffuse * ambientMult;
	if(useSSAO)
	{
		float ssaoValue = texture(ssao, TexCoords).r;
		light*=ssaoValue;
	}
	FragColor = vec4(light,1.0);
	
}
