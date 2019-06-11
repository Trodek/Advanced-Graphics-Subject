#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 FragPos;
out vec2 TexCoords;

out Data
{
	vec3 tangentLocal;
	vec3 bitangentLocal;
	vec3 normalLocal;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = worldPos.xyz; 
    TexCoords = aTexCoords;
    
	vs_out.tangentLocal = aTangent;
	vs_out.bitangentLocal = aBitangent;
	vs_out.normalLocal = aNormal;

    gl_Position = projection * view * worldPos;
}