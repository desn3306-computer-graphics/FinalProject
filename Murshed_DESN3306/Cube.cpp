#include "Cube.h"



Cube::Cube()
{
	GLfloat vertices[] = {
		// positions            // colors         // tex coords

		// FRONT face
		-0.5f,-0.5f, 0.5f,     1,0,0,   0,0,
		 0.5f,-0.5f, 0.5f,     0,1,0,   1,0,
		 0.5f, 0.5f, 0.5f,     0,0,1,   1,1,
		-0.5f, 0.5f, 0.5f,     1,1,0,   0,1,

		// RIGHT face
		 0.5f,-0.5f, 0.5f,     1,0,0,   0,0,
		 0.5f,-0.5f,-0.5f,     0,1,0,   1,0,
		 0.5f, 0.5f,-0.5f,     0,0,1,   1,1,
		 0.5f, 0.5f, 0.5f,     1,1,0,   0,1,

		 // BACK face
		  0.5f,-0.5f,-0.5f,     1,0,0,   0,0,
		 -0.5f,-0.5f,-0.5f,     0,1,0,   1,0,
		 -0.5f, 0.5f,-0.5f,     0,0,1,   1,1,
		  0.5f, 0.5f,-0.5f,     1,1,0,   0,1,

		  // LEFT face
		  -0.5f,-0.5f,-0.5f,     1,0,0,   0,0,
		  -0.5f,-0.5f, 0.5f,     0,1,0,   1,0,
		  -0.5f, 0.5f, 0.5f,     0,0,1,   1,1,
		  -0.5f, 0.5f,-0.5f,     1,1,0,   0,1,

		  // TOP face
		  -0.5f, 0.5f, 0.5f,     1,0,0,   0,0,
		   0.5f, 0.5f, 0.5f,     0,1,0,   1,0,
		   0.5f, 0.5f,-0.5f,     0,0,1,   1,1,
		  -0.5f, 0.5f,-0.5f,     1,1,0,   0,1,

		  // BOTTOM face
		  -0.5f,-0.5f,-0.5f,     1,0,0,   0,0,
		   0.5f,-0.5f,-0.5f,     0,1,0,   1,0,
		   0.5f,-0.5f, 0.5f,     0,0,1,   1,1,
		  -0.5f,-0.5f, 0.5f,     1,1,0,   0,1,
	};

	GLuint indices[] = {
		0,1,2, 0,2,3,        // Front
		4,5,6, 4,6,7,        // Right
		8,9,10, 8,10,11,     // Back
		12,13,14, 12,14,15,  // Left
		16,17,18, 16,18,19,  // Top
		20,21,22, 20,22,23   // Bottom
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

void Cube::RenderMeshModel()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Cube::~Cube()
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
