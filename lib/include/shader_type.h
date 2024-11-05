#pragma once

#include <stdbool.h>

typedef struct {
    unsigned int id;
    void (*use)(void);
    void (*setUniformBool)(char *name, bool value);
    void (*setUniformFloat)(char *name, float value);
    void (*setUniformInt)(char *name, int value);
} Shader;

Shader *createShader(const char *vertexPath, const char *fragmentPath);