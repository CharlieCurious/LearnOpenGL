#pragma once
#define SHADER_PROGRAM_CREATION_ERROR 0

#include <stdbool.h>

typedef unsigned int programId;

typedef enum {
    SHADER_COMPILATION,
    PROGRAM_LINKING
} ShaderProgramError;

programId createShaderProgram(
    const char *vertexShaderSource, 
    const char *fragmentShaderSource, 
    void (*onErrorCallback)(ShaderProgramError errorType, char *message));
void setUniformBool(programId programID, char *name, bool value);
void setUniformInt(programId programID, char *name, int value);
void setUniformFloat(programId programID, char *name, float value);