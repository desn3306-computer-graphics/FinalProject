#pragma once
#include <GL\glew.h>

class TetrahedronModel
{
public:
	TetrahedronModel();
	void RenderMeshModel();
	~TetrahedronModel();

private:
	GLuint VAO, VBO, IBO;
};

