#ifndef TEXTURE_H
#define TEXTURE_H

#include <gl/glew.h>
#include <SOIL/SOIL.h>

#include <iostream>

class Texture
{
public:
	Texture(const char* path);
	~Texture();

	void bind(GLuint unit);

private:
	GLuint m_texture;

};

#endif