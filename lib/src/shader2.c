#include <file_handling.h>
#include <glad/glad.h>
#include <shader2.h>
#include <stdio.h>

static unsigned int compileShader(GLenum shaderType, const char *shaderSource);
static unsigned int createProgram(const char *vSource, const char *fSource);
static bool wasProgramLinked(unsigned int programId);
static bool wasShaderCompiled(unsigned int shaderId);

unsigned int create(const char *vertexShaderPath, const char *fragmentShaderPath) {
    FILE *vShaderFile = fopen(vertexShaderPath, "r");
    if (!vShaderFile) return NULL;

    char *vSource = loadFileContentToString(vShaderFile);
    fclose(vShaderFile);
    if (!vSource) return NULL;

    FILE *fShaderFile = fopen(fragmentShaderPath, "r");
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
    free(vSource);
    free(fSource);

    if (!wasProgramLinked(programId)) {
        glDeleteProgram(programId);
        return NULL;
    }

    return programId;
}

void use(unsigned int shader) {
    glUseProgram(shader);
}

void setUniformBool(const char *name, const bool value, GLuint shaderProgramId) {
    glUniform1i(glGetUniformLocation(shaderProgramId, name), (int)value);
}

void setUniformFloat(const char *name, const float value, GLuint shaderProgramId) {
    glUniform1f(glGetUniformLocation(shaderProgramId, name), value);
} 

void setUniformInt(const char *name, const int value, GLuint shaderProgramId) {
    glUniform1i(glGetUniformLocation(shaderProgramId, name), value);
}

void setUniformVec2(const char *name, const vec2 value, GLuint shaderProgramId) {
    glUniform2fv(glGetUniformLocation(shaderProgramId, name), 1, value);
}

void setUniformVec3(const char *name, const vec3 value, GLuint shaderProgramId) {
    glUniform3fv(glGetUniformLocation(shaderProgramId, name), 1, value);
}

void setUniformVec4(const char *name, const vec4 value, GLuint shaderProgramId) {
    glUniform4fv(glGetUniformLocation(shaderProgramId, name), 1, value);
}

void setUniformMat2(const char *name, const mat2 value, GLuint shaderProgramId) {
    glUniformMatrix2fv(glGetUniformLocation(shaderProgramId, name), 1, GL_FALSE, value);
}

void setUniformMat3(const char *name, const mat3 value, GLuint shaderProgramId) {
    glUniformMatrix3fv(glGetUniformLocation(shaderProgramId, name), 1, GL_FALSE, value);
}

void setUniformMat4(const char *name, const mat4 value, GLuint shaderProgramId) {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name), 1, GL_FALSE, value);
}

static unsigned int compileShader(GLenum shaderType, const char *shaderSource) {
    unsigned int id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);
    return id;
}

static unsigned int createProgram(const char *vSource, const char *fSource) {
    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vSource);
    if (!wasShaderCompiled(vertexShaderId))
        return NULL;

    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fSource); 
    if (!wasShaderCompiled(fragmentShaderId))
        return NULL;

    unsigned int programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

static bool wasProgramLinked(unsigned int programId) {
    if (programId == NULL) {
        return false;
    }

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

static bool wasShaderCompiled(unsigned int shaderId) {
    int success;
    char errorMessageBuffer[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, errorMessageBuffer);
        perror(errorMessageBuffer);
        return false;
    }
    return true;
}