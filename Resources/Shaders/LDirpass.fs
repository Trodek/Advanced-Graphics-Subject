#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 viewPos;
uniform float intensity;

void main()
{
    vec3 position = texture(gPosition, TexCoords).xyz;
    vec3 N = texture(gNormal,TexCoords).xyz;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    
    //ambient precalculated
    
    //Calculate vectors
    vec3 L = normalize(lightDir);
    vec3 V = normalize(viewPos - position);
    
    //Half vector
    vec3 H = normalize(L+V);
	
	vec3 lColor = lightColor * intensity;
    
    vec3 diffuse = Diffuse * dot(L, N) * lColor;
    vec3 specular = dot(N, H) * Diffuse;
	specular *= Specular;
    
    vec3 lightning = diffuse + specular;
    
    FragColor = vec4(lightning,1.0);
}