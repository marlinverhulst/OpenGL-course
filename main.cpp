#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image/stb_image.h"

#include "src/Shader.h"

#define SCR_WIDTH 1000
#define SCR_HEIGHT 800



float vertices[] = 
{       /*POSITIONS*/    /*VERTEX COLOR */              /*TEXTURE COORDS*/
    -0.5f, -0.5f, 0.0f,       1.0f, 0.0f, 0.0f,         0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,        0.0f, 1.0f, 0.0f,         1.0f, 0.0f,
    0.5f, 0.5f, 0.0f,         0.0f, 0.0f, 1.0f,         1.0f, 1.0f,

    0.5f, 0.5f, 0.0f,         1.0f, 0.0f, 0.0f,         1.0f,1.0f,
    -0.5f, 0.5f, 0.0f,        0.0f, 1.0f, 0.0f,         0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, 1.0f,         0.0f,0.0f,
};


void resizeCallBack(GLFWwindow* window, int width, int height); // declaration (protype)
void userInput(GLFWwindow* window);
void mouseCursorPosition(GLFWwindow* window, double xPos, double yPos);
void mouseScrollPosition(GLFWwindow* window, double xOffset, double yOffset);


unsigned int loadtexture(const char* texturePath);

glm::mat4 model; // represents the model for scaling position etc
glm::mat4 view; // represent the camera
glm::mat4 projection;
glm::vec3 myPos = glm::vec3(0.0f); // postion vector

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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 3.3", NULL, NULL);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*Color attribute */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    /*Texture Coord attribute */
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    
    
    /* Texture */
    unsigned int containertex =  loadtexture("res/textures/container.jpg");
    unsigned int facetex =  loadtexture("res/textures/awesomeface.png");
 
    
    /* Shaders */

    Shader myShader("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
    myShader.use();
    myShader.setInt("container_texture", 0);
    myShader.setInt("face_texture", 1);

   
   


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

        //model = glm::mat4(1.0f);
        //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
       // model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.5f, 0.5f, 0.5f ));
        //model = glm::translate(model, myPos);


        // COORDINATES 

        projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH) / float(SCR_HEIGHT), 0.1f, 100.0f);
        myShader.setMat4("projection", projection);

        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        myShader.setMat4("view", view);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(model, myPos);
        myShader.setMat4("model", model);


        myShader.setFloat("alpha", xValue);

       
        userInput(window);
        
        
        /* Render here */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*Draw your stuff here*/
       myShader.use();
       //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       glBindVertexArray(VAO);
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, containertex);

       glActiveTexture(GL_TEXTURE1);

       glBindTexture(GL_TEXTURE_2D, facetex);

       glDrawArrays(GL_TRIANGLES, 0, 6);


       //model = glm::mat4(1.0f);
       //model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
       //myShader.setMat4("model", model);
       //glBindVertexArray(VAO);
       //glDrawArrays(GL_TRIANGLES, 0, 6);

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

unsigned int loadtexture(const char* texturePath)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    /*set up filters options*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum channel = GL_RGB;
        if (nrChannels == 1)
            channel = GL_RED;
        if (nrChannels == 3)
            channel = GL_RGB;
        if (nrChannels == 4) 
        {
            channel = GL_RGBA;
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        }

        glTexImage2D(GL_TEXTURE_2D, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture !!! \n";
    }
    
    stbi_image_free(data);




    return texture;
}
