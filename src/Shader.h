#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
private:
	std::string vertexCode, fragmentCode;
	std::fstream vertexShaderFile, fragmentShaderFile;
	std::stringstream vertexShaderStream,  fragmentShaderStream;
	const char* vertexShaderData, * fragmentShaderData;
	unsigned int vertexShader, fragmentShader;

public: 
	unsigned int ID;

	// constructor 
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void use();

	// Uniforms utils
	
	void setFloat(const std::string& name, float value) const;
	void setInt(const std::string& name, int value) const;
	void setVec3(const std::string& name, float r, float g, float b);
	void setVec3(const std::string& name, const glm::vec3& value);
	void setMat4(const std::string& name, const glm::mat4& value);




};
