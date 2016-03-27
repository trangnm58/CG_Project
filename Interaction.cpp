#include "Interaction.h"

const float DEFAULT_SPIN_DEGREE = 0.1;

Interaction::Interaction() {
}

GLfloat Interaction::spin = 0;
float Interaction::spin_degree = DEFAULT_SPIN_DEGREE;
bool Interaction::spinning = false;
double Interaction::eye_x = 0;
double Interaction::eye_z = 35;

int Interaction::cur_x = 0;
int Interaction::cur_y = 0;
int Interaction::last_x = 0;
int Interaction::last_y = 0;
bool Interaction::mouseDown = false;

void Interaction::spinDisplay() {
	spin = spin + spin_degree;
	if (spin > 360) {
		spin = spin - 360;
	}
	spin = -spin * PI / 180.0;
	// calculate the eye's position
	double old_eye_x = eye_x;
	eye_x = cos(spin) * eye_x + sin(spin) * eye_z;
	eye_z = -sin(spin) * old_eye_x + cos(spin) * eye_z;
	glutPostRedisplay();
}

// Use keyboard event to animate
void Interaction::keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 32:
			if (!spinning) {
				glutIdleFunc(spinDisplay);
				spinning = true;
			} else {
				glutIdleFunc(NULL);
				spinning = false;
			}
			break;
		default:
			break;
	}
}

// Use motion of the mouse to animate
void Interaction::mouseMotion(int x, int y) {
	if (mouseDown) {
		cur_x = x;
		cur_y = y;

		int distance = cur_x - last_x;
		// calculate the spin degree depends on distance
		spin_degree = distance * 0.01;
		spinDisplay();
		spin_degree = DEFAULT_SPIN_DEGREE;
	}
}

// Use mouse left button click to animate
void Interaction::mouse(int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN) {
				// left mouse was pressed
				mouseDown = true;
				last_x = cur_x = x;
				last_y = cur_y = y;
			} else {
				// left mouse was released
				mouseDown = false;
			}
			break;
		default:
			break;
	}
}
