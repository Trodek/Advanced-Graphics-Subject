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

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
	
    // also store the per-fragment normals into the gbuffer
	vec3 texNormal = texture(normal, TexCoords).rgb;
    // transform normal vector to range [-1,1]
    texNormal = normalize(texNormal * 2.0 - 1.0);  // this normal is in tangent space
	
	vec3 T = normalize(fs_in.tangentLocal);
	vec3 B = normalize(fs_in.bitangentLocal);
	vec3 N = normalize(fs_in.normalLocal);
	mat3 TBN = mat3(T, B, N);
	
	gNormal = TBN * texNormal;

    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(albedo, TexCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(specular, TexCoords).r;
}  