#ifndef Interaction_H
#define Interaction_H

#include <cmath>
#include <GL/glut.h>

#define PI 3.14159265

class Interaction {
	public:
		Interaction();
		
		static void keyboard(unsigned char key, int x, int y);
		static void mouseMotion(int x, int y);
		static void mouse(int button, int state, int x, int y);
		
		static GLfloat spin;
		static float spin_degree;
		static bool spinning;
		static double eye_x, eye_z;
		
		static int last_x, last_y, cur_x, cur_y;
		static bool mouseDown;

		static void spinDisplay();		
};

#endif // Interaction_H

