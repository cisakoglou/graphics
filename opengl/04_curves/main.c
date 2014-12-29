/**
 *	Xristina Isakoglou - 2056
 *	christci@csd.auth.gr
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <math.h>

#define D 2 // number of dimensions
#define T 20 // number of u subintervals

// window info
int window;
int ww = 500;
int wh = 500;

int mode = 1; // [1 = hermitte | 2 = interpolating cubic | 3 = bezier | 4 = 2 bezier]
int N = 4; // number of control points [mode 1,2->4, mode 3-> 7, mode 4-> 8]

static GLfloat ctrlPoints[8][3] = {{15,20, 0}, {200, 150, 0}, {30,300, 0}, {200, 220, 0},
								{250, 360, 0}, {380, 430, 0}, {300,150, 0}, {450, 100, 0}};
GLfloat temp[4][3];

// remember the moving control name
int MOVENAME = -1;
GLfloat dtangent[D];

// set up pick radius for detecting movement of a control point
int pickRadius = 30;

void printControlPoints()
{
	int i,j;
	printf("\nControl Points:\n");

	for (i = 0; i < N; i++)
	{
		printf("  ( ");
		for (j = 0; j < D; j++)
		{
		 printf("%g ",ctrlPoints[i][j]);
		}
		printf(")\n");
	}
}

void display2DControlPolyline()
{
	int i;
	glLineWidth(1.0);
	glColor3f(0.0f, 0.0f, 1.0f);
  
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < N; i++)
	{
      glVertex2i(ctrlPoints[i][0],ctrlPoints[i][1]);
	}
    glEnd();
    glFlush();
}


void display2DControlPoints()
{
	int i;
	glPointSize(4.0);
	glColor3f(.0f, .0f, .0f);

	glBegin(GL_POINTS);
	for (i = 0; i < N; i++)
	{
      glVertex2i(ctrlPoints[i][0],ctrlPoints[i][1]);
	}
    glEnd();
    glFlush();
}

void initCtrlPoints(){
	int i;
	if (mode == 1){
		// for second way [conversion to matrix]
		//b0 = p0
		//b3 = p1
		//b1 = p0+v0/3
		//ctrlPoints[1][0] =  ctrlPoints[0][0] +  (ctrlPoints[1][0]-ctrlPoints[0][0])/3;
		//ctrlPoints[1][1] =  ctrlPoints[0][1] +  (ctrlPoints[1][1]-ctrlPoints[0][1])/3;
		//b2 = p1-v1/3
		//ctrlPoints[2][0] =  ctrlPoints[3][0] -  (ctrlPoints[3][0]-ctrlPoints[2][0])/3;
		//ctrlPoints[2][1] =  ctrlPoints[3][1] -  (ctrlPoints[3][1]-ctrlPoints[2][1])/3;
	}
	else if (mode == 2){
		/*
		for (i=0;i<N;i++){
			temp[i][0] = ctrlPoints[i][0];
			temp[i][1] = ctrlPoints[i][1];
			temp[i][2] = ctrlPoints[i][2];
		} 
		ctrlPoints[0][0] = temp[0][0]; 
		ctrlPoints[0][1] = temp[0][1];

		ctrlPoints[1][0] = (-5/6)*temp[0][0] + 3*temp[1][0] + (-3/2)*temp[2][0] + (1/3)*temp[3][0];
		ctrlPoints[1][1] = (-5/6)*temp[0][1] + 3*temp[1][1] + (-3/2)*temp[2][1] + (1/3)*temp[3][1];

		ctrlPoints[2][0] = (1/3)*temp[0][0] + (-3/2)*temp[1][0] + (-3)*temp[2][0] + (-5/6)*temp[3][0]; 
		ctrlPoints[2][1] = (1/3)*temp[0][1] + (-3/2)*temp[1][1] + (-3)*temp[2][1] + (-5/6)*temp[3][1];

		ctrlPoints[3][0] = temp[3][0];
		ctrlPoints[3][1] = temp[3][0];
		*/
	}
	
	// c_{0} continuity
	else if (mode == 3){
		for (i=0;i<D;i++){
			ctrlPoints[6][i] = ctrlPoints[0][i];
		}
	}
	// c_{0} and c_{1} continuity
	else if (mode == 4){
		for (i=0;i<D;i++){
			ctrlPoints[4][i] = ctrlPoints[3][i];
			ctrlPoints[5][i] = 2*ctrlPoints[3][i]-ctrlPoints[2][i];
			dtangent[i] = abs(ctrlPoints[3][i] - ctrlPoints[2][i]);
		}
	}
}

