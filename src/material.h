#pragma once

#include "texture.h"

class Material
{
public:
	Material(Texture* diffuse, Texture* specular, float shininess);
	~Material();

	void bind();
private:
	Texture* m_diffuse;
	Texture* m_specular;
	float m_shininess;
	
};