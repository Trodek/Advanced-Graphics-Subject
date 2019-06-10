#version 330 core
out vec4 FragColor;

uniform mat4 view;
uniform mat4 model;

in Data {
 vec3 tangentLocalspace;
 vec3 bitangentLocalspace;
 vec3 normalLocalspace;
 vec2 texCoords;
} FSIn;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

void main()
{    
    FragColor = vec4(1);
}