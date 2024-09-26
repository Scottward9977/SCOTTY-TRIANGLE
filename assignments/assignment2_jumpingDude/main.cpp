#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "ew/external/stb_image.h"
#include "../core/ColorsnShit/ColorsnShit.h" 

using namespace SHADER_;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
        
     0.25f,  0.25f, 0.0f,   1.0f, 0.4f, 0.9f,   1.0f, 1.0f,
     0.25f, -0.25f, 0.0f,   1.0f, 0.4f, 0.9f,   1.0f, 0.0f,
    -0.25f, -0.25f, 0.0f,   1.0f, 0.4f, 0.9f,   0.0f, 0.0f,
    -0.25f,  0.25f, 0.0f,   1.0f, 0.4f, 0.9f,   0.0f, 1.0f
};
unsigned int indices[] = {
    0, 1, 3, 
    1, 2, 3  
};

float backgroundVertices[] = {
    -1.0f,  1.0f, 0.0f,  8.0f, 8.0f, // Top-left corner
    -1.0f, -1.0f, 0.0f,  8.0f, 0.0f, // Bottom-left corner
     1.0f, -1.0f, 0.0f,  0.0f, 0.0f, // Bottom-right corner
     1.0f,  1.0f, 0.0f,  0.0f, 8.0f  // Top-right corner
};
unsigned int backgroundIndices[] = {
    0, 1, 2, 
    0, 2, 3 
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shaderInfo("assets/VertexShader.vert", "assets/FragmentShader.frag");
    Shader backgroundShader("assets/backgroundVert.vert", "assets/backgroundFrag.frag");

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

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int bgVBO, bgEBO, bgVAO;

    glGenVertexArrays(1, &bgVAO);
    glBindVertexArray(bgVAO);

    glGenBuffers(1, &bgVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundVertices), backgroundVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &bgEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bgEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(backgroundIndices), backgroundIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture Coordinates
    glEnableVertexAttribArray(1);

    // texture coord attribute
   
    




    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("assets/cat.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    unsigned int bgTexture;
    glGenTextures(1, &bgTexture);
    glBindTexture(GL_TEXTURE_2D, bgTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Load and generate the texture
    int bgWidth, bgHeight, bgNrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bgData = stbi_load("assets/wall.jpg", &bgWidth, &bgHeight, &bgNrChannels, 0);
    if (bgData)
    {
      
        GLenum format = (bgNrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, bgWidth, bgHeight, 0, format, GL_UNSIGNED_BYTE, bgData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load background texture" << std::endl;
    }
    stbi_image_free(bgData);


    unsigned int bgTexture2;
    glGenTextures(1, &bgTexture2);
    glBindTexture(GL_TEXTURE_2D, bgTexture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


   
    stbi_set_flip_vertically_on_load(true);
    bgData = stbi_load("assets/catfood.png", &bgWidth, &bgHeight, &bgNrChannels, 0);
    if (bgData)
    {

        GLenum format = (bgNrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, bgWidth, bgHeight, 0, format, GL_UNSIGNED_BYTE, bgData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load background texture" << std::endl;
    }
    stbi_image_free(bgData);



    shaderInfo.use();
    glUniform1i(glGetUniformLocation(shaderInfo.ID, "texture1"), 0);


    backgroundShader.use();
    glUniform1i(glGetUniformLocation(backgroundShader.ID, "bgTexture1"), 0); 
    glUniform1i(glGetUniformLocation(backgroundShader.ID, "bgTexture2"), 1);

    
    

    // Googled thse two lines becouse i wanted to know the wire frame code!
    //glPolygonMode(GL_FRONT, GL_FILL);
    //glPolygonMode(GL_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();


        // Clear framebuffer
        glClearColor(1.0f, 0.0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        float timeValue = glfwGetTime();
        //shaderInfo.setFloat("editColor", abs(sin(glfwGetTime())));  
        //shaderInfo.setFloat("editLocationy", glfwGetTime()); 
        // bind textures on corresponding texture units
        // Background rendering
        backgroundShader.use();

        backgroundShader.use();
        glUniform1f(glGetUniformLocation(backgroundShader.ID, "time"), timeValue);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bgTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, bgTexture2);
        glBindVertexArray(bgVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 2. Use foreground shader and draw foreground
        shaderInfo.use();
        glUniform1f(glGetUniformLocation(shaderInfo.ID, "time"), timeValue); // Ensure you use shaderInfo.ID here
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
