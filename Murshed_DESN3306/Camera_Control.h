#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>


class Camera_Control
{
public:
	Camera_Control();
	Camera_Control(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialKeyboardMoveSpeed);
	void keyboardControl(bool* kkeys, GLfloat deltaTime);
	void MouseMovementControl(float xoffset, float yoffset);
	void mouseScrollControl(double yoffset);
	GLfloat getFov() { return fov; }
	glm::mat4 calculateCameraViewMatrix();
	~Camera_Control();

private:
	glm::vec3 curPos;
	glm::vec3 goFront;
	glm::vec3 lookUp;
	glm::vec3 lookRight;
	glm::vec3 referenceWorldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat keyboardMoveSpeed;

	const GLfloat defaultFov = 45.0f;
	GLfloat fov = defaultFov;
	GLfloat zoomSensitivity = 1.0f;
	GLfloat minFov = 15.0f;
	GLfloat maxFov = 120.0f;

	void updateAllPositions();
};