#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

typedef struct {
	int x,y;
} Point;

Point P[4];
int n=-1;
float m=1;
float r=0;
int a=0, b=0;

void MouseEventHandler(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state ==  GLUT_UP)
		{   n++;
			P[n].x=x-300;
			P[n].y=300-y;		printf("\n n=%i x=%d y=%d",n,P[n].x,P[n].y);
			if(n==2){
				//m = float(P[1].y - P[0].y)/float(P[1].x - P[0].x);
				//r = sqrt(pow(P[1].x - P[0].x,2) + pow(P[1].y - P[0].y ,2));
				a = abs(P[1].x - P[0].x);
				b = abs(P[2].y - P[0].y);
				//printf("\n r=%f",r);
				n=-1;
			}
			glutPostRedisplay();
		}
}

void put4pixel	(int xc,int yc, int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x+xc, y+yc);
	glVertex2i(x+xc,-y+yc);
	glVertex2i(xc-x, yc-y);
	glVertex2i(xc-x, yc+y);
	glEnd();
}

void ElipBres(int xc,int yc, int a, int b){

	int x = 0;
	int y = b; 
	
	float x0 = a*a/sqrt(a*a + b*b); 
	float P = a*a*(1-2*b)+ b*b;
	put4pixel(xc,yc,x,y);
	while (x <= x0) 
    	{
		if (P <0)	
           P += (2*b*b)*(2*x + 3);
            
		else
           {	
            
            P += (2*b*b)*(2*x+3) + 4*a*a*(1-y);
		    y--;
		   }
		x++;
       put4pixel(xc,yc,x,y);
		}
	
	 x=a;
	 y=0;
	
	 P=b*b*(1-2*a)+ a*a;
	put4pixel(xc,yc,x,y);
	while (x > x0) 
    	{
		if (P <0)	
            P +=(2*a*a)*(2*y + 3);
		else
           {	
            P += (2*a*a)*(2*y + 3) + 4*b*b*(1-x);
            
		    x--;
		   }
		y++;
      put4pixel(xc,yc,x,y);
		}

}
void EllipsMidpoint(int xc,int yc,double a, double b )	
{	 
   	
   	int x = 0;
	int y = b; 
	
	float x0 = a*a/sqrt(a*a + b*b); 
	float P = b*b - a*a*b +a*a/4;
	put4pixel(xc,yc,x,y);
	while (x <= x0) 
    	{
		if (P <0)	
           P += (b*b)*(2*x + 3);
            
		else
           {	
            
            P += (b*b)*(2*x+3) - 2*a*a*(y-1);
		    y--;
		   }
		x++;
        put4pixel(xc,yc,x,y);
		}
	
	x=a;
	y=0;
	
	P = a*a - b*b*a +b*b/4;
	put4pixel(xc,yc,x,y);
	while (x > x0) 
    	{
		if (P <0)	
            P +=(a*a)*(2*y + 3);
		else
           {	
            P += (a*a)*(2*y+3) - 2*b*b*(x-1);
            
		    x--;
		   }
		y++;
        put4pixel(xc,yc,x,y);
		}
		
		
}

void MyDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	if(a!=0 && b!=0) {	
		ElipBres(P[0].x, P[0].y, a, b);
		a=0;
		b=0;
	}
	glFlush();
}


int main(int argc,char* arg[]){

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize (600, 600); 
	glutInitWindowPosition (10, 10); 
	glutCreateWindow("Circle 1");
	gluOrtho2D(-300, 300, -300, 300);
	glClearColor(0,0,0,0);
	glutMouseFunc(MouseEventHandler);	
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
}


