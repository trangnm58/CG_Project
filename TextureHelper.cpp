#include "TextureHelper.h"

TextureHelper::TextureHelper() {
	textureWidth = 1024;
	textureHeight = 512;
}

GLuint TextureHelper::getTexture(string fileName) {
	/** REFERENCES **************************************
	*** This code is based on the answer of Dinesh Subedi at http://stackoverflow.com
	*** full link: http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
	*****************************************************/
	GLuint texture;
	unsigned char* data;
	
	FILE* file;
	file = fopen(fileName.c_str(), "rb");

	if (file == NULL) {
		cout << "Can not open " << fileName << " file" << endl;
		return 0;
	}
	data = (unsigned char*) malloc(textureWidth * textureHeight * 3);
	fread(data, textureWidth * textureHeight * 3, 1, file);
	fclose(file);
	
	for(int i = 0; i < textureWidth * textureHeight; i++) {
		int index = i * 3;
		unsigned char temp;
		temp = data[index];
		data[index] = data[index + 2];
		data[index + 2] = temp;
	}
	
	// get 1 name for the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureWidth, textureHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

	free(data);
	return texture;
}