void checkForC0Continuity(){
	if (mode == 3){
	}
	else if (mode == 4){
	
	}
	
}

void checkForC1Continuity(){
	int c=0,i;
	for (i=0;i<D;i++){
		if ((abs(ctrlPoints[4][i]-ctrlPoints[2][i]) == abs(ctrlPoints[5][i]-ctrlPoints[4][i])) && 
			(abs(ctrlPoints[3][i]-ctrlPoints[2][i]) == abs(ctrlPoints[5][i]-ctrlPoints[3][i]))) {
			c++;
		}
	}
	if (c == 2) {
		printf("it has c1 continuity\n");
	}

}

void hermite()
{
	// Calculate Hermite form with
	//	p0 = ctrlPoints[0]
	//  p1 = ctrlPoints[3]

	//  tangent "weights" chosen to show that curve can exit control polygon's convex hull
	//  tangent at p0 = 3*(ctrlPoints[1]-ctrlPoints[0])
	//  tangent at p1 = 6*(ctrlPoints[3]-ctrlPoints[2])

	GLfloat* fu =(GLfloat*) malloc(N*sizeof(GLfloat));
	GLfloat u2,u3,x,y;
	GLfloat u;
	int uInt,i;

	printf("\nCalculating Hermite Form with specific endpoint tangents...\n");
	
	// ________ 1st WAY : blending functions __________
	///*
	glLineWidth(2.0);
	glColor3f(.0f, .5f, 1.0f);

	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		u2 = u*u;
		u3 = u2*u;
		fu[0] = 2.0*u3 - 3.0*u2 + 1.0;
		fu[1] = -2.0*u3 + 3.0*u2;
		fu[2] = u3 - 2.0*u2 + u;
		fu[3] = u3 - u2;

		x = 0.0;
		y = 0.0;
	
		// p0 = ctrlPoints[0]
		x += fu[0]*ctrlPoints[0][0];
		y += fu[0]*ctrlPoints[0][1];

		// p1 = ctrlPoints[3]
		x += fu[1]*ctrlPoints[3][0];
		y += fu[1]*ctrlPoints[3][1];

	    //  tangent at p0 = ctrlPoints[1]-ctrlPoints[0]
		x += fu[2]*(3.0*(ctrlPoints[1][0]-ctrlPoints[0][0]));
		y += fu[2]*(3.0*(ctrlPoints[1][1]-ctrlPoints[0][1]));

		//  tangent at p1 = ctrlPoints[3]-ctrlPoints[2]
		x += fu[3]*(-3.0*(ctrlPoints[3][0]-ctrlPoints[2][0]));//  fu[3]*(6.0*(ctrlPoints[3][0]-ctrlPoints[2][0]))
		y += fu[3]*(-3.0*(ctrlPoints[3][1]-ctrlPoints[2][1]));

		glVertex2i(x,y);
	}
	glEnd();
	//*/

	// ________ 2nd WAY : conversion to bezier _____________
	/*

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlPoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	glLineWidth(2.0);
	glColor3f(0.0f, .5f, 1.0f);
  
	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		glEvalCoord1f(u);
	}

	glEnd();
	*/

	//draw tangents
	glLineWidth(1.0);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_STRIP);
	glVertex2i(ctrlPoints[3][0],ctrlPoints[3][1]);
	glVertex2i(ctrlPoints[2][0],ctrlPoints[2][1]);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2i(ctrlPoints[1][0],ctrlPoints[1][1]);
	glVertex2i(ctrlPoints[0][0],ctrlPoints[0][1]);
	glEnd();
	
    glFlush();
	free(fu);
}

