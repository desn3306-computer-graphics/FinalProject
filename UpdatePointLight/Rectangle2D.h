#pragma once
#include <GL\glew.h>
#include<glm\glm.hpp>

class Rectangle2D
{
public:
	Rectangle2D();
	void RenderMeshModel();
	void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
	~Rectangle2D();

private:
	GLuint VAO, VBO, IBO;
};

