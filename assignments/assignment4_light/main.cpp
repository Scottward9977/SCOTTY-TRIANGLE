#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>

#include <../imgui.h>
#include <../backends/imgui_impl_glfw.h>
#include <../backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ew/external/stb_image.h"
#include "../core/ColorsnShit/ColorsnShit.h" 

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 560;

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
    if (window == NULL) {
        printf("GLFW failed to create window");
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("GLAD Failed to load GL headers");
        return 1;
    }

    IMGUI_CHECKVERSION();
    CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();


    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, cam.mouse_callback);
    glfwSetScrollCallback(window, cam.scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int lightCubeVAO;
        glGenVertexArrays(1, &lightCubeVAO);
        glBindVertexArray(lightCubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // note that we update the lamp's position attribute's stride to reflect the updated buffer data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


    unsigned int texture1;
    glGenTextures(1, &texture1);
    textuer.bind(texture1);
    textuer.loadTextureImage("assets/cat.png", true, GL_LINEAR, GL_REPEAT);

    shaderInfo.use();
    vec3 lightPos = vec3(5.2f, 7.0f, 2.0);
    shaderInfo.setInt("texture1", 0);
  
    while (!glfwWindowShouldClose(window)&& cam.exit) {
        glfwPollEvents();
        cam.processInput(window);


        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        NewFrame();

        Begin("Settings");
        Text("Add Stuff Here");
        End();

        Render();
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

        // Clear screen and render OpenGL
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        shaderInfo.use();
        shaderInfo.setVec3("lightPos", lightPos);
        shaderInfo.setVec3("viewPos", cam.cameraPos);


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


        // also draw the lamp object
        lightCube.use();
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

