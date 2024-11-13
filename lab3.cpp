#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

struct Point {
    float x, y;
};

std::vector<Point> shape;
Point translationVector, scaleCenter, rotationCenter, linePoint1, linePoint2;
bool setTranslation = false, setScale = false, setRotation = false, setReflectionLine = false;

void multiplyMatrixVector(const float matrix[3][3], float &x, float &y) {
    float tx = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * 1;
    float ty = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * 1;
    x = tx;
    y = ty;
}

void translateShape(float tx, float ty) {
    float matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {tx, ty, 1}
    };
    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}

void scaleShape(float sx, float sy, float x0, float y0) {
    for (int i = 0; i < shape.size(); ++i) {
        shape[i].x -= x0;
        shape[i].y -= y0;
    }

    float matrix[3][3] = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };

    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }

    for (int i = 0; i < shape.size(); ++i) {
        shape[i].x += x0;
        shape[i].y += y0;
    }
}

void rotateShape(float angle, float x0, float y0) {
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);

    for (int i = 0; i < shape.size(); ++i) {
        shape[i].x -= x0;
        shape[i].y -= y0;
    }

    float matrix[3][3] = {
        {cosA, sinA, 0},
        {-sinA, cosA, 0},
        {0, 0, 1}
    };

    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }

    for (int i = 0; i < shape.size(); ++i) {
        shape[i].x += x0;
        shape[i].y += y0;
    }
}

void reflectLine(float a, float b) {
    float matrix[3][3];
    float denominator = 1 + a * a;
    matrix[0][0] = (1 - a * a) / denominator;
    matrix[0][1] = (2 * a) / denominator;
    matrix[0][2] = (2 * a * b) / denominator;
    matrix[1][0] = (2 * a) / denominator;
    matrix[1][1] = (a * a - 1) / denominator;
    matrix[1][2] = (2 * b) / denominator;
    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;

    for (int i = 0; i < shape.size(); ++i) {
        multiplyMatrixVector(matrix, shape[i].x, shape[i].y);
    }
}

void drawLine(float a, float b) {
    glBegin(GL_LINES);
    float x1 = -50;
    float y1 = a * x1 + b;
    float x2 = 50;
    float y2 = a * x2 + b;

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < shape.size(); ++i) {
        glVertex2f(shape[i].x, shape[i].y);
    }
    glEnd();

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        float wx = (x / 250.0 - 1) * 100;
        float wy = (1 - y / 250.0) * 100;

        if (setTranslation) {
            translationVector = {wx, wy};
            setTranslation = false;
            translateShape(translationVector.x, translationVector.y);
        } else if (setScale) {
            scaleCenter = {wx, wy};
            setScale = false;
            scaleShape(1.1, 1.1, scaleCenter.x, scaleCenter.y);
        } else if (setRotation) {
            rotationCenter = {wx, wy};
            setRotation = false;
            rotateShape(10, rotationCenter.x, rotationCenter.y);
        } else if (setReflectionLine) {
            if (linePoint1.x == 0 && linePoint1.y == 0) {
                linePoint1 = {wx, wy};
            } else {
                linePoint2 = {wx, wy};
                float a = (linePoint2.y - linePoint1.y) / (linePoint2.x - linePoint1.x);
                float b = linePoint1.y - a * linePoint1.x;
                reflectLine(a, b);
                setReflectionLine = false;
            }
        }

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        setTranslation = true;
        std::cout << "Click to set translation vector.\n";
        break;
    case '2':
        setScale = true;
        std::cout << "Click to set scale center.\n";
        break;
    case '3':
        setRotation = true;
        std::cout << "Click to set rotation center.\n";
        break;
    case '4':
        reflectLine(0, 0); // Reflect across the X-axis
        break;
    case '5':
        reflectLine(INFINITY, 0); // Reflect across the Y-axis
        break;
    case '7':
        setReflectionLine = true;
        linePoint1 = {0, 0};
        std::cout << "Click to set two points on the reflection line.\n";
        break;
    }
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);

    shape.push_back({10, 20});
    shape.push_back({20, 0});
    shape.push_back({10, 0});
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseClick); // Register mouse click handler
    glutMainLoop();
    return 0;
}

