#pragma once

#include <vector>
#include <string>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"
#include "material.h"

class Model
{
public:
	Model(const std::string& path);
	~Model();
	void render();

private:
	std::vector<Mesh*> m_meshes;
	std::string m_directory;

	void load(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    Texture* loadMaterialTexture(aiMaterial* mat, aiTextureType tex);
};