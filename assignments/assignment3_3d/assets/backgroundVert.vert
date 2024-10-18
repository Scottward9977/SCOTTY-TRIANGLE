#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 ourColor;
uniform float time;

void main()
{
    float depth = sin(aPos.x * 10.0 + time) * 0.4; 
    vec3 pos = vec3(aPos.x*4, aPos.y*4, (aPos.z * 4));
    ourColor = aColor;
    float speed = 0.5; 
    TexCoord = vec2(((aTexCoord.x*8) + time * speed), (aTexCoord.y*8));
     gl_Position = vec4(pos, 1.0);
}
