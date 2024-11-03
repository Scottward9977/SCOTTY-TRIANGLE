#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
using namespace ImGui;




float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

vec3 cubePositions[] = {
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f),
     vec3(0.0f, 0.0f, 0.0f)
};

size_t arraySize = sizeof(cubePositions) / sizeof(cubePositions[0]);

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
    IMGUI_CHECKVERSION();
    CreateContext();

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

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    Shader shaderInfo("assets/VertexShader.vert", "assets/FragmentShader.frag");
    Shader lightCube ("assets/lightcube.vert", "assets/lightcube.frag");
    Texture textuer;
    TheredObject cubes(cubePositions, shaderInfo,cam, arraySize);
   

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);


    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    textuer.bind(texture1);
    textuer.loadTextureImage("assets/wall.jpg", true, GL_LINEAR, GL_REPEAT);

    shaderInfo.use();
    vec3 lightPos = vec3(5.2f, 7.0f, 2.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;
    float diffuseStrength = 0.1;
    float specularStrength = 0.1;
    float ShininessStrength = 2;
    shaderInfo.setInt("texture1", 0);
  
    while (!glfwWindowShouldClose(window)&& cam.exit) {

        
        glfwPollEvents();
        cam.processInput(window);


        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        NewFrame();


        ImGuiIO& io = ImGui::GetIO();
        if (!cam.clickedOn) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            io.MousePos = ImVec2((float)xpos, (float)ypos);
        }
        else {
            io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
        }
        
        // Define ImGui window content
        Begin("Settings");
        DragFloat3("Light Pos", &lightPos.x, 0, 100);
        ColorEdit3("Light Color", &lightColor.x);
        SliderFloat("Ambient Strength", &ambientStrength, 0.0f, 1.0f);
        SliderFloat("Diffuse Strength",&diffuseStrength, 0.0f, 1.0f);
        SliderFloat("Specular Strength", &specularStrength, 0.0f, 1.0f);
        SliderFloat("Shininess", &ShininessStrength, 2.0f, 1024.0f);
        Checkbox("Rotate", &cubes.rotateObj);
        Checkbox("Scale", &cubes.scaleObj);
        End();

       

        // Clear screen and render OpenGL
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        Render();
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

        glBindVertexArray(VAO);
        shaderInfo.use();
        shaderInfo.setVec3("lightPos", lightPos);
        shaderInfo.setVec3("viewPos", cam.cameraPos);
        shaderInfo.setVec3("lightColor", lightColor);
        shaderInfo.setFloat("ambientStrength", ambientStrength);
        shaderInfo.setFloat("diffuseStrength", diffuseStrength);
        shaderInfo.setFloat("specularStrength", specularStrength);
        shaderInfo.setFloat("ShininessStrength", ShininessStrength);



        float currentFrame = glfwGetTime();
        cam.deltaTime = currentFrame - cam.lastFrame;
        cam.lastFrame = currentFrame;

        mat4 view = mat4(1.0f);

        view = lookAt(cam.cameraPos, cam.cameraPos + cam.cameraFront, cam.cameraUp);
        mat4 projection = perspective(radians(cam.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        shaderInfo.setMat4("view", view);
        shaderInfo.setMat4("projection", projection);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        cubes.Draw();


       
        lightCube.use();
        lightCube.setVec3("color", lightColor);
        lightCube.setMat4("projection", projection);
        lightCube.setMat4("view", view);
        mat4 model = mat4(1.0f);
        model =translate(model, lightPos);
        model = scale(model,vec3(0.2f)); 
        lightCube.setMat4("model", model);
        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
    }
    

    glfwTerminate();
    return 0;
}

