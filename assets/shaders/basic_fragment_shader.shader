#version 330 core

in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D ourTexture1;

void main()
{
    FragColor =  texture(ourTexture1, TexCoord);
}