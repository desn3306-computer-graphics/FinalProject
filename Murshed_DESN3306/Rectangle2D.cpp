#include "Rectangle2D.h"


Rectangle2D::Rectangle2D()
{
	
	GLfloat vertices[] = {
		// positions              // colors
		//recalculated using cahtgpt for that top point and center on the Y axis (perfect equilateral triangle)
		//Px      Py     Pz      Cr    Cg    Cb     Ts    Tt   Nx     Ny    Nz
		-1.0f,  -1.0f,  0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top
		 1.0f, -1.0f,  0.0f,   0.0f, 0.0f, 1.0f,  30.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Base left
		 1.0f, 1.0f,  0.0f,    0.0f, 1.0f, 0.0f, 30.0f, 30.0f, 0.0f, 0.0f, 0.0f,  // Base right
		 -1.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,  0.0f, 30.0f, 0.0f, 0.0f, 0.0f, // Base back
	};
	GLuint indices[] = {
		// Triangle Bottom Right
		0, 1, 2,
		// Triangle Top Left
		0, 2, 3,
	};

	calcAverageNormals(indices, 6, vertices, 4 * 11, 11, 8); //size of vertex data, offset



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// -------- VBO --------
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// -------- IBO --------
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// -------- Vertex Attributes --------
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// IMPORTANT:
	// Do NOT unbind GL_ELEMENT_ARRAY_BUFFER while VAO is active
	glBindVertexArray(0);

	// Optional (safe after VAO unbound)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Rectangle2D::calcAverageNormals(unsigned int* indices,
	unsigned int indiceCount,
	GLfloat* vertices,
	unsigned int verticeCount,
	unsigned int vLength,
	unsigned int normalOffset)
{
	for (unsigned int i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		vertices[nOffset + 0] = 0.0f;
		vertices[nOffset + 1] = 0.0f;
		vertices[nOffset + 2] = 0.0f;
	}

	for (unsigned int i = 0; i < indiceCount; i += 3)
	{
		unsigned int i0 = indices[i] * vLength;
		unsigned int i1 = indices[i + 1] * vLength;
		unsigned int i2 = indices[i + 2] * vLength;

		glm::vec3 v0(vertices[i0], vertices[i0 + 1], vertices[i0 + 2]);
		glm::vec3 v1(vertices[i1], vertices[i1 + 1], vertices[i1 + 2]);
		glm::vec3 v2(vertices[i2], vertices[i2 + 1], vertices[i2 + 2]);

		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v0;

		glm::vec3 normal = glm::cross(edge1, edge2);

		float len = glm::length(normal);

		if (len < 0.00001f) continue; // ?? prevents NaN

		normal /= len;

		unsigned int n0 = i0 + normalOffset;
		unsigned int n1 = i1 + normalOffset;
		unsigned int n2 = i2 + normalOffset;

		vertices[n0] += normal.x;
		vertices[n0 + 1] += normal.y;
		vertices[n0 + 2] += normal.z;

		vertices[n1] += normal.x;
		vertices[n1 + 1] += normal.y;
		vertices[n1 + 2] += normal.z;

		vertices[n2] += normal.x;
		vertices[n2 + 1] += normal.y;
		vertices[n2 + 2] += normal.z;
	}

	for (unsigned int i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;

		glm::vec3 n(
			vertices[nOffset],
			vertices[nOffset + 1],
			vertices[nOffset + 2]
		);

		float len = glm::length(n);
		if (len < 0.00001f) continue;

		n /= len;

		vertices[nOffset] = n.x;
		vertices[nOffset + 1] = n.y;
		vertices[nOffset + 2] = n.z;
	}
}

void Rectangle2D::RenderMeshModel()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Rectangle2D::~Rectangle2D()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}