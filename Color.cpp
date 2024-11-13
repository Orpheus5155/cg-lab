#include <GL/glut.h>
#include <stack>

using namespace std;

void setPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void BoundaryFill(int x, int y, float fillColor[3], float boundaryColor[3]) {
    float color[3];
    getPixelColor(x, y, color);
    
    if ((color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        setPixel(x, y, fillColor[0], fillColor[1], fillColor[2]);
        BoundaryFill(x + 1, y, fillColor, boundaryColor);
        BoundaryFill(x - 1, y, fillColor, boundaryColor);
        BoundaryFill(x, y + 1, fillColor, boundaryColor);
        BoundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0); 
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(300, 200);
    glVertex2i(100, 200);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        y = windowHeight - y;

        float fillColor[3] = {1.0, 0.0, 0.0};      
        float boundaryColor[3] = {0.0, 0.0, 0.0}; 

        BoundaryFill(x, y, fillColor, boundaryColor);
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glColor3f(0.0, 0.0, 0.0); 
    gluOrtho2D(0, 400, 0, 300); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutCreateWindow("Boundary Fill using OpenGL");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);  // Ðang ký hàm x? lý chu?t
    glutMainLoop();
    return 0;
}


