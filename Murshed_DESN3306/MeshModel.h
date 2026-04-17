#pragma once
#include <GL\glew.h>

class MeshModel
{
public:
	MeshModel();
	void RenderMeshModel();
	void CreateObjectModel(GLfloat* vertices, unsigned int* indices, unsigned int nVertices, unsigned int nIndices);
	~MeshModel();

private:
	GLuint VAO, VBO, IBO;
	int iCount;

};

