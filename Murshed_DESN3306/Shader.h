#pragma once
#include <GL\glew.h>
#include<string>
#include<fstream>
#include<iostream>
#include "DirectionalLight.h"
#include "PointLight.h"

using namespace std;

const int MAX_POINT_LIGHTS = 5;

class Shader
{
public:
	Shader();
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	string ReadFile(const char* fileDir);
	void CreateShaderProgramFromFiles(const char* vertexPath, const char* fragmentPath);
	void UseShader();
	void UseGpu();
	GLuint getUnifromModel() { return uniformModelLoc; }
	GLuint getUnifromProjectionModel() { return uniformProjectionModelLoc; }
	GLuint getUnifromCameraModel() { return uniformCameraLoc; }

	GLuint GetColour() { return uniformColour; }
	GLuint GetAmbientIntensity() { return uniformAmbientIntensity; }

	GLuint GetDiffuseIntensity() { return uniformDiffuseIntensity; }
	GLuint GetDirection() { return uniformDirection; }

	GLuint GetSpecularIntensity() { return uniformSpecularIntensity; }
	GLuint GetShininess() { return uniformShininess; }
	GLuint GetEyePosition() { return uniformEyePosition; }

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);


	~Shader();
private:
	GLuint shaderID;
	GLuint uniformModelLoc;
	GLuint uniformProjectionModelLoc;
	GLuint uniformCameraLoc;

	GLuint uniformColour, uniformAmbientIntensity;
	GLuint uniformDiffuseIntensity, uniformDirection;
	GLuint uniformSpecularIntensity, uniformShininess, uniformEyePosition;

	int pointLightCount;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	// Vertex Shader code based on GLSL version 3.30
	const char* vShader = "shaders/vShader.txt";
	// The Fragment Shader for version 3.30
	const char* fShader = "shaders/fShader.txt";
};

