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

float* vertices; // array of all vertices' coordinates that were given
float* rightSideVertices; // array of all vertices' coordinates symetrical to vertices
unsigned int* connections; // array of connections between vertices that were given

float* textureCoords; // array of all textures' coordinates

GLuint texture; //The texture

// Use FileHelper to open and read the data file into 3 defined arrays
void readFaceData() {
	FileHelper fileHelper;
	fileHelper.ReadData(FILE_NAME, vertices, connections);
	
	// create the vertex array for the right side of the face
	rightSideVertices = new float[FileHelper::numOfVertices * 3];
	for (int i=0; i < FileHelper::numOfVertices * 3; i += 3) {
		rightSideVertices[i] = -vertices[i];
		rightSideVertices[i+1] = vertices[i+1];
		rightSideVertices[i+2] = vertices[i+2];
	}
	
	// create texture coordinates array
	textureCoords = new float[FileHelper::numOfVertices * 3];
	for (int i=0; i < FileHelper::numOfVertices * 3; i += 3) {
		textureCoords[i] = vertices[i] / 8;
		textureCoords[i+1] = vertices[i+1] / 8;
		textureCoords[i+2] = vertices[i+2] / 8;
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
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	TextureHelper textureHelper;
	texture = textureHelper.getTexture("face_texture.bmp");
}

void setWindow() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, windowWidth / windowHeight, -10, 10);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	setWindow();
}

/* ----------------------------------------------------------------------- */

void display()  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setWindow();
    
    glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		gluLookAt(Interaction::eye_x, 0, Interaction::eye_z, 0, 0, 2, 0, 1, 0);
		
		// texture pointer of left vertices
		glTexCoordPointer(3, GL_FLOAT, 0, textureCoords);
		// vertex pointer of left vertices
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		
		
		for (int i=0; i < FileHelper::numOfConnections * 3; i += 3) {
			// GL_LINE_LOOP
			glBegin(GL_TRIANGLES);
				glArrayElement(connections[i]);
				glArrayElement(connections[i+1]);
				glArrayElement(connections[i+2]);
			glEnd();
		}
		// draw all right vertices
		glVertexPointer(3, GL_FLOAT, 0, rightSideVertices);
		for (int i=0; i < FileHelper::numOfConnections * 3; i += 3) {
			glBegin(GL_TRIANGLES);
				glArrayElement(connections[i]);
				glArrayElement(connections[i+1]);
				glArrayElement(connections[i+2]);
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
