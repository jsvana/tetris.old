#pragma once

#ifndef __SHADER_MANAGER_H
#define __SHADER_MANAGER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <map>

class ShaderManager {
private:
	std::map<std::string, GLuint> shaders;
	std::vector<GLuint> shaderProgs;

	static ShaderManager *instance;

	static char *shaderRead(const char *file);

	static int shaderDidCompile(GLuint id);
	static void shaderPrintCompileLog(GLuint id);

	ShaderManager();
	~ShaderManager();

public:
	static ShaderManager *getInstance();
	void destroy();

	static GLuint load(std::string shader, int type);
	static GLuint buildProgram(std::vector<std::string> shaderList);
};

#define SHADERMAN (ShaderManager::getInstance())

#endif
