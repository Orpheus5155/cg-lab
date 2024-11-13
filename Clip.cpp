#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>


#define  INC 10
#define M_PI 3.14159265358979323846

typedef struct {
	int x,y;
} Point;

Point A,B, wmax, wmin;;
float goc;
char chuot;

//-----------------------------------------

void KhoiTao(){
	glClearColor(0,0,0,0);
	glLineWidth(2);

	wmin.x=0;wmin.y=0;
	wmax.x=200;wmax.y=120;
	A.x=300;	A.y=200;
	B.x=50;		B.y=-100;

	goc=0;
	chuot=0;
}
int Ma(Point M){
	int m=0;
	if(M.x<wmin.x) m |=1;
	if(M.x>wmax.x) m |=2;
	if(M.y<wmin.y) m |=4;
	if(M.y>wmax.y) m |=8;
	return m;
}
void HoanVi(Point *A,Point *B){
	Point T;
	T=*A;	*A=*B;	*B=T;
}
Point Xoay(Point A,int g)
{
	float goc_rad =g * M_PI/180;
	Point T;
	T.x=A.x*cos(goc_rad)-A.y*sin(goc_rad);
	T.y=A.x*sin(goc_rad)+A.y*cos(goc_rad);
	return T;
}
void VeDuongThang(Point A,Point B){
	glBegin(GL_LINES);
	glVertex2i(A.x,A.y);
	glVertex2i(B.x,B.y);
	glEnd();
}
void VeHCN(Point wmin,Point wmax,int g)
{
	Point A,B,C,D;	
	A=wmin;
	C=wmax;
	B.x=wmax.x; B.y=wmin.y;
	D.x=wmin.x; D.y=wmax.y;
	
	A=Xoay(A,g);
	B=Xoay(B,g);
	C=Xoay(C,g);
	D=Xoay(D,g);
	
	glBegin(GL_LINE_LOOP);
	glVertex2i(A.x,A.y);
	glVertex2i(B.x,B.y);
	glVertex2i(C.x,C.y);
	glVertex2i(D.x,D.y);
	glEnd();
	
}

void ClipCohen(Point A,Point B,Point wmin,Point wmax,int g){
	int thoat=0 , ve=1;
	double m;
	
	while(thoat==0){
		if((Ma(A)|Ma(B))==0)	thoat=1;	// A va B nam trong vung cn ma(A)=ma(B)=0000
		else if((Ma(A) & Ma(B))!=0)			// AB nam hoan toan ben ngoai vung cn
		{
			thoat =1;		ve=0;
		}else{
			if(Ma(A)==0)	HoanVi(&A,&B);	//A nam trong vung cn
			if(A.x==B.x)					// A va B cung nam doc
			{
				if(A.y>wmax.y)	A.y=wmax.y;	// 
				else A.y=wmin.y;
			}
			else 
			{
				m=(double)(B.y-A.y)/(B.x-A.x);
				if(A.x<wmin.x)
				{
					A.y=A.y+(wmin.x-A.x)*m;
					A.x=wmin.x;
				}else if(A.x>wmax.x)
				{
					A.y=A.y+(wmax.x-A.x)*m;
					A.x=wmax.x;
				}else if(A.y<wmin.y)
				{
					A.x=A.x+(wmin.y-A.y)/m;
					A.y=wmin.y;
				}else if(A.y>wmax.y)
				{
					A.x=A.x+(wmax.y-A.y)/m;
					A.y=wmax.y;
				}
			}

		}
	}
	if(ve) VeDuongThang(Xoay(A,g),Xoay(B,g));
}
void XenHinhNhiPhan(Point A,Point B,Point wmin,Point wmax,int g){
	Point P,Q,M;
	
	if((Ma(A)|Ma(B))==0) VeDuongThang(Xoay(A,g),Xoay(B,g));
	if((Ma(A)&Ma(B))!=0) return ;
	if((Ma(A)!=0) &&(Ma(B)==0))	HoanVi(&A,&B);
	if((Ma(A)==0) &&(Ma(B)!=0)) 
	{
		P=A;Q=B;
		while((abs(P.x-Q.x)+abs(P.y-Q.y))>2)
		{
			M.x=(P.x+Q.x)/2;
			M.y=(P.y+Q.y)/2;
			if(Ma(M)==0)	P=M;
			else			Q=M;				
		}
		VeDuongThang(Xoay(A,g),Xoay(P,g));
	}
	if((Ma(A)!=0)&&(Ma(B)!=0)&&((Ma(A) & Ma(B))==0))
	{
		P=A;Q=B;
		M.x=(P.x+Q.x)/2;
		M.y=(P.y+Q.y)/2;

		while(( Ma(M)!=0) && ((abs(P.x-Q.x)+abs(P.y-Q.y))>2))
		{
			if((Ma(P)& Ma(M)) !=0)	P=M;
			else Q=M;
			M.x=(P.x+Q.x)/2;
			M.y=(P.y+Q.y)/2;			
		}
		if(Ma(M)==0)
		{
			XenHinhNhiPhan(P,M,wmin,wmax,g);
			XenHinhNhiPhan(M,Q,wmin,wmax,g);
		}
	}
}

void Mydisplay(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(0.0, 1.0, 0.0);
	VeHCN(wmin,wmax,goc);
	
	glColor3f(0.0, 0.0, 1.0);
	VeDuongThang(A,B);
	
	glColor3f(1.0, 0.0, 0.0);
	//ClipCohen(Xoay(A,-goc),Xoay(B,-goc),wmin,wmax,goc);
	XenHinhNhiPhan(Xoay(A,-goc),Xoay(B,-goc),wmin,wmax,goc);
	
	glFlush();
}

void KeyboardEventHandler(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		goc += INC;
		if(goc >360) goc=0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		goc -= INC;
		if(goc <0) goc=360;
		glutPostRedisplay();
		break;
	}
}

void MouseEventHandler(int button, int state, int x, int y)
{
	
	if(button == GLUT_LEFT_BUTTON && state ==  GLUT_UP)
		if(chuot==0)
		{
			A.x=x-300;
			A.y=300-y;		
			chuot=1;
		}
	else
		{
			B.x=x-300;
			B.y=300-y;	
			chuot=0;
			glutPostRedisplay();
		}
	
}
//-----------------------------------------
int main(int argc,char* arg[]){

	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize (600, 600); 
	glutInitWindowPosition (10, 10); 
	glutCreateWindow("Thuat Toan Xen Hinh");
	gluOrtho2D(-300, 300, -300, 300);
	KhoiTao();
	glutMouseFunc(MouseEventHandler);	
	glutDisplayFunc(Mydisplay);
	glutSpecialFunc(KeyboardEventHandler);
	glutMainLoop();
}

