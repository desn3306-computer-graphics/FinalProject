#include "GLWindow.h"



GLWindow::GLWindow()
{
	width = 1000;
	height = 1000;
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

GLWindow::~GLWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

int GLWindow::InitGLWindow()
{
	// Initialise GLFW
	if (!glfwInit())  //initializes OpenGL Window System
	{
		printf("GLFW initialisation failed!");
		glfwTerminate(); //terminate due to error
		return 1;
	}

	// Setup GLFW window properties and version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Major and minor version is 3.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  //
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core Profile means No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 	// Allow Forward Compatbility

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Welcome to DESN3306!", NULL, NULL); // Create Main Window

	


	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate(); //terminate due to error
		return 1;
	}
	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); //bufferwidth and bufferHeight is system dependent so, load them.
	glfwMakeContextCurrent(mainWindow); // Set mainWindow as context for GLEW
	
	glEnable(GL_DEPTH_TEST);
	
	glewExperimental = GL_TRUE; 	// Allow modern features


	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);  //clear resources already allocated
		glfwTerminate();  //terminate due to error
		return 1;
	}

	glViewport(0, 0, bufferWidth, bufferHeight); // Setup the Viewport dimension





	// Handle Keyboard keys 
	glfwSetKeyCallback(mainWindow, handleKeyboardKeys);
	// Handle Mouse Movement
	glfwSetCursorPosCallback(mainWindow, handleMouseMovements);
	// Handle Mouse Scroll
	glfwSetScrollCallback(mainWindow, handleMouseScroll);
	//add window input listener for all callbacks 
	glfwSetWindowUserPointer(mainWindow, this);


	return 0;
}

void GLWindow::handleKeyboardKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	GLWindow* curWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 512)
	{
		if (action == GLFW_PRESS)
		{
			curWindow->kkeys[key] = true;    //use a bool array to examine which keys are pressed
			cout << "Keyboard key: (" << key << ") is pressed" << endl;
		}
		else if (action == GLFW_RELEASE)
		{
			curWindow->kkeys[key] = false;   //status is false once the key is released  
			cout << "Keyboard key: (" << key << ") is released" << endl;
		}
	}
}


void GLWindow::handleMouseMovements(GLFWwindow* window, double xPos, double yPos)
{
	GLWindow* curWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window)); 	if (curWindow->initMouse)    //initMouse is true when the program first runs
	{
		curWindow->prevX = xPos;     //update previous position
		curWindow->prevY = yPos;
		curWindow->initMouse = false;
	}
	curWindow->xChange = xPos - curWindow->prevX;   //mouse motion change along x direction
	curWindow->yChange = curWindow->prevY - yPos; //mouse motion change along y direction
	curWindow->prevX = xPos;
	curWindow->prevY = yPos;
	cout << "Mouse Movement(" << curWindow->xChange << "," << curWindow->yChange << ")" << endl;
}
void GLWindow::handleMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	GLWindow* curWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
	curWindow->yScrollChange = yoffset;

	cout << "Mouse Scroll(" << yoffset << ")" << endl;
}
