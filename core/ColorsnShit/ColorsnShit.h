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

    class Camera {
        public:

            Camera(int SCREEN_WIDTH_, int SCREEN_HEIGHT_);
            void setCam(Camera* cam);

            void processInput(GLFWwindow* window);
            static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
            static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

            vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
            vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
            vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

            float deltaTime = 0.0f;
            float lastFrame = 0.0f;
            float fov = 45.0f;
            bool firstMouse = true;
            float camYaw = -90.0f;
            float camPitch = 0.0f;
            float lastX = SCREEN_WIDTH / 2.0;
            float lastY = SCREEN_HEIGHT / 2.0;
            
    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;

        static Camera* camera;
    };
}
