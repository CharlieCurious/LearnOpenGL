#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define MAX_FILE_SIZE 1048576 // 1 MB

GLFWwindow *createGLFWwindowOrExit(int width, int height);
unsigned int createShaderProgramOrExit(const char *vertexShaderSource, const char *fragmentShaderSource);
void initializeGLFW();
void loadOpenGLFunctionPointersOrExit(void);
char *loadShaders(FILE *shaders_file);