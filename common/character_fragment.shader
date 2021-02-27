#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool goRight;

void main()
{
    if (goRight) {
        FragColor = texture(ourTexture, TexCoord);
    }
    else {
        FragColor = texture(ourTexture, vec2(1-TexCoord.x, TexCoord.y));
    }
}