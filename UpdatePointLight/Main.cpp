#include "PointLight.h"

int main()
{


	DirectionalLight ambientDiffuseLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.2f, 0.3f, 0.0f, -1.0f, 0.0f); //color+ambient intensity
	PointLight pointLights[MAX_POINT_LIGHTS];
	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.5f, 0.6f,
		5.0f, 0.0f, -10.0f,
		0.3f, 0.3f, 0.3f);
	pointLightCount++;

	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
		0.5f, 0.6f,
		-5.0f, 0.0f, -10.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] = PointLight(0.0f, 0.0f, 1.0f,
		0.7f, 1.8f,
		0.0f, 0.0f, -5.0f,
		0.1f, 0.2f, 0.3f);
	pointLightCount++;








	while (!myWindow.getShouldClose()) 	// Loop until main window is closed
	{

		myShader->UseGpu();

		myShader->SetDirectionalLight(&ambientDiffuseLight);
		myShader->SetPointLights(pointLights, pointLightCount);
		ambientDiffuseLight.UseLight(myShader->GetAmbientIntensity(), myShader->GetColour(), myShader->GetDiffuseIntensity(), myShader->GetDirection());
		


	
	}
}