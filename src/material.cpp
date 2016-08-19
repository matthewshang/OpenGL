#include "material.h"

Material::Material(Texture* diffuse, Texture* specular, float shininess)
{
	m_diffuse = diffuse;
	m_specular = specular;
	m_shininess = shininess;
}

Material::~Material()
{
	delete m_diffuse;
	delete m_specular;
}

void Material::bind()
{
	m_diffuse->bind(Texture::TEXTURE_DIFFUSE);
	m_specular->bind(Texture::TEXTURE_SPECULAR);
}