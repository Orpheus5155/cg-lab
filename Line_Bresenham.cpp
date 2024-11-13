#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
using std::abs;
typedef struct {
	int x, y;
} Point;

Point P[2];
int n = -1;

void DrawBresenhamLine(int x1, int y1, int x2, int y2) {
	int Dx = x2 - x1;
	int Dy = y2 - y1;
	int x = x1, y = y1;
	int absDx = abs(Dx), absDy = abs(Dy);
	int const1, const2, P;

	glBegin(GL_POINTS);

	if (absDy <= absDx) { // Slope between -1 and 1
		const1 = 2 * absDy;
		const2 = 2 * (absDy - absDx);
		P = 2 * absDy - absDx;

		while (x <= x2) {
			glVertex3i(x, y, 0);
			if (P < 0)
				P += const1;
			else {
				P += const2;
				y += (Dy >= 0) ? 1 : -1;
			}
			x++;
		}
	} else { // Slope is greater than 1 or less than -1
		const1 = 2 * absDx;
		const2 = 2 * (absDx - absDy);
		P = 2 * absDx - absDy;

		while (y != y2) {
			glVertex3i(x, y, 0);
			if (P < 0)
				P += const1;
			else {
				P += const2;
				x += (Dx >= 0) ? 1 : -1;
			}
			y += (Dy >= 0) ? 1 : -1;
		}
	}
	glEnd();
}

void MouseEventHandler(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		n++;
		P[n].x = x - 300;
		P[n].y = 300 - y;
		printf("\n n=%i x=%d y=%d", n, P[n].x, P[n].y);
		if (n == 1) {
			glutPostRedisplay();
			n = -1;
		}
	}
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	DrawBresenhamLine(P[0].x, P[0].y, P[1].x, P[1].y);
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Bresenham Line");
	gluOrtho2D(-300, 300, -300, 300);
	glClearColor(0, 0, 0, 0);
	glutMouseFunc(MouseEventHandler);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
}

