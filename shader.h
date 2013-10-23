#ifndef __SHADER_H
#define __SHADER_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

char *shaderRead(const char *file);

int shaderDidCompile(GLuint id);
void shaderPrintCompileLog(GLuint id);

#endif
