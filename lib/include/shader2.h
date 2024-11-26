#include <cglm/cglm.h>
#include <glad/glad.h>
#include <stdbool.h>

GLuint create(const char *vertexShaderPath, const char *fragmentShaderPath);

void use(GLuint shaderProgramId);

void setUniformBool(const char *name, const bool value, GLuint shaderProgramId); 

void setUniformFloat(const char *name, const float value, GLuint shaderProgramId); 

void setUniformInt(const char *name, const int value, GLuint shaderProgramId);

void setUniformVec2(const char *name, const vec2 value, GLuint shaderProgramId);

void setUniformVec3(const char *name, const vec3 value, GLuint shaderProgramId);

void setUniformVec4(const char *name, const vec4 value, GLuint shaderProgramId);

void setUniformMat2(const char *name, const mat2 value, GLuint shaderProgramId);

void setUniformMat3(const char *name, const mat3 value, GLuint shaderProgramId);

void setUniformMat4(const char *name, const mat4 value, GLuint shaderProgramId);