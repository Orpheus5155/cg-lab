#include <GL/glut.h>
#include <cmath>
#include <stdio.h>

typedef struct {
    int x, y;
} Point;

Point P[3];
int n = -1; // Initialize n to -1
float r = 0; // Radius variable

void put8pixel(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

void CircleBres(int xc, int yc, int r) {
    int x = 0, y = r, p = 5 / 4 - r;
    while (x <= y) {
        put8pixel(xc, yc, x, y);
        if (p < 0) 
            p += 2 * x + 3;
        else {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void MouseEventHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        n++;
        P[n].x = x - 300;  // Convert x to match the window coordinates
        P[n].y = 300 - y;  // Convert y to match the window coordinates
        if (n == 1) {
            r = sqrt(pow(P[1].x - P[0].x, 2) + pow(P[1].y - P[0].y, 2));  // Calculate radius
            n = -1;  // Reset n for next circle creation
        }
        glutPostRedisplay();
    }
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    if (r != 0) {
        CircleBres(P[0].x, P[0].y, r);  // Draw the circle
        r = 0;  // Reset the radius after drawing
    }
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Circle Boundary Fill");
    gluOrtho2D(-300, 300, -300, 300);
    glClearColor(0, 0, 0, 0);
    glutMouseFunc(MouseEventHandler);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}

