#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

float vertices[] = 
{       /*POSITIONS*/
    -0.5f, -0.5f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f, //  bottom right
    0.5f, 0.5f, 0.0f, //  up right
    -0.5f, 0.5f, 0.0f, //  up left
};

int indecies[] =
{
    0,1,2,
    2,3,0
};


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

    if (glewInit() != GLEW_OK) {
        std::cout << "failed to init GLEW\n";
        glfwTerminate();
    }

    /* Buffers */
    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), &indecies, GL_STATIC_DRAW);

    /*Position attribute*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Update here*/

         
        /* Render here */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*Draw your stuff here*/
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       //glBindVertexArray(VAO);
       //glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,(void*)0);


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