#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../core/ColorsnShit/ColorsnShit.h" 

using namespace SHADER_;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
     0.5f,  0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f, 
    -0.5f,  0.5f, 0.0f   
};
unsigned int indices[] = {  
    0, 1, 3,  
    1, 2, 3  
};
using namespace std;

int main() {
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

    Shader shaderInfo("assets/VertexShader.vert", "assets/FragmentShader.frag");



    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderInfo.use();

    // Googled thse two lines becouse i want to know the wire frame code!
    //glPolygonMode(GL_FRONT, GL_LINE);
    //glPolygonMode(GL_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();


        // Clear framebuffer
        glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        shaderInfo.use();
        //shaderInfo.setFloat("editColor", abs(sin(glfwGetTime())));  
        //shaderInfo.setFloat("editLocationy", glfwGetTime()); 

        glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
