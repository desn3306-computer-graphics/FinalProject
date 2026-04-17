#pragma once
#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include<iostream>

using namespace std;

class GLWindow
{
public:
	GLWindow();
	GLWindow(GLint windowWidth, GLint windowHeight);
	int InitGLWindow();
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	bool isWindowClosed() { return glfwWindowShouldClose(mainWindow); }
	void swapBuffers() { glUseProgram(0); glfwSwapBuffers(mainWindow); }
	bool* GetKeboardKeys() { return kkeys; }
	GLfloat GetXChange() {
		GLfloat horizontalMouseMovement = xChange;
		xChange = 0;
		return horizontalMouseMovement;
	}
	GLfloat GetYChange() {
		GLfloat verticalMouseMovement = yChange;
		yChange = 0;
		return verticalMouseMovement;
	}
	static void handleKeyboardKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouseMovements(GLFWwindow* window, double xPos, double yPos);
	~GLWindow();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;

	//for keyboard key press detection
	bool kkeys[512];

	//for mouse movement
	bool initMouse = true;
	GLfloat prevX;
	GLfloat prevY;
	GLfloat xChange;
	GLfloat yChange;

};

