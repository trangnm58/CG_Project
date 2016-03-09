#ifndef Interaction_H
#define Interaction_H

#include <GL/glut.h>

class Interaction {
	public:
		Interaction();
		
		static void keyboard(unsigned char key, int x, int y);
		static void mouseMotion(int x, int y);
		static void mouse(int button, int state, int x, int y);
		
		static GLfloat spin;
		static float spin_degree;
		static bool spinning;
		
		static int last_x, last_y, cur_x, cur_y;
		static bool mouseDown;

		static void spinDisplay();
		
};

#endif // Interaction_H

