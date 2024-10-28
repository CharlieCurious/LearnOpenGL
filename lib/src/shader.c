#define GLFW_INCLUDE_NONE
#define INFO_LOG_BUFFER_SIZE 1024

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int shaderId;

static shaderId compileShader(GLenum shaderType, const char *shaderSource);
static bool wasProgramLinked(programId, char *);
static bool wasShaderCompiled(shaderId, char *);

programId createShaderProgram(
    const char *vertexShaderSource, 
    const char *fragmentShaderSource, 
    void (*onErrorCallback)(ShaderProgramError errorType, char *message)) {
        
        char infoLogBuffer[INFO_LOG_BUFFER_SIZE];

        shaderId vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
        if (!wasShaderCompiled(vertexShader, infoLogBuffer)) {
            onErrorCallback(SHADER_COMPILATION, infoLogBuffer);
            glDeleteShader(vertexShader);
            return SHADER_PROGRAM_CREATION_ERROR;
        }

        shaderId fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        if (!wasShaderCompiled(fragmentShader, infoLogBuffer)) {
            onErrorCallback(SHADER_COMPILATION, infoLogBuffer);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return SHADER_PROGRAM_CREATION_ERROR;
        }

        programId program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        if (!wasProgramLinked(program, infoLogBuffer)) {
            onErrorCallback(PROGRAM_LINKING, infoLogBuffer);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(program);
            return SHADER_PROGRAM_CREATION_ERROR;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
}

char *getShaderSourcePath(const char *shaderFolderPath, const char* shaderFileName) {
    char shaderFolderPathBuffer[1024];
    strncpy(shaderFolderPathBuffer, shaderFolderPath, sizeof(shaderFolderPathBuffer) - 1);
    shaderFolderPathBuffer[sizeof(shaderFolderPathBuffer) - 1] = '\0';

    // Remove leading "./" if present
    if (strncmp(shaderFolderPathBuffer, "./", 2) == 0) {
        memmove(shaderFolderPathBuffer, shaderFolderPathBuffer + 2, strlen(shaderFolderPathBuffer) - 1);
    }

    // Remove trailing "/" if present
    size_t len = strlen(shaderFolderPathBuffer);
    if (len > 0 && shaderFolderPathBuffer[len - 1] == '/') {
        shaderFolderPathBuffer[len - 1] = '\0';
    }

    char *shaderPathBuffer = malloc(2048 * sizeof(char));
    snprintf(shaderPathBuffer, 2048, "%s/%s", shaderFolderPathBuffer, shaderFileName);

    return shaderPathBuffer;
}

char *loadShaderSource(FILE *shaderSource) {
    if (!shaderSource) {
        return NULL;
    }

    if(fseek(shaderSource, 0L, SEEK_END) != 0) {
        perror("Failed to determine shader source size.");
        return NULL;
    }
    
    long length = ftell(shaderSource);
    if (length < 0 || length > MAX_FILE_SIZE) {
        perror("File size error of file too large.");
        return NULL;
    }

    rewind(shaderSource);

    char *content = (char *)malloc(length + 2); // +2 for /n and /0.
    if (!content) {
        perror("Memory allocation failed.");
        return NULL;
    }

    size_t read_size = fread(content, 1, length, shaderSource);

    // Handle incomplete reads
    if (read_size != length) {
        perror("Failed to read the entire file.");
        free(content);
        return NULL;
    }

    memcpy(content + length, "\n\0", 2);

    return content;
}

void setUniformBool(programId programID, char *name, bool value) {
    glUniform1i(glGetUniformLocation(programID, name), (int)value);
}

void setUniformInt(programId programID, char *name, int value) {
    glUniform1i(glGetUniformLocation(programID, name), value);
}

void setUniformFloat(programId programID, char *name, float value) {
    glUniform1f(glGetUniformLocation(programID, name), value);
}

static shaderId compileShader(GLenum shaderType, const char *shaderSource) {
    shaderId shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    return shader;
}

static bool wasProgramLinked(programId program, char *infoLogBuffer) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, INFO_LOG_BUFFER_SIZE, NULL, infoLogBuffer);
        return false;
    }
    return true;
}

static bool wasShaderCompiled(shaderId shader, char *infoLogBuffer) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, INFO_LOG_BUFFER_SIZE, NULL, infoLogBuffer);
        return false;
    }
    return true;
}