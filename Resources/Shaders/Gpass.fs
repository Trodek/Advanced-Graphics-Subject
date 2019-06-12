#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;

in Data
{
	vec3 tangentLocal;
	vec3 bitangentLocal;
	vec3 normalLocal;
} fs_in;

uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D specular;

uniform mat4 model;
uniform mat4 view;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
	
    vec3 texNormal = texture(normal, TexCoords).xyz * 2.0 - vec3(1.0);  // this normal is in tangent space
	
	vec3 T = normalize(fs_in.tangentLocal);
	vec3 B = normalize(fs_in.bitangentLocal);
	vec3 N = normalize(fs_in.normalLocal);
	mat3 TBN = mat3(T, B, N);
	
	vec3 localSpaceNormal = TBN * texNormal;
	gNormal = normalize(model * vec4(localSpaceNormal,0.0)).xyz;

    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(albedo, TexCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(specular, TexCoords).r;
}  