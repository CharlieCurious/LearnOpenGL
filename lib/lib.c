#include <lib.h>
#include <stdlib.h>
#include <string.h>

static unsigned int compileShader(GLenum shaderType, const char *shaderSource); 

unsigned int createShaderProgramOrExit(const char *vertexShaderSource, const char *fragmentShaderSource) {
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR: shader program linking failed: %s.\n", infoLog);
        exit(EXIT_FAILURE);
    }

    // Delete shaders after successful linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLFWwindow *createGLFWwindowOrExit(int width, int height) {
    GLFWwindow *window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        printf("ERROR: Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    return window;
}

static unsigned int compileShader(GLenum shaderType, const char *shaderSource) {
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR: shader failed to compile: %s\n", infoLog);
        exit(EXIT_FAILURE);
    }

    return shader;
}

void initializeGLFW(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

char *loadShaders(FILE *shaders_file) {
    if (!shaders_file) {
        return NULL;
    }

    if(fseek(shaders_file, 0L, SEEK_END) != 0) {
        perror("Failed to determine shader source size.");
        return NULL;
    }
    
    long length = ftell(shaders_file);
    if (length < 0 || length > MAX_FILE_SIZE) {
        perror("File size error of file too large.");
        return NULL;
    }

    rewind(shaders_file);

    char *content = (char *)malloc(length + 2); // +2 for /n and /0.
    if (!content) {
        perror("Memory allocation failed.");
        return NULL;
    }

    size_t read_size = fread(content, 1, length, shaders_file);

    // Handle incomplete reads
    if (read_size != length) {
        perror("Failed to read the entire file.");
        free(content);
        return NULL;
    }

    memcpy(content + length, "\n\0", 2);

    return content;
}

void loadOpenGLFunctionPointersOrExit(void) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("ERROR: Failed to initialize GLAD.\n");
        exit(EXIT_FAILURE);
    }
}