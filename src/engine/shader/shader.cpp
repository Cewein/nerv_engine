#pragma once
#include <glad/glad.h>
#include "shader.h"

size_t nerv::shader::liveProgram = NULL;

void nerv::shader::shaderInfo(size_t shaderId)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		logger.error("SHADER", "Shader did not compile : \n" + std::string(infoLog));

	}
	else
	{
		logger.warning("SHADER", "Shader loaded and compiled proprely");
	}

}

void nerv::shader::programInfo(size_t program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		logger.error("SHADER", "Program did not compile : \n" + std::string(infoLog));
	}
	else
	{
		logger.warning("SHADER", "Program loaded and compiled proprely");
	}
}

size_t nerv::shader::createShader(std::string path, int shaderType)
{
	const char * file = file::read(path);
	size_t shdr;

	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		logger.warning("SHADER", "Compiling Vertex shader");
		shdr = glCreateShader(GL_VERTEX_SHADER);
		break;
	case GL_FRAGMENT_SHADER:
		logger.warning("SHADER", "Compiling Fragment shader");
		shdr = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GL_COMPUTE_SHADER:
		shdr = glCreateShader(GL_COMPUTE_SHADER);
		break;
	default:
		break;
	}

	glShaderSource(shdr, 1, &file, NULL);
	glCompileShader(shdr);
	this->shaderInfo(shdr);

	return shdr;
}

nerv::shader::shader()
{
}

nerv::shader::shader(std::string vertPath, std::string fragPath)
{
	size_t vertexShader = this->createShader(vertPath, GL_VERTEX_SHADER);
	size_t fragmentShader = this->createShader(fragPath, GL_FRAGMENT_SHADER);

	logger.warning("SHADER", "Program in creation");
	this->shaderProgram = glCreateProgram();

	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);

	programInfo(this->shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void nerv::shader::use()
{
	if(compare(this))
		glUseProgram(nerv::shader::liveProgram);
}

bool nerv::shader::compare(nerv::shader * shader)
{
	if (shader->shaderProgram != nerv::shader::liveProgram)
	{
		nerv::shader::liveProgram = shader->shaderProgram;
		return true;
	}
	return false;
}