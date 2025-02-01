#pragma once

#include "shader.hpp"
#include <glm/glm.hpp>
#include <string>
#include <sys/types.h>
#include <vector>

struct Vertex {
    glm::vec3 Postion;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    uint id;
    std::string type;
    std::string path;
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex>     vertices;
        std::vector<uint>       indices;
        std::vector<Texture>    textures;

        Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures);

        void Draw(Shader &shader);

    private:
        // render data
        uint VAO, VBO, EBO;

        void setupMesh();
};
