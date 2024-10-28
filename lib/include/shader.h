#pragma once
#define MAX_FILE_SIZE 1048576 // 1 MB
#define SHADER_PROGRAM_CREATION_ERROR 0

#include <stdbool.h>
#include <stdio.h>

typedef unsigned int programId;

typedef enum {
    SHADER_COMPILATION,
    PROGRAM_LINKING
} ShaderProgramError;

// Returns the progam ID of the created program or SHADER_PROGRAM_CREATION_ERROR.
programId createShaderProgram(
    const char *vertexShaderSource, 
    const char *fragmentShaderSource, 
    void (*onErrorCallback)(ShaderProgramError errorType, char *message));
char *getShaderSourcePath(const char *shaderFolderPath, const char* shaderFileName);
char *loadShaderSource(FILE *shaderSource);
void setUniformBool(programId programID, char *name, bool value);
void setUniformInt(programId programID, char *name, int value);
void setUniformFloat(programId programID, char *name, float value);