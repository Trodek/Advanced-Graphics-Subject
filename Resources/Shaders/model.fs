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

uniform sampler2D albedo;
uniform sampler2D normal;

void main()
{    
    FragColor = texture(albedo, FSIn.texCoords);
}