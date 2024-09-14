#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
out vec4 Color;
uniform float editLocationy; 
void main()
{
   Color = aColor;
   gl_Position = vec4(aPos.x, aPos.y+cos(editLocationy*2+aPos.x)/4, aPos.z, 1.0);
};
