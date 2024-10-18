#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D bgTexture1;
uniform sampler2D bgTexture2;

void main()
{
    vec4 brickColor = texture(bgTexture1, TexCoord);
    brickColor.a *= 2.0f;
    vec4 foodColor = texture(bgTexture2, TexCoord);
    foodColor.a = .8;
    FragColor = mix(brickColor, foodColor, 0.5f);
    FragColor.a = 1.0;
    
}
