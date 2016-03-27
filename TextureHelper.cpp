#include "TextureHelper.h"

TextureHelper::TextureHelper() {
	textureWidth = 1024;
	textureHeight = 512;
}

GLuint TextureHelper::getTexture(string fileName) {
	/** REFERENCES **************************************
	*** This code is based on the answer of Dinesh Subedi
	*** at http://stackoverflow.com
	*** full link: http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
	*****************************************************/
	GLuint texture;
	unsigned char* data;
	
	FILE * file;
	file = fopen( fileName.c_str(), "rb" );

	if (file == NULL) {
		return 0;
	}
	data = (unsigned char*) malloc(textureWidth * textureHeight * 3);
	fread(data, textureWidth * textureHeight * 3, 1, file);
	fclose(file);
	
	for(int i = 0; i < textureWidth * textureHeight ; i++) {
	   int index = i * 3;
	   unsigned char B, R;
	   B = data[index];
	   R = data[index + 2];
	
	   data[index] = R;
	   data[index + 2] = B;
	}
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureWidth, textureHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	free(data);
	return texture;
}
