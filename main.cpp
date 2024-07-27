#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "src/Shader.h"

float vertices[] = 
{       /*POSITIONS*/    /*VERTEX COLOR */
    -0.5f, -0.5f, 0.0f,       1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,        0.0f, 1.0f, 0.0f,  
    0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,  

    0.5f, 0.5f, 0.0f,         1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,        0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,
};

void resizeCallBack(GLFWwindow* window, int width, int height); // declaration (protype)
void userInput(GLFWwindow* window);


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 800, "OpenGL 3.3", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeCallBack);

    if (glewInit() != GLEW_OK) {
        std::cout << "failed to init GLEW\n";
        glfwTerminate();
    }

     




    /* Buffers */
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW );


    /*Position attribute*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*Color attribute */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    /* Shaders */

    Shader myShader("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
   


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Update here*/

        userInput(window);
        /* Render here */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*Draw your stuff here*/
       myShader.use();
       //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       glBindVertexArray(VAO);
       glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    // CLEARING
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void resizeCallBack(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void userInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}
