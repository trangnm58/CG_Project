/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <GL/glut.h>

#include "FileHelper.h"
#include "Interaction.h"
#include "TextureHelper.h"
/* ----------------------------------------------------------------------- */
const string FILE_NAME = "face.dat";
const int windowWidth = 750;
const int windowHeight = 720;

float* vertices; // array of all vertices' coordinates
unsigned int* connections; // array of connections between vertices
float* textureCoords; // array of all textures' coordinates

GLuint texture; //The texture
/* ----------------------------------------------------------------------- */

// Use FileHelper to open and read the data file into 3 defined arrays
void readFaceData() {
	FileHelper fileHelper;
	fileHelper.ReadData(FILE_NAME, vertices, connections);
}

// Find the z coordinate of the front most point
float findNoseZ() {
	float nose_z = vertices[2]; // the initial value
	for (int i=0; i < FileHelper::numOfVertices; i++) {
		if (vertices[i*3 + 2] > nose_z) {
			nose_z = vertices[i*3 + 2];
		}
	}
	return nose_z;
}

// Generate texture coordinates from vertices' coordinates
void generateTextureCoords() {
	// create texture coordinates array using distance from the nose
	float nose_z = findNoseZ(); // get z coordinate of the nose

	textureCoords = new float[FileHelper::numOfVertices * 3 * 2];
	for (int i=0; i < FileHelper::numOfVertices * 3; i += 3) {
		if (abs(vertices[i]) > abs(nose_z - vertices[i + 2]) - 1.1) {
			textureCoords[i] = textureCoords[i + FileHelper::numOfVertices * 3] = vertices[i] / 10; 
		} else {
			textureCoords[i] = textureCoords[i + FileHelper::numOfVertices * 3] = (vertices[i + 2] - nose_z) / 11.2;
		}
		textureCoords[i + 1] = textureCoords[i+1 + FileHelper::numOfVertices * 3] = vertices[i + 1] / 16.5 + 0.3;
	}
}

void instruction() {
	cout << endl << endl << "************** INSTRUCTIONS **************" << endl << endl;
	cout << "- Drag the mouse to rotate the head manually." << endl;
	cout << "- Press Space Bar to toggle the rotation." << endl;
}
/* ----------------------------------------------------------------------- */
void init()  {
	glClearColor(1, 1, 1, 0);
	glColor3f(0.8, 0.6, 0.5);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	// get a texture from 'face.bmp' file
	TextureHelper textureHelper;
	texture = textureHelper.getTexture("face.bmp");
}

void setWindow() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, windowWidth / windowHeight, 10, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	setWindow();
}
/* ----------------------------------------------------------------------- */
void display()  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setWindow();
	glPushMatrix();
		gluLookAt(Interaction::eye_x, 0, Interaction::eye_z, 0, 0, 3, 0, 1, 0);

		// texture pointer of vertices
		glTexCoordPointer(3, GL_FLOAT, 0, textureCoords);
		// vertex pointer of vertices
		glVertexPointer(3, GL_FLOAT, 0, vertices);

		for (int i=0; i < FileHelper::numOfConnections * 3; i += 3) {
			glBegin(GL_TRIANGLES);
				glArrayElement(connections[i]);
				glArrayElement(connections[i + 1]);
				glArrayElement(connections[i + 2]);
			glEnd();
			// draw all right vertices
			glBegin(GL_TRIANGLES);
				glArrayElement(connections[i + FileHelper::numOfConnections * 3]);
				glArrayElement(connections[i + 1 + FileHelper::numOfConnections * 3]);
				glArrayElement(connections[i + 2 + FileHelper::numOfConnections * 3]);
			glEnd();
		}
	glPopMatrix();
    
	glFlush();
    glutSwapBuffers();
}
/* ----------------------------------------------------------------------- */
int main(int argc, char *argv[])  {
	// Initialize GLUT.
	glutInit(&argc, argv);
	// Set the mode to draw in.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Set the window size in screen pixels.
	glutInitWindowSize(windowWidth, windowHeight);
	// Set the window position in screen pixels.
	glutInitWindowPosition(600, 0);
	// Create the window.
	glutCreateWindow("Face Texturing");
	
	// Initialize some things.
	init();
	
	// print out the instruction
	instruction();
	// read the data from face.dat
	readFaceData();
	// generate the texture coordinates
	generateTextureCoords();
	
	// Set the callback funcion to call when we need to draw something.
	glutDisplayFunc(display);
	// set reshape function
	glutReshapeFunc(reshape);
	// set keyboard function
	glutKeyboardFunc(Interaction::keyboard);
	// set mouse function
	glutMouseFunc(Interaction::mouse);
	// set mouse motion function
	glutMotionFunc(Interaction::mouseMotion);
	
	// Now that we have set everything up, loop responding to events.
	glutMainLoop();
}
/* ----------------------------------------------------------------------- */

