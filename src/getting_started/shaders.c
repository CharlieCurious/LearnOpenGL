#include <lib.h>
#include <stdlib.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, const char **argv) {

    // ------ Setup GLFW and glad ---------
    initializeGLFW();

    GLFWwindow *window = createGLFWwindowOrExit(SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    loadOpenGLFunctionPointersOrExit();

    return EXIT_SUCCESS;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}