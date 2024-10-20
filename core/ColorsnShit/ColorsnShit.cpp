#include "ColorsnShit.h"
#include "../ew/external/stb_image.h"
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
using namespace glm;
     ColorNShit_:: Shader  :: Shader(const char* vertexPath, const char* fragmentPath)
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
void ColorNShit_:: Shader  :: use()
{
    glUseProgram(ID);
}
void ColorNShit_:: Shader  :: setBool(const string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void ColorNShit_:: Shader  :: setInt(const string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void ColorNShit_:: Shader  :: setFloat(const string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void ColorNShit_:: Shader  :: setMat4(const string& name, mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value_ptr(value));
}
void ColorNShit_:: Shader  :: checkCompileErrors(unsigned int shader, string type)
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

void ColorNShit_:: Texture :: loadTextureImage(char* assetPath, bool flip, int filterMode, int wrapMode)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
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
void ColorNShit_:: Texture :: bind(unsigned int slot)
{
    glBindTexture(GL_TEXTURE_2D, slot);
}

     ColorNShit_:: Camera  :: Camera(int SCREEN_WIDTH_, int SCREEN_HEIGHT_)
{
    SCREEN_WIDTH = SCREEN_WIDTH_;
    SCREEN_HEIGHT = SCREEN_HEIGHT_;
}
void ColorNShit_:: Camera  :: setCam(Camera* cam)
{
    camera = cam;
}
void ColorNShit_:: Camera  :: processInput(GLFWwindow* window) {
    const float cameraSpeed = 5.0 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraFront * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;

    }

};
void ColorNShit_:: Camera  :: mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (camera->firstMouse) {
        camera->lastX = xpos;
        camera->lastY = ypos;
        camera->firstMouse = false;
    }

    float xoffset = xpos - camera->lastX;
    float yoffset = camera->lastY - ypos;
    camera->lastX = xpos;
    camera->lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->camYaw += xoffset;
    camera->camPitch += yoffset;

    if (camera->camPitch > 89.0f)
        camera->camPitch = 89.0f;
    if (camera->camPitch < -89.0f)
        camera->camPitch = -89.0f;

    vec3 direction;
    direction.x = cos(radians(camera->camYaw)) * cos(radians(camera->camPitch));
    direction.y = sin(radians(camera->camPitch));
    direction.z = sin(radians(camera->camYaw)) * cos(radians(camera->camPitch));
    camera->cameraFront = normalize(direction);
}
void ColorNShit_:: Camera  :: scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera->fov -= static_cast<float>(yoffset);
    if (camera->fov < 1.0f)
        camera->fov = 1.0f;
    if (camera->fov > 45.0f)
        camera->fov = 45.0f;
}




