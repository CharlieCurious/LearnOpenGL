#pragma once

#include "mesh.hpp"
#include "shader.hpp"
#include <assimp/scene.h>
#include <vector>

class Model {
    public:
        Model(char *path);
        void Draw(Shader &shader);

    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string name);
};
