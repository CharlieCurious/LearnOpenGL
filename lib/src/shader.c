#define GLFW_INCLUDE_NONE

#include <file_handling.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void checkShaderCompiled(unsigned int shaderId);
static unsigned int createProgram(const char *vSource, const char *fSource);
static unsigned int compileShader(GLenum shaderType, const char *shaderSource);
static void deleteShader(void);
static void useProgram(void);
static void setUniformBoolInternal(char *name, bool value);
static void setUniformFloatInternal(char *name, float value);
static void setUniformIntInternal(char *name, int value);
static bool wasProgramLinked(unsigned int programId);

static Shader *context = NULL;

Shader *createShader(const char *vertexPath, const char *fragmentPath) {
    if (context != NULL) {
        return context;
    }

    FILE *vShaderFile = fopen(vertexPath, "r");
    if (!vShaderFile) return NULL;
    
    char *vSource = loadFileContentToString(vShaderFile);
    fclose(vShaderFile);
    if (!vSource) return NULL;

    FILE *fShaderFile = fopen(fragmentPath, "r");
    if (!fShaderFile) {
        free(vSource);
        return NULL;
    }
    char *fSource = loadFileContentToString(fShaderFile);
    fclose(fShaderFile);
    if (!fSource) {
        free(vSource);
        return NULL;
    }

    unsigned int programId = createProgram(vSource, fSource);
    if (!wasProgramLinked(programId)) {
        free(vSource);
        free(fSource);
        glDeleteProgram(programId);
        return NULL;
    }

    Shader *shader = (Shader *)malloc(sizeof(Shader));
    if (!shader) return NULL;

    context = shader; // set the currentShaderId to the createdProgram
    shader->id = programId;
    shader->use = useProgram;
    shader->setUniformBool = setUniformBoolInternal;
    shader->setUniformFloat = setUniformFloatInternal;
    shader->setUniformInt = setUniformIntInternal;
    shader->delete = deleteShader;

    return shader;
}

static void checkShaderCompiled(unsigned int shaderId) {
    int success;
    char errorMessageBuffer[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, errorMessageBuffer);
        perror(errorMessageBuffer);
    }
}

static unsigned int createProgram(const char *vSource, const char *fSource) {
    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vSource);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fSource);

    unsigned int programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

static unsigned int compileShader(GLenum shaderType, const char *shaderSource) {
    unsigned int id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);

    checkShaderCompiled(id);

    return id;
}

static void deleteShader(void) {
    glDeleteProgram(context->id);
    free(context);
    context = NULL;
}

static void useProgram(void) {
    glUseProgram(context->id);
}

static void setUniformBoolInternal(char *name, bool value) {
    glUniform1i(glGetUniformLocation(context->id, name), (int)value);
}

static void setUniformFloatInternal(char *name, float value) {
    glUniform1f(glGetUniformLocation(context->id, name), value);
}

static void setUniformIntInternal(char *name, int value) {
    glUniform1i(glGetUniformLocation(context->id, name), value);
}

static bool wasProgramLinked(unsigned int programId) {
    int success;
    char errorMessageBuffer[512];
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programId, 512, NULL, errorMessageBuffer);
        perror(errorMessageBuffer);
        return false;
    }
    return true;
}
