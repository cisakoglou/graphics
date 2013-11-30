/**
 *   graphics/01_fractals_barnsley-fern
 *   Copyright (C) 2013 Christina Isakoglou
 *   Contact : kristaisak@gmail.com
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 */


#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846
typedef GLfloat point2[2]; 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// default values - first time run                                                                                   //
// window = 500x500                                                                                                  //
// drawing color = black                                                                                             //
// number of iterations = 50000                                                                                      //
// Shapes supported : pentagon fractal, hexagon fractal, fern                                                        //                              
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

int window;
int numberOfIterations = 50000; 

float window_width = 500.0,window_height = 500.0;
float window_width_start = 0.0,window_height_start = 0.0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// modes under which our program runs                                                                                //
// 1. pentagon_display_mode = 1 when the drawing shape is pentagon | = 0 when hexagon                                //
// 2. fern_display_mode = 1 fern is drawn instead of polugons                                                        //
// 3. rand_color = 1 when random colors are used to redraw our shape, triggered after user's choise to redraw shape  //
// with diferrent number of iterations                                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

int rand_color = 0;
int fern_display_mode = 0;
int pentagon_display_mode = 1;

double fern_zoom_scale;

int old_x,old_y;
int start_dragging = 0;// not dragging shapes by default

void fern_display(void) {
	int i;
	point2 p;
	double prob[4] = { 0.85, 0.92, 0.99, 1.00 }; //non-uniform probability
	double r,x,y;

	if (rand_color == 1){
		glColor3ub(rand()%256,rand()%256, rand()%256);
		rand_color = 0;
	}

	// random initial points
	p[0] =  (rand() / (RAND_MAX + 1.0));
	p[1] =  (rand() / (RAND_MAX + 1.0));
	
	glBegin ( GL_POINTS );
		glVertex2f((GLfloat)250+50.0*p[0],(GLfloat)50.0*p[1]);
	glEnd ( );
	
	for ( i = 0; i < numberOfIterations; i++ )
	{
		r = (rand() / (RAND_MAX + 1.0));

		if ( r < prob[0] )
		{
			x =   0.85 * p[0] + 0.04 * p[1] + 0.0;
			y = - 0.04 * p[0] + 0.85 * p[1] + 1.6;
		}
		else if ( r < prob[1] )
		{
			x =   0.20 * p[0] - 0.26 * p[1] + 0.0;
			y =   0.23 * p[0] + 0.22 * p[1] + 1.6;
		}
		else if ( r < prob[2] )
		{
			x = - 0.15 * p[0] + 0.28 * p[1] + 0.0;
			y =   0.26 * p[0] + 0.24 * p[1] + 0.44;
		}
		else
		{
			x =   0.00 * p[0] + 0.00 * p[1] + 0.0;
			y =   0.00 * p[0] + 0.16 * p[1] + 0.0;
		}

		p[0] = x;
		p[1] = y;
	
		glBegin ( GL_POINTS );
			glVertex2f((GLfloat)250+fern_zoom_scale*p[0],(GLfloat)fern_zoom_scale*p[1]); // scale and transposition in order to be visible in the center of our window
		glEnd ( );
	}  
}

void pentagon_display(){
	int n = 5; // #vertices
	int  i,j, k;
    int rand();
	point2 random={40.0,40.0};

	// calculate vertices
	float centerx = 250.0,centery = 250.0; // center the middle point of our 500x500 window - fixed point
	float radius = 250;
	float angle = 18.0*PI/180.0; 
	float angle_increment = 2.0*PI/n;
	point2 vertices[5];
    for (i = 0; i < n; i++)
	{
		vertices[i][0] = centerx + radius * cos(angle);
		vertices[i][1] = centery + radius * sin(angle);
		angle += angle_increment;
	}
       
	if (rand_color == 1){
		glColor3ub(rand()%256,rand()%256, rand()%256);
		rand_color = 0;
	}
	
	glBegin(GL_POINTS);
		for (i = 0; i < n; i++)
		{
			glVertex2fv(vertices[n]);
		}
	glEnd();
	
	for( k = 0; k < numberOfIterations; k++)
    {
		j=rand()%n; 
		random[0] = random[0] + (vertices[j][0] - random[0]) * (5.0/8.0); 
		random[1] = random[1] + (vertices[j][1] - random[1]) * (5.0/8.0); 

        glBegin(GL_POINTS);
			glVertex2fv(random); 
        glEnd();
	}	
}

