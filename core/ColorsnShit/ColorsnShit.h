#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "../ew/external/glad.h"
#include <string> 
using namespace std;

namespace SHADER_ {
    class Shader
    {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const string& name, bool value) const;
        void setInt(const string& name, int value) const;
        void setFloat(const string& name, float value) const;

    private:
        void checkCompileErrors(unsigned int shader, string type);
    };
   
}
