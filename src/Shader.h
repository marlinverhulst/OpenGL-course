#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
	
	void setFloat(std::string& name, float value) const;
	void setInt(std::string& name, int value) const;




};
