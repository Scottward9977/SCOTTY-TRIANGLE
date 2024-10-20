#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "../ew/external/glad.h"
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <string> 
using namespace std;
using namespace glm;

namespace ColorNShit_ {
    class Shader
    {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const string& name, bool value) const;
        void setInt(const string& name, int value) const;
        void setFloat(const string& name, float value) const;
        void setMat4(const string& name, mat4 value) const;

    private:
        void checkCompileErrors(unsigned int shader, string type);
    };

    class Texture
    {
    public:
        void loadTextureImage(char* assetPath, bool flip, int filterMode, int wrapMode);
        void bind(unsigned int slot);
    };
}
