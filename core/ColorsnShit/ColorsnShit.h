#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "../ew/external/glad.h"
#include <string> 
using namespace std;

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

    private:
        void checkCompileErrors(unsigned int shader, string type);
    };

    class Texture
    {
    public:
        void loadTextureImage(char* assetPath, bool flip, int filterMode, int wrapMode);
        void bind(unsigned int slot);
    };
 
    class Camera
    {
     template <typename T >;
     public:
        Camera(int SCREEN_WIDTH_, int SCREEN_HEIGHT_);

        void processInput(GLFWwindow* window);

        void mouse_callback(GLFWwindow* window, double xpos, double ypos);

        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
        vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
        vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        float fov = 45.0f;

    private:

        const int SCREEN_WIDTH = 1920;
        const int SCREEN_HEIGHT = 1080;

        bool firstMouse = true;
        float camYaw = -90.0f;
        float camPitch = 0.0f;
        float lastX = SCREEN_WIDTH / 2.0;
        float lastY = SCREEN_HEIGHT / 2.0;
    };
   
}
