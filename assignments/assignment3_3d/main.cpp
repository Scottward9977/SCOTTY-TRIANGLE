#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ew/external/stb_image.h"
#include "../core/ColorsnShit/ColorsnShit.h" 

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

using namespace std;
using namespace glm;
using namespace ColorNShit_;




float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
vec3 cubePositions[] = {
     vec3(0.0f, 0.0f, 0.0f),
     vec3(2.0f, 5.0f, -15.0f),
     vec3(-1.5f, -2.2f, -2.5f),
     vec3(-3.8f, -2.0f, -12.3f),
     vec3(2.4f, -0.4f, -3.5f),
     vec3(-1.7f, 3.0f, -7.5f),
     vec3(1.3f, -2.0f, -2.5f),
     vec3(1.5f, 2.0f, -2.5f),
     vec3(1.5f, 0.2f, -1.5f),
     vec3(-1.3f, 1.0f, -1.5f)
};

// was having issues with the camera passing properly, used chat gpt to get this line so that it would pass
// i get an unresolved external singal error with out it this is the only line chat gpt gave me
Camera* Camera::camera = nullptr;

int main() {

    Camera cam(SCREEN_WIDTH, SCREEN_HEIGHT);
    cam.setCam(&cam);
   
    if (!glfwInit()) {
        printf("GLFW failed to init!");
        return 1;
    }
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
    if (window == NULL) {
        printf("GLFW failed to create window");
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("GLAD Failed to load GL headers");
        return 1;
    }


    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, cam.mouse_callback);
    glfwSetScrollCallback(window, cam.scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   


    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shaderInfo("assets/VertexShader.vert", "assets/FragmentShader.frag");
    Shader backgroundShader("assets/backgroundVert.vert", "assets/backgroundFrag.frag");

    Texture textuer;
   
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1;
    glGenTextures(1, &texture1);

    textuer.bind(texture1);
    textuer.loadTextureImage("assets/cat.png", true, GL_LINEAR, GL_REPEAT);

    shaderInfo.use();
    shaderInfo.setInt("texture1", 0);
  
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        shaderInfo.use();

        cam.processInput(window);

        float currentFrame = glfwGetTime();
        cam.deltaTime = currentFrame - cam.lastFrame;
        cam.lastFrame = currentFrame;

         mat4 view =  mat4(1.0f);

         view = lookAt(cam.cameraPos, cam.cameraPos + cam.cameraFront, cam.cameraUp);
         mat4 projection =  perspective(radians(cam.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        shaderInfo.setMat4("view", view);
        shaderInfo.setMat4("projection", projection);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        for (unsigned int i = 0; i < 10; i++) {
             mat4 model =  mat4(1.0f);
            model =  translate(model, cubePositions[i]);
            float angle = 20.0f * (i + 1);
            float timeValue = (float)glfwGetTime();
            float rotationSpeed =  radians(angle); 
            model =  rotate(model, timeValue * rotationSpeed,  vec3(1.0f, 0.3f, 0.5f));
            shaderInfo.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
    }
    

    glfwTerminate();
    return 0;
}

