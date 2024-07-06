#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float vertices[] = 
{       /*POSITIONS*/
    -0.5f, -0.5f, 0.0f, // bottom left
    0.5f, -0.5f, 0.0f, //  bottom right
    0.5f, 0.5f, 0.0f, //  up right

    0.5f, 0.5f, 0.0f, //  up right
    -0.5f, 0.5f, 0.0f, //  up left
    -0.5f, -0.5f, 0.0f, // bottom left
};

const char* vertexShaderData =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* fragmentShaderData =
"#version 330 core\n"
"out vec4 fragColor;\n"
"uniform float xColor;"
"uniform float yColor;"
"uniform float zColor;"
"void main()\n"
"{\n"
"   fragColor = vec4(xColor, yColor, zColor, 1.0f );"
"}\0";


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

    /* Vertex Shader */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderData, NULL);
    glCompileShader(vertexShader);

    int succes;
    char infoLog[1024];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "Failed to compile vertex shader::<" << infoLog << std::endl;
    };

    /* Fragment Shader */
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderData, NULL);
    glCompileShader(fragmentShader);


    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "Failed to compile fragment shader::<" << infoLog << std::endl;
    };

    // Program

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &succes);
    if (!succes)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "Failed to link program::<" << infoLog << std::endl;
    };


    /* Delete unneeded shaders */

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);







    /* Buffers */
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW );


    /*Position attribute*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Update here*/
        float time = glfwGetTime();
        float xValue = std::cos(time) / 2.0f + 0.5f; // Clamp it between 0.0f and 1.0f
        float yValue = std::sin(time) / 2.0f + 0.5f; // Clamp it between 0.0f and 1.0f
        float zValue = std::cos(time) / 2.0f + 0.5f; // Clamp it between 0.0f and 1.0f

        glUniform1f(glGetUniformLocation(program, "xColor"), xValue);
        glUniform1f(glGetUniformLocation(program, "yColor"), yValue);
        glUniform1f(glGetUniformLocation(program, "zColor"), zValue);


         
        /* Render here */
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*Draw your stuff here*/
       glUseProgram(program);
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