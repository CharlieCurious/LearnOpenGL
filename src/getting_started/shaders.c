#include <lib.h>
#include <shader.h>
#include <file_handling.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void onCreateProgramError(ShaderProgramError, char *);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, const char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <shader-folder-path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char vertexShaderPath[256];
    getSourceFilePath(vertexShaderPath, 256, argv[1], "vertex.glsl");
    FILE *vertexShaderSourceFile = fopen(vertexShaderPath, "r");
    if (vertexShaderSourceFile == NULL) {
        perror("Could not open vertex shader source.");
        exit(EXIT_FAILURE);
    }
    char fragmentShaderPath[256];
    getSourceFilePath(fragmentShaderPath, 256, argv[1], "fragment.glsl");
    FILE *fragmentShaderSourceFile = fopen(fragmentShaderPath, "r");
    if (fragmentShaderSourceFile == NULL) {
        perror("Could not open fragment shader source.");
        exit(EXIT_FAILURE);
    }

    char *vertexShaderSource = loadFileContentToString(vertexShaderSourceFile);
    fclose(vertexShaderSourceFile);
    char *fragmentShaderSource = loadFileContentToString(fragmentShaderSourceFile);
    fclose(fragmentShaderSourceFile);

    // ------ Setup GLFW and glad ---------
    initializeGLFW();

    GLFWwindow *window = createGLFWwindowOrExit(SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    loadOpenGLFunctionPointersOrExit();

    // ------ Setup Shaders -------------
    programId shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource, onCreateProgramError);
    free(vertexShaderSource);
    free(fragmentShaderSource);

    // ------ Setup vertex data and buffers and configure vertex attributes ------
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };    

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void onCreateProgramError(ShaderProgramError errorType, char *message) {
    switch (errorType)
    {
    case SHADER_COMPILATION:
        fprintf(stderr, "One or more shaders failed to compile: %s\n.", message);
        glfwTerminate();
        exit(EXIT_FAILURE);
    case PROGRAM_LINKING:
        fprintf(stderr, "Shader program linking failed: %s\n.", message);
        glfwTerminate();
        exit(EXIT_FAILURE);
    default:
        fprintf(stderr, "Unexpected error while creating shader program occurred: %s\n.", message);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}