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
#include "../core/ColorsnShit/TextuerinShit.h"

using namespace SHADER_;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

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
unsigned int indices[] = {
    0, 1, 3, 
    1, 2, 3  
};

using namespace std;
using namespace glm;

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

    Texture textuer;
    

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);



    unsigned int texture1;
    glGenTextures(1, &texture1);

    textuer.bind(texture1);
    textuer.loadTextureImage("assets/wall.jpg", true, GL_LINEAR, GL_REPEAT);


   /* unsigned int bgTexture1, bgTexture2;

    glGenTextures(1, &bgTexture1);
    glGenTextures(1, &bgTexture2);

    textuer.bind(bgTexture1);
    textuer.loadTextureImage("assets/wall.jpg", true, GL_LINEAR, GL_REPEAT);

    textuer.bind(bgTexture2);
    textuer.loadTextureImage("assets/catfood.png", true, GL_LINEAR, GL_REPEAT);*/



    shaderInfo.use();
    shaderInfo.setInt("texture1", 0);

    backgroundShader.use();
    backgroundShader.setInt("bgTexture1", 0);
    backgroundShader.setInt("bgTexture2", 1);

    unsigned int vectModel = glad_glGetUniformLocation(shaderInfo.ID, "model");
    unsigned int vectView = glad_glGetUniformLocation(shaderInfo.ID, "view");
    unsigned int vectPro = glad_glGetUniformLocation(shaderInfo.ID, "projection");


    


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();


        // Clear framebuffer
        glClearColor(1.0f, 0.0f, .0f, .0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // stuff to set animations
        float timeValue = glfwGetTime();
        float waveFrequency = 10.0f; 
        float waveAmplitude = 0.05f;

        glBindVertexArray(VAO);

        //backgroundShader.use();
       
      /*  glUniform1f(glGetUniformLocation(backgroundShader.ID, "time"), timeValue);
        glUniform1f(glGetUniformLocation(backgroundShader.ID, "waveFrequency"), waveFrequency);
        glUniform1f(glGetUniformLocation(backgroundShader.ID, "waveAmplitude"), waveAmplitude);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bgTexture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, bgTexture2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

        mat4 model = mat4(1.0f);
        model = rotate(model, (float)glfwGetTime() *  radians(50.0f),  vec3(0.5f, 1.0f, 0.0f));
         mat4 view =  mat4(1.0f);
        view =  translate(view,  vec3(0.0f, 0.0f, -3.0f));
        mat4 projection;
        projection = perspective( radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

        shaderInfo.use();


        

        glUniform1f(glGetUniformLocation(shaderInfo.ID, "time"), timeValue);

        glUniformMatrix4fv( vectModel, 1, GL_FALSE,   value_ptr(model));
        glUniformMatrix4fv( vectView,  1,  GL_FALSE,  value_ptr(view));
        glUniformMatrix4fv( vectPro,   1,   GL_FALSE, value_ptr(projection));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
