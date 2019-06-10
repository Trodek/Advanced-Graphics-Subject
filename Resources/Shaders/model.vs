#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out Data
{
 vec3 tangentLocalspace;
 vec3 bitangentLocalspace;
 vec3 normalLocalspace;
 vec2 texCoords;
} VSOut;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    VSOut.tangentLocalspace = aTangent;
	VSOut.bitangentLocalspace = aBitangent;
	VSOut.normalLocalspace = aNormal;
	VSOut.texCoords = aTexCoords;

 
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}