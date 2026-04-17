#pragma once
#pragma once
#include <GL\glew.h>
class TextureMapping
{
public:
	TextureMapping();
	TextureMapping(char* myFilePath);
	bool LoadTextureImage();
	void applyTexture();
	void ClearTexture();

	~TextureMapping();
private:
	GLuint textureID;
	int width, height, bitDepth;
	char* filePathName;
	
};




