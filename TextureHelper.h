#ifndef TextureHelper_H
#define TextureHelper_H

#include <fstream>
#include <iostream>
#include <GL/glut.h>

using namespace std;

class TextureHelper {
	public:
		TextureHelper();
		
		GLuint getTexture(string fileName);
		
		int textureWidth;
		int textureHeight;
};

#endif // TextureHelper_H