void hexagon_display(){
	int n = 6; // #vertices
	int  i,j, k;
    int rand();
	point2 random={40.0,40.0};

	// calculate vertices
	float centerx = 250.0,centery = 250.0; // center the middle point of our 500x500 window - fixed point
	float radius = 250;
	float angle = 30.0*PI/180.0; // convert degrees to rad
	float angle_increment = 2.0*PI/n;
	point2 vertices[6];
    for (i = 0; i < n; i++)
	{
		vertices[i][0] = centerx + radius * cos(angle);
		vertices[i][1] = centery + radius * sin(angle);
		angle += angle_increment;
	}
       
	if (rand_color == 1){
		glColor3ub(rand()%256,rand()%256, rand()%256);
		rand_color = 0;
	}
	
	glBegin(GL_POINTS);
		for (i = 0; i < n; i++)
		{
			glVertex2fv(vertices[n]);
		}
	glEnd();

	for( k = 0; k < numberOfIterations; k++)
    {
		j=rand()%n; 
		random[0] = random[0] + (vertices[j][0] - random[0]) * (2.0/3.0); 
		random[1] = random[1] + (vertices[j][1] - random[1]) * (2.0/3.0); 

        glBegin(GL_POINTS);
			glVertex2fv(random); 
        glEnd();
	}	
}

void render_scene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	if (fern_display_mode == 0){
		if (pentagon_display_mode == 1){	
			pentagon_display();
		}
		else {
			hexagon_display();
		}
	}
	if (fern_display_mode == 1){
		fern_display();
	}
	glutSwapBuffers();
}

void my_init(void)
{ 
	glClearColor(1.0, 1.0, 1.0, 0.0); // clear with white
    glColor3f(0.0, 0.0, 0.0); // default color black of our window
	glViewport(0, 0,  glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(window_width_start, window_width, window_height_start, window_height); 
	glMatrixMode(GL_MODELVIEW);
}

void mouse_func(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		old_x=x; 
		old_y=y;
		start_dragging = 1;
	}
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP){
		start_dragging = 0;
	}
}


void motion_func (int x, int y) {
// (!) the movement of shape is implemented via projection matrix ~ camera
// (!) PROBLEM : moving a shape far away and then choosing to draw a new one will cause the new shape to be out of sight
// (!) as it was told to be drawn at the initial fixed point
// (!) SOLUTION : before the drawing of a new back, change projection matrix to its default state 

  if (start_dragging == 1) {
    int dx = old_x - x;
	int dy = old_y - y;
	window_width_start = window_width_start + dx;
	window_height_start = window_height_start - dy;
	window_width = window_width + dx;
	window_height = window_height - dy;
    
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(window_width_start, window_width,window_height_start, window_height); // (!) - PROBLEM
	glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
  }
  old_x = x;
  old_y = y;
}

void menu(int id)
{	
	if(id == 0){
		glutDestroyWindow(window);
		exit(0);
	}
	glutPostRedisplay();
}

void polygon_menu(int id)
{	
	rand_color = 0;
	fern_display_mode = 0;
	// (!) - SOLUTION
	window_width = 500.0,window_height = 500.0;
	window_width_start = 0.0,window_height_start = 0.0;
	my_init();

	if(id == 1){
		pentagon_display_mode = 1;
	}else{
		pentagon_display_mode = 0;
	}
	glutPostRedisplay();
}

void points_menu(int id)
{	
	// random color only when redrawing
	if(id == 3){
		rand_color = 1;
		numberOfIterations = 50000;
	}else if (id == 4){
		rand_color = 1;
		numberOfIterations = 100000;
	}
	else{
		rand_color = 1;
		numberOfIterations = 200000;
	}
	glutPostRedisplay();
}

void fern_menu(int id)
{
	fern_display_mode = 1;
	// (!) - SOLUTION
	window_width = 500.0,window_height = 500.0;
	window_width_start = 0.0,window_height_start = 0.0;
	my_init();

	if (id == 7){
		fern_zoom_scale = 100.0;
	}
	else {
		fern_zoom_scale = 50.0;
		rand_color = 0;
	}
	glutPostRedisplay();
}

void create_menu(void)
{
	int submenu_1,submenu_2,submenu_3,main_menu;

	submenu_1 = glutCreateMenu(polygon_menu);
	glutAddMenuEntry("pentagon", 1);
	glutAddMenuEntry("hexagon", 2);

	submenu_2 = glutCreateMenu(points_menu);
	glutAddMenuEntry("50.000", 3);
	glutAddMenuEntry("100.000", 4);
    glutAddMenuEntry("200.000", 5);

	submenu_3 =  glutCreateMenu(fern_menu);
	glutAddMenuEntry("Default size", 6);
	glutAddMenuEntry("Zoom", 7);

	main_menu = glutCreateMenu(menu);
	glutAddSubMenu("Polygon",submenu_1);
	glutAddSubMenu("# of points",submenu_2);
	glutAddSubMenu("Barnsley Fern",submenu_3);
    glutAddMenuEntry("Quit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500); 
	window = glutCreateWindow("Graphics_Project_1");
	create_menu();

	// register callbacks
	glutDisplayFunc(render_scene);
	//glutDisplayFunc(fern);
	glutMouseFunc (mouse_func);
	glutMotionFunc(motion_func);
	
	//set attributes
	my_init();
	
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;

}