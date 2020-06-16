#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_viking;

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 1.0); // set alle 4 vector values to 1.0
    
}