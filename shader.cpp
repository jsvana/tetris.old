#include "shader.h"

#include "logging.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *shaderRead(const char *file) {
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

int shaderDidCompile(GLuint id) {
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	return status;
}

void shaderPrintCompileLog(GLuint id) {
	char buf[512];
	if (!shaderDidCompile(id)) {
		glGetShaderInfoLog(id, 512, NULL, buf);
		ERR("Error compiling shader:\n%s", buf);
	}
}
