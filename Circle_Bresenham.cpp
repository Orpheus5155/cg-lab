#include <GL/glut.h>
#include <cmath>
#include <stack>
#include <utility>
#include <stdio.h> 

typedef struct {
	int x,y;
} Point;

Point P[3];
int n=-1;
float m=1;
float r=0;


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

void CircleBres(int xc,int yc,int r){
	int x,y,p;
	x=0; y=r; p=3-2*r;
	while (x<=y) {
		put8pixel(xc,yc,x,y);
		if (p<0) p+=4*x+6;
		else{ p+=4*(x-y)+10;
			y--;
		}
		x++;
	}
}



void MouseEventHandler(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state ==  GLUT_UP)
		{   
			n++;
			P[n].x=x-300;
			P[n].y=300-y;		
			if(n==1){
				r = sqrt(pow(P[1].x - P[0].x,2) + pow(P[1].y - P[0].y ,2));
				n=-1;
			}
			glutPostRedisplay();
		}
}
      
void MyDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	if (r != 0) {
        CircleBres(P[0].x, P[0].y, r);
        r = 0;
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

