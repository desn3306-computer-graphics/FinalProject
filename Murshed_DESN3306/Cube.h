#pragma once
#include <GL\glew.h>

class Cube
{
public:
	Cube();
	void RenderMeshModel();
	~Cube();

private:
	GLuint VAO, VBO, IBO;
};
