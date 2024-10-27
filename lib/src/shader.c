#define GLFW_INCLUDE_NONE
#define INFO_LOG_BUFFER_SIZE 1024

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>

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