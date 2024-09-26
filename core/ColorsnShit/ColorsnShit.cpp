#include "ColorsnShit.h"
#include "TextuerinShit.h"
#include "../ew/external/stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
SHADER_ :: Shader :: Shader(const char* vertexPath, const char* fragmentPath)
    {
       
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;

        vShaderFile.exceptions(ifstream::failbit |  ifstream::badbit);
        fShaderFile.exceptions( ifstream::failbit |  ifstream::badbit);
        try
        {
          
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
             stringstream vShaderStream, fShaderStream;
           
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            
            vShaderFile.close();
            fShaderFile.close();
        
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch ( ifstream::failure& e)
        {
             cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() <<  endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
   
        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
 
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
void SHADER_:: Shader :: use()
{
    glUseProgram(ID);
}
void SHADER_::Shader :: setBool(const string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void SHADER_:: Shader :: setInt(const string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void SHADER_:: Shader :: setFloat(const string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void SHADER_:: Shader :: checkCompileErrors(unsigned int shader, string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
             cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " <<  endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
             cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " <<  endl;
        }
    }
}

void SHADER_::Texture::loadTextureImage(char* assetPath, bool flip)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char* data = stbi_load(assetPath, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;// this line is chatgpt becouse i couldn't get it to load properly 
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}