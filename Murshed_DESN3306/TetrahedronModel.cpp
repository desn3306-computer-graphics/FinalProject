#include "TetrahedronModel.h"

TetrahedronModel::TetrahedronModel()
{
	/*
	GLfloat vertices[] = {
		// positions              // colors
		//recalculated using cahtgpt for that top point and center on the Y axis (perfect equilateral triangle)
		 0.0f,  0.75f,  0.0f,     1.0f, 0.0f, 0.0f,   0.5f, 0.33f, // Top
		-0.5f, -0.25f,  0.2887f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,// Base left
		 0.5f, -0.25f,  0.2887f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Base right
		 0.0f, -0.25f, -0.5774f,  1.0f, 1.0f, 0.0f,   0.5f, 1.0f,// Base back
	};
	GLuint indices[] = {
	// Face 1
	0, 1, 2,
	// Face 2
	0, 2, 3,
	// Face 3
	0, 3, 1,
	// Face 4 (base)
	3, 2, 1
	};
	*/

	GLfloat vertices[] = {
		// positions              // colors           // tex coords

		// Front face
		 0.0f,  0.75f,  0.0f,     1.0f, 0.0f, 0.0f,   0.5f, 1.0f,
		-0.5f, -0.25f,  0.2887f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.25f,  0.2887f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,

		 // Right face
		  0.0f,  0.75f,  0.0f,     1.0f, 0.0f, 0.0f,   0.5f, 1.0f,
		  0.5f, -0.25f,  0.2887f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		  0.0f, -0.25f, -0.5774f,  1.0f, 1.0f, 0.0f,   1.0f, 0.0f,

		  // Left face
		   0.0f,  0.75f,  0.0f,     1.0f, 0.0f, 0.0f,   0.5f, 1.0f,
		   0.0f, -0.25f, -0.5774f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		  -0.5f, -0.25f,  0.2887f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,

		  // Bottom face
		  -0.5f, -0.25f,  0.2887f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		   0.0f, -0.25f, -0.5774f,  1.0f, 1.0f, 0.0f,   0.5f, 1.0f,
		   0.5f, -0.25f,  0.2887f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 2,      // Front
		3, 4, 5,      // Right
		6, 7, 8,      // Left
		9, 10, 11     // Bottom
	};


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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// IMPORTANT:
	// Do NOT unbind GL_ELEMENT_ARRAY_BUFFER while VAO is active
	glBindVertexArray(0);

	// Optional (safe after VAO unbound)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TetrahedronModel::RenderMeshModel()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

TetrahedronModel::~TetrahedronModel()
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