void interpolate()
{
	// *************************** 1st way ********************* //
	///*
	int uInt,i;
	GLfloat u,x,y;
	GLfloat* bu =(GLfloat*) malloc(N*sizeof(GLfloat));
	printf("\nCalculating Interpolating Form...\n");

	glLineWidth(3.0);
	glColor3f(0.0f, 1.0f, 1.0f);
  
	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		bu[0] = (-9.0/2.0)*(u-(1.0/3.0))*(u-(2.0/3.0))*(u-1.0);
		bu[1] = (27.0/2.0)*u*(u-(2.0/3.0))*(u-1.0);
		bu[2] = (-27.0/2.0)*u*(u-(1.0/3.0))*(u-1.0);
		bu[3] = (9.0/2.0)*u*(u-(1.0/3.0))*(u-(2.0/3.0));

		x = 0.0;
		y = 0.0;

		for (i = 0; i < N; i++)
		{
			x += bu[i]*ctrlPoints[i][0];
			y += bu[i]*ctrlPoints[i][1];
		}
		glVertex2i(x,y);
	}

	glEnd();
    glFlush();
	free(bu);
	//*/

	// *************************** 2nd way[conversion to bezier] ******************* //
	/*
	int uInt,i;
	GLfloat u;
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlPoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);

	glLineWidth(3.0);
	glColor3f(0.0f, 1.0f, 1.0f);
  
	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		glEvalCoord1f(u);
	}

	glEnd();
    glFlush();

	*/
}



void bezier()
{
	int uInt;
	GLfloat u;

	printf("\nEvaluating Bezier Form ...\n");

   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 7, &ctrlPoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);

	glLineWidth(3.0);
	glColor3f(0.0f, 1.0f, 1.0f);
  
	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		glEvalCoord1f(u);
	}

	glEnd();
    glFlush();
}

void bezier2(){
	int uInt;
	GLfloat u;

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlPoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glLineWidth(3.0);
	glColor3f(0.0f, 1.0f, 1.0f);
  
	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		glEvalCoord1f(u);
	}

	glEnd();
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlPoints[4][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glLineWidth(3.0);
	glColor3f(0.0f, 1.0f, .0f);
  
	glBegin(GL_LINE_STRIP);

	for (uInt = 0; uInt <= T; uInt++)
	{
		u = uInt/(GLfloat)T;
		glEvalCoord1f(u);
	}

	glEnd();
}

void drawCurve()
{
	switch(mode){
		case 1:
			hermite();
			break;
		case 2:
			interpolate();
			break;
		case 3:
			N = 7;
			initCtrlPoints();
			bezier();
			break;
		case 4:
			N = 8;
			initCtrlPoints();
			bezier2();
			break;
	}
}

void menu(int id){
	if (id == 5){
		glutDestroyWindow(window);
		exit(0);
	}
	else {
		mode = id;
		if ((mode == 2)||(mode==1)){
			N = 4;
			initCtrlPoints();
		}
	}
	glutPostRedisplay();
}

void create_menu(void)
{

	glutCreateMenu(menu);
	glutAddMenuEntry("hermitte with 2 control points",1);
	glutAddMenuEntry("qubic interpolation with 4",2);
	glutAddMenuEntry("bezier with 7 control points",3);
	glutAddMenuEntry("2 bezier",4);
	glutAddMenuEntry("quit",5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void render_scene_func(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	drawCurve();
	display2DControlPoints();
	glFlush();
}

void reshape_func(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	ww = w;
	wh = h;
}

// mouse function
void pick_func(int button, int state, int xPosition, int yPosition)
{
	int i;
	int choiceFound = 0;
	// left mouse button down
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		GLuint newX = xPosition;
		GLuint newY = wh - yPosition;
		//printf("Pick location: x = %d   y = %d\n", newX, newY);

	// determine which control point is picked

	for (i = 0; i < N && !choiceFound; i++)
	{
		// Use globally defined pickRadius

		if ((abs(ctrlPoints[i][0] - newX) <= pickRadius) &&
		    (abs(ctrlPoints[i][1] - newY) <= pickRadius))
		{
			MOVENAME = i;
			choiceFound = 1;
			printf("Control point %d was picked.\n",MOVENAME);
		}
	}
	}

	// left mouse button up
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		MOVENAME = -1;
		if (mode == 4){
			checkForC1Continuity();
		}
	}
	glutPostRedisplay();
}

