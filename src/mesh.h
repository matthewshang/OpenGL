#pragma once

#include <vector>

#include <GL/glew.h>

#include "math/vec3.h"
#include "math/vec2.h"
#include "material.h"

struct Vertex
{
	Vec3 position;
	Vec3 normal;
	Vec2 texCoords;

	Vertex() {};
	Vertex(Vec3 _position, Vec3 _normal, Vec2 _texCoords) :
		position(_position), normal(_normal), texCoords(_texCoords) {};
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<int> indices, Material* material);
	~Mesh();

	void render();
private:
	Material* m_material;
	GLuint m_vbo;
	GLuint m_vao;
	GLuint m_ebo;
	int m_drawCount;
};