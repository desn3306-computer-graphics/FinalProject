#include "MaterialProperty.h"



MaterialProperty::MaterialProperty()
{
	specularIntensity = 0.5f;
	shininess = 10.0f;
}

MaterialProperty::MaterialProperty(GLfloat sIntensity, GLfloat shine)
{
	specularIntensity = sIntensity;
	shininess = shine;
}

void MaterialProperty::UseMaterialProperty(GLuint sIntensity, GLuint shine)
{
	glUniform1f(sIntensity, specularIntensity);
	glUniform1f(shine, shininess);
}

MaterialProperty::~MaterialProperty()
{
}
