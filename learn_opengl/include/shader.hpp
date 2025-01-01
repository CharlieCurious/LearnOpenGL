#pragma once

#include <string>
#include <sys/types.h>

class Shader {
    public:
        // the program ID
        uint m_ID;

        // constructor reads and builds the shader
        Shader(const char *vertexPath, const char *fragmentPath);
        // use/active the shader
        void use();
        // utility uniform functons
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
};
