#include "model.h"

#include <iostream>

#include <assimp/Importer.hpp>

Model::Model(const std::string& path)
{
	load(path);
}

Model::~Model()
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		delete m_meshes[i];
	}
}

void Model::render()
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i]->render();
	}
}

void Model::load(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error: " << importer.GetErrorString() << std::endl;
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	Material* material;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;
		v.position = Vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		v.normal = Vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		if (mesh->mTextureCoords[0])
		{
			v.texCoords = Vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		vertices.push_back(v);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		Texture* diffuseMap = loadMaterialTexture(mat, aiTextureType_DIFFUSE);
		Texture* specularMap = loadMaterialTexture(mat, aiTextureType_SPECULAR);
		material = new Material(diffuseMap, specularMap, 32.0f);
	}
	return new Mesh(vertices, indices, material);
}

Texture* Model::loadMaterialTexture(aiMaterial* mat, aiTextureType tex)
{
	aiString str;
	mat->GetTexture(tex, 0, &str);
	return new Texture((m_directory + "/" + str.C_Str()).c_str());
}