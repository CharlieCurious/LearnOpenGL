#pragma once
#define GLFW_INCLUDE_NONE
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define MAX_FILE_SIZE 1048576 // 1 MB

GLFWwindow *createGLFWwindowOrExit(int width, int height);
void initializeGLFW();
void loadOpenGLFunctionPointersOrExit(void);
void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);