/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <GL/glut.h>

#include "FileHelper.h"
#include "Interaction.h"
/* ----------------------------------------------------------------------- */

const string FILE_NAME = "face.dat";

float* vertices; // array of all vertices' coordinates that were given
float* rightSideVertices; // array of all vertices' coordinates symetrical to vertices
int* connections; // array of connections between vertices that were given

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
}

void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble f, GLdouble n) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, f, n);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	setWindow(-10, 10, -10, 10, -10, 4);
}

/* ----------------------------------------------------------------------- */

void display()  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    setWindow(-10, 10, -10, 10, -10, 4);
    
    glEnableClientState(GL_VERTEX_ARRAY);
	
	glPushMatrix();
		// rotate spin degree around y (0,1,0) axis
		glRotatef(Interaction::spin, 0, 1, 0);
		
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		for (int i=0; i < FileHelper::numOfConnections * 3; i += 3) {
			glBegin(GL_LINE_LOOP);
				glArrayElement(connections[i]);
				glArrayElement(connections[i+1]);
				glArrayElement(connections[i+2]);
			glEnd();
		}
		
		glVertexPointer(3, GL_FLOAT, 0, rightSideVertices);
		for (int i=0; i < FileHelper::numOfConnections * 3; i += 3) {
			glBegin(GL_LINE_LOOP);
				glArrayElement(connections[i]);
				glArrayElement(connections[i+1]);
				glArrayElement(connections[i+2]);
			glEnd();
		}
	// go back to where you were
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
	glutInitWindowSize(720, 750);
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
