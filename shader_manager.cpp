#include "shader_manager.h"

#include "logging.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

ShaderManager *ShaderManager::instance = nullptr;

ShaderManager::ShaderManager() {
}

ShaderManager *ShaderManager::getInstance() {
	if (ShaderManager::instance == nullptr) {
		ShaderManager::instance = new ShaderManager();
	}

	return ShaderManager::instance;
}

char *ShaderManager::shaderRead(const char *file) {
	int fd;
	long size;
	char *buf;

	fd = open(file, O_RDONLY, 0);
	if (fd < 0) {
		return NULL;
	}

	size = lseek(fd, 0, SEEK_END);
	buf = (char *)malloc(sizeof(char) * (size + 1));

	lseek(fd, 0, SEEK_SET);
	read(fd, buf, size);

	close(fd);

	buf[size] = 0;

	return buf;
}

int ShaderManager::shaderDidCompile(GLuint id) {
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	return status;
}

void ShaderManager::shaderPrintCompileLog(GLuint id) {
	char buf[512];
	if (!shaderDidCompile(id)) {
		glGetShaderInfoLog(id, 512, NULL, buf);
		ERR("Error compiling shader:\n%s", buf);
	}
}

GLuint ShaderManager::load(std::string shader, int type) {
	char *shaderSource = shaderRead(shader.c_str());
	const char *source = shaderSource;
	GLuint id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
	free(shaderSource);
	glCompileShader(id);

	if (!shaderDidCompile(id)) {
		shaderPrintCompileLog(id);
	}

	getInstance()->shaders.insert(std::pair<std::string, GLuint>(shader, id));

	return id;
}

GLuint ShaderManager::buildProgram(std::vector<std::string> shaderList) {
	GLuint prog = glCreateProgram();

	for (std::string &shader : shaderList) {
		auto it = getInstance()->shaders.find(shader);
		if (it != getInstance()->shaders.end()) {
			glAttachShader(prog, it->second);
		}
	}

	glBindFragDataLocation(prog, 0, "outColor");
	glLinkProgram(prog);

	return prog;
}
