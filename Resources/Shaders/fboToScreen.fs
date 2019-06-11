#version 330 core

in vec2 TexCoord;

uniform sampler2D colorTex;

out vec4 outColor;

void main()
{
 outColor = vec4(texture(colorTex, TexCoord).rgb, 1.0);
}