#include <lib.h>
#include <stdlib.h>
#include <string.h>

GLFWwindow *createGLFWwindowOrExit(int width, int height) {
    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        printf("ERROR: Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    return window;
}

void initializeGLFW(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void loadOpenGLFunctionPointersOrExit(void) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("ERROR: Failed to initialize GLAD.\n");
        exit(EXIT_FAILURE);
    }
}