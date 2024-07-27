#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
void mouseCursorPosition(GLFWwindow* window, double xPos, double yPos);
void mouseScrollPosition(GLFWwindow* window, double xOffset, double yOffset);

glm::mat4 model; // represents the model for scaling position etc
glm::vec3 myPos = glm::vec3(1.0f); // postion vector

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

    // setCallbackFunctions
    glfwSetFramebufferSizeCallback(window, resizeCallBack);
    glfwSetCursorPosCallback(window, mouseCursorPosition);
    glfwSetScrollCallback(window, mouseScrollPosition);
    

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
        float time = glfwGetTime();
		float xValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::cos(time) / 2.0f + 0.5f; // 0.0f - 1.0f
        
        glm::vec3 colorVecor = { 1.0f, 0.5f, 0.50f };
        myShader.setVec3("color", colorVecor);

        /* MATRIX for scaling / rotation etc*/

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.5f, 0.5f, 0.5f ));
                
         


        model = glm::translate(model, myPos);
        myShader.setMat4("model", model);

       
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE)  
             myPos.y += 0.0005f;
            
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)  
             myPos.y -= 0.0005f;
         
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)  
             myPos.x += 0.0005f;
            
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)  
             myPos.x -= 0.0005f;


}
void mouseCursorPosition(GLFWwindow* window, double xPos, double yPos)
{
    std::cout << "mouse has been moved: " << xPos << " " << yPos << "\n";
}


void mouseScrollPosition(GLFWwindow* window, double xOffset, double yOffset)
{
    std::cout << "Scrolling: " << xOffset << " " << yOffset << "\n";
}
