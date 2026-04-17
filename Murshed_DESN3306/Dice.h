#pragma once
#include <GL\glew.h>
#include<glm\glm.hpp>

class Dice
{
public:
	Dice();
	void RenderMeshModel();
	void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
	~Dice();

private:
	GLuint VAO, VBO, IBO;
};
