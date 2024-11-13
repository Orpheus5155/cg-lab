#include <GL/glut.h>
#include <stdio.h>

// Function prototypes
void LineMidpointShallowPositive(int x1, int y1, int x2, int y2);
void LineMidpointSteepPositive(int x1, int y1, int x2, int y2);
void LineMidpointShallowNegative(int x1, int y1, int x2, int y2);
void LineMidpointSteepNegative(int x1, int y1, int x2, int y2);

typedef struct {
    int x, y;
} Point;

Point P[2];
int n = -1;
float slope;

void MouseEventHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        n++;
        P[n].x = x - 300;
        P[n].y = 300 - y;
        printf("\n n=%d x=%d y=%d", n, P[n].x, P[n].y);
        if (n == 1) {
            slope = (float)(P[1].y - P[0].y) / (P[1].x - P[0].x);
            printf("\n Slope=%f", slope);
            n = -1;
            glutPostRedisplay();
        }
    }
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    if (slope > 0 && slope <= 1) {
        LineMidpointShallowPositive(P[0].x, P[0].y, P[1].x, P[1].y);
    } else if (slope > 1) {
        LineMidpointSteepPositive(P[0].x, P[0].y, P[1].x, P[1].y);
    } else if (slope >= -1 && slope < 0) {
        LineMidpointShallowNegative(P[0].x, P[0].y, P[1].x, P[1].y);
    } else if (slope < -1) {
        LineMidpointSteepNegative(P[0].x, P[0].y, P[1].x, P[1].y);
    }

    glFlush();
}

void LineMidpointShallowPositive(int x1, int y1, int x2, int y2) {
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int d = 2 * Dy - Dx;
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (x < x2) {
        if (d < 0) {
            d += 2 * Dy;
        } else {
            d += 2 * (Dy - Dx);
            y++;
        }
        x++;
        glVertex2i(x, y);
    }
    glEnd();
}

void LineMidpointSteepPositive(int x1, int y1, int x2, int y2) {
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int d = 2 * Dx - Dy;
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (y < y2) {
        if (d < 0) {
            d += 2 * Dx;
        } else {
            d += 2 * (Dx - Dy);
            x++;
        }
        y++;
        glVertex2i(x, y);
    }
    glEnd();
}

void LineMidpointShallowNegative(int x1, int y1, int x2, int y2) {
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int d = 2 * Dy + Dx;
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (x < x2) {
        if (d < 0) {
            d += 2 * Dy;
        } else {
            d += 2 * (Dy + Dx);
            y--;
        }
        x++;
        glVertex2i(x, y);
    }
    glEnd();
}

void LineMidpointSteepNegative(int x1, int y1, int x2, int y2) {
    int Dx = x2 - x1;
    int Dy = y2 - y1;
    int d = 2 * Dx + Dy;
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (y > y2) {
        if (d < 0) {
            d += 2 * Dx;
        } else {
            d += 2 * (Dx + Dy);
            x++;
        }
        y--;
        glVertex2i(x, y);
    }
    glEnd();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Midpoint Line Drawing");
    gluOrtho2D(-300, 300, -300, 300);
    glClearColor(0, 0, 0, 0);
    glutMouseFunc(MouseEventHandler);
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}

