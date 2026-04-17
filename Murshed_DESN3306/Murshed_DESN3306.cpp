#include <iostream> //Standard Header Files
#include<conio.h>
#include <iomanip>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"Dice.h" //Our Own Custom Class Headers
#include"Shader.h"
#include"GLWindow.h"
#include "RandomMode.h"
#include "Model2D.h"
#include"TetrahedronModel.h" 
#include"Camera_Control.h"
#include"Rectangle2D.h" 
#include "TextureMapping.h"
#include "ImportedModel.h"
#include<assimp/Importer.hpp> 
#include "Light.h"
#include "MaterialProperty.h"


using namespace std;


int main()
{
	GLWindow myWindow = GLWindow(1500, 1500);
	myWindow.InitGLWindow();
	Shader* myShader = new Shader();
	TetrahedronModel* myTetra = new TetrahedronModel();
	Dice* myCube = new Dice();
	Rectangle2D* my2DPlane = new Rectangle2D();

	MaterialProperty shinyObject = MaterialProperty(1.0f, 512);
	MaterialProperty dullObject = MaterialProperty(0.2f, 2);


	DirectionalLight ambientDiffuseLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.6f, 0.1f, 0.0f, -1.0f, 0.0f); //color+ambient intensity
	PointLight pointLights[MAX_POINT_LIGHTS];
	unsigned int pointLightCount = 0;

	glm::vec3 light0Position= glm::vec3(-20.0f, -5.0f, -20.0f);
	glm::vec3 light1Position = glm::vec3(20.0f, -5.0f, -20.0f);
	glm::vec3 light2Position = glm::vec3(0.0f, -5.0f, 10.0f);

	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		1.5f, 20.6f,
		light0Position.x, light0Position.y+2.5, light0Position.z,
		0.2f, 0.2f, 0.2f);
	pointLightCount++;


	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
		1.5f, 7.6f,
		light1Position.x, light1Position.y+2.5, light1Position.z,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] = PointLight(0.0f, 0.0f, 1.0f,
		1.5f, 15.6f,
		light2Position.x, light2Position.y+2.5, light2Position.z,
		0.1f, 0.1f, 0.1f);
	pointLightCount++;
	



	//world texture
	TextureMapping my2DPlaneTexture = TextureMapping((char*)"Textures/Wall.jpg");
	TextureMapping diceTexture = TextureMapping((char*)"Textures/Dice3.png");
	diceTexture.LoadTextureImage();
	my2DPlaneTexture.LoadTextureImage();

	GLfloat deltaTime, prevTime;
	deltaTime = prevTime = 0;
	Camera_Control myCamera = Camera_Control(glm::vec3(0.0f, 10.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.002f);


	//load external model
	ImportedModel* XWingModel = new ImportedModel();
	XWingModel->LoadModel("3DModels/model.obj");
	ImportedModel* streetLight = new ImportedModel();
	streetLight->LoadModel("3DModels/Light.obj");

	RandomMode* rotateXwing = new RandomMode(0.0f, 360 * 3.14159f, 0.001f, true);
	RandomMode rotationMode = RandomMode(0, 2 * 3.1415, 0.001, true);
	RandomMode translateMode = RandomMode(0, 97.99, 0.001);

	//projection matrix
	glm::mat4 projModel;

	while (!myWindow.isWindowClosed()) 	// Loop until main window is closed
	{


		//Adjusted Hardware Speed
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;
		myCamera.keyboardControl(myWindow.GetKeboardKeys(), deltaTime);
		myCamera.MouseMovementControl(myWindow.GetXChange(), myWindow.GetYChange());
		//scroll control for zoom function
		myCamera.mouseScrollControl(myWindow.getYScrollChange());
		//zoom in/out 
		projModel = glm::perspective(glm::radians(myCamera.getFov()), 1.0f, 0.1f, 100.0f);

		myShader->UseGpu();

		myShader->SetDirectionalLight(&ambientDiffuseLight);
		myShader->SetPointLights(pointLights, pointLightCount);
		ambientDiffuseLight.UseLight(myShader->GetAmbientIntensity(), myShader->GetColour(), myShader->GetDiffuseIntensity(), myShader->GetDirection());

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0, 5.0, -20.0));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f)); //scaling
		model = glm::rotate(model, rotationMode.genCurrentValue(), glm::vec3(1.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(myShader->getUnifromModel(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getUnifromProjectionModel(), 1, GL_FALSE, glm::value_ptr(projModel));
		glUniformMatrix4fv(myShader->getUnifromCameraModel(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));

		
		diceTexture.applyTexture();

		dullObject.UseMaterialProperty(myShader->GetSpecularIntensity(), myShader->GetShininess());
		//shinyObject.UseMaterialProperty(myShader->GetSpecularIntensity(), myShader->GetShininess());
		myCube->RenderMeshModel();


		glm::mat4 model4 = glm::mat4();
		model4 = glm::rotate(model4, rotateXwing->genCurrentValue(), glm::vec3(0.0f, 1.0f, 0.0f));
		model4 = glm::translate(model4, glm::vec3(0.0, 0.0, 40.0)); //translation to bring the view on the projection plane
		model4 = glm::scale(model4, glm::vec3(0.5, 0.5, 0.5));
		model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model4 = glm::rotate(model4, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		model4 = glm::translate(model4, glm::vec3(8.647037506103516f, -2.1167092323303223f, -3.1478381156921387f));
		glUniformMatrix4fv(myShader->getUnifromModel(), 1, GL_FALSE, glm::value_ptr(model4));
		glUniformMatrix4fv(myShader->getUnifromProjectionModel(), 1, GL_FALSE, glm::value_ptr(projModel));
		glUniformMatrix4fv(myShader->getUnifromCameraModel(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));

		XWingModel->RenderModel();
		
		

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0, -8.0, 0.0)); //translation to make it the background plane
		model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f)); //scaling
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		glUniformMatrix4fv(myShader->getUnifromModel(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getUnifromProjectionModel(), 1, GL_FALSE, glm::value_ptr(projModel));
		glUniformMatrix4fv(myShader->getUnifromCameraModel(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		
		my2DPlaneTexture.applyTexture();

		dullObject.UseMaterialProperty(myShader->GetSpecularIntensity(), myShader->GetShininess());
		my2DPlane->RenderMeshModel();

		

		//light-0
		model = glm::mat4();
		model = glm::translate(model, light0Position);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f)); //scaling
		
		glUniformMatrix4fv(myShader->getUnifromModel(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getUnifromProjectionModel(), 1, GL_FALSE, glm::value_ptr(projModel));
		glUniformMatrix4fv(myShader->getUnifromCameraModel(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		streetLight->RenderModel();


		//light-1
		model = glm::mat4();
		model = glm::translate(model, light1Position);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f)); //scaling

		glUniformMatrix4fv(myShader->getUnifromModel(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getUnifromProjectionModel(), 1, GL_FALSE, glm::value_ptr(projModel));
		glUniformMatrix4fv(myShader->getUnifromCameraModel(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		streetLight->RenderModel();


		//light-2
		model = glm::mat4();
		model = glm::translate(model, light2Position);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f)); //scaling

		glUniformMatrix4fv(myShader->getUnifromModel(), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(myShader->getUnifromProjectionModel(), 1, GL_FALSE, glm::value_ptr(projModel));
		glUniformMatrix4fv(myShader->getUnifromCameraModel(), 1, GL_FALSE, glm::value_ptr(myCamera.calculateCameraViewMatrix()));
		streetLight->RenderModel();



		myWindow.swapBuffers(); //Swap buffers, OpenGL main tains two Buffers, One is displayed, one is getting prepared
	}

	return 0;
}