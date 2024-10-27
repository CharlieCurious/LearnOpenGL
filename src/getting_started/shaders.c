#include <lib.h>
#include <shader.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void onCreateProgramError(ShaderProgramError, char *);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";


int main(int argc, const char **argv) {

    if (argc < 2) {
        puts("Specify the path to the shaders folder.");
        exit(EXIT_FAILURE);
    }

    // ------ Setup GLFW and glad ---------
    initializeGLFW();

    GLFWwindow *window = createGLFWwindowOrExit(SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    loadOpenGLFunctionPointersOrExit();

    // ------ Setup Shaders -------------
    programId shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource, onCreateProgramError);

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