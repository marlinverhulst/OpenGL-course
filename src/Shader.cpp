#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		// this is weird check it later  << this boy is lost

		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}

	catch (std::ifstream::failure e)
	{
		std::cout << "FAILED TO READ FILE \n";

		glfwTerminate();
	}

	vertexShaderData = vertexCode.c_str();
	fragmentShaderData = fragmentCode.c_str();

    /* Vertex Shader*/

    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderData, NULL);
    glCompileShader(fragmentShader);


    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "Failed to compile fragment shader::<" << infoLog << std::endl;
    };

    // Program

    this->ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &succes);
    if (!succes)
    {
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cout << "Failed to link program::<" << infoLog << std::endl;
    };


    /* Delete unneeded shaders */

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float r, float g, float b)
{
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), r,g,b );
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()),1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, 0, glm::value_ptr(value));

}
