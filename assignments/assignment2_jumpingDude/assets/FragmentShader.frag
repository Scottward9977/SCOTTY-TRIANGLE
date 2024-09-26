#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    // Sample the texture and output it as the fragment color
    FragColor = texture(texture1, TexCoord);

    if (FragColor.a < 0.1)
        discard;
}