// mouse motion function
void mouse_move_func(int xPosition, int yPosition)
{
	int i;
	if (MOVENAME > -1)
	{
	 GLuint newX = xPosition;
	 GLuint newY = wh - yPosition;

	 ctrlPoints[MOVENAME][0] = newX;
	 ctrlPoints[MOVENAME][1] = newY;

	if (mode == 3){
		 // last point should be the same with the first one
		 // ctrlPoints[N-1] == ctrlPoints[0]
		if (MOVENAME==0){
			for (i=0;i<D;i++){
				ctrlPoints[N-1][i] = ctrlPoints[0][i];
			}
		}
		else if (MOVENAME == N-1){
			for (i=0;i<D;i++){
				ctrlPoints[0][i] = ctrlPoints[N-1][i];
			}
		}
	 }
	 else if (mode == 4){
		if (MOVENAME == 2){
			for (i=0;i<D;i++){
				ctrlPoints[5][i] = 2*ctrlPoints[3][i]-ctrlPoints[2][i];
				dtangent[i] = abs(ctrlPoints[3][i] - ctrlPoints[2][i]);
			}
		}
		else if (MOVENAME == 3){
			for (i=0;i<D;i++){
				ctrlPoints[4][i] = ctrlPoints[3][i];
				//ctrlPoints[2][i] = 2*ctrlPoints[3][i]-ctrlPoints[5][i];
				//ctrlPoints[5][i] = 2*ctrlPoints[3][i]-ctrlPoints[2][i];
				// define ctrlPoints[2][i]
				if (ctrlPoints[2][i] <= ctrlPoints[3][i]){
					ctrlPoints[2][i] = ctrlPoints[3][i] - dtangent[i];
				}
				else{
					ctrlPoints[2][i] = ctrlPoints[3][i] + dtangent[i];
				}
				// define ctrlPoints[5][i]
				if (ctrlPoints[5][i] >= ctrlPoints[3][i]){
					ctrlPoints[5][i] = ctrlPoints[3][i] + dtangent[i];
				}
				else{
					ctrlPoints[5][i] = ctrlPoints[3][i] - dtangent[i];
				}
			}
		}
		else if (MOVENAME == 4){
			for (i=0;i<D;i++){
				ctrlPoints[3][i] = ctrlPoints[4][i];
				ctrlPoints[2][i] = 2*ctrlPoints[3][i]-ctrlPoints[5][i];
				ctrlPoints[5][i] = 2*ctrlPoints[3][i]-ctrlPoints[2][i];
			}
		}
		else if (MOVENAME == 5){
			for (i=0;i<D;i++){
				ctrlPoints[2][i] = 2*ctrlPoints[3][i]-ctrlPoints[5][i];
				dtangent[i] = abs(ctrlPoints[3][i] - ctrlPoints[2][i]);
			}
		}
	 }
	
	glutPostRedisplay();
	}
}

void init_func(void)
{ 
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ww, 0, wh);
	glMatrixMode(GL_MODELVIEW);
	initCtrlPoints();
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(ww, wh); 
	window = glutCreateWindow("Curves");
	create_menu();

	// register callbacks
	glutDisplayFunc(render_scene_func);
	//glutReshapeFunc(reshape_func);
	glutMouseFunc(pick_func);
	glutMotionFunc(mouse_move_func);

	//set attributes
	init_func();
	glutMainLoop();

	return 0;

}