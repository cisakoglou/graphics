/**
 *	Xristina Isakoglou - 2056
 *	christci@csd.auth.gr
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

GLuint cubeSide;

static GLfloat a = 7.0;
GLfloat a_scaling = 3.5;
GLint a_mode = 1; // becoming bigger

static GLfloat theta_idle = 0.0;
static GLfloat a_idle = 0.0;

void render_scene_func(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// transformations for list
	
    glLoadIdentity();

	// ---- (a) ----
	glTranslatef(0.0,0.0,-70.0);
	glRotatef(theta_idle, 1.0, 2.0, 4.0);

	// ---- (b) ----
	//glTranslatef(0.0,0.0,-70.0);
	//glTranslatef(0.0, 0.0, 8.0*70.0/10.0);
	//glRotatef(theta_idle, 1.0, 2.0, 4.0);
	//glTranslatef(0.0, 0.0, -8.0*70.0/10.0);

	// scaling
	glScalef(a_scaling,a_scaling,a_scaling);
	
	glPushMatrix();
	
	//front side
	glColor3f(1.0, .0, .0);
	glCallList(cubeSide);
	glPopMatrix();
	glPushMatrix();

	//back side
	glColor3f(.0, .0, 1.0);
	glTranslatef(0.0,.0,-2.0);
	glCallList(cubeSide);
	glPopMatrix();
	glPushMatrix();

	// top side
	glColor3f(.0, 1.0, .0);
	glRotatef(-90,1.0,0.0,0.0);
	glCallList(cubeSide);
	glPopMatrix();
	glPushMatrix();

	// bottom side
	glColor3f(.0, 1.0, 1.0);
	glRotatef(90,1.0,0.0,0.0);
	glCallList(cubeSide);
	glPopMatrix();
	glPushMatrix();

	//left side
	glColor3f(1.0, 1.0, .0);
	glRotatef(-90,.0,1.0,0.0);
	glCallList(cubeSide);
	glPopMatrix();
	glPushMatrix();
	
	// right side
	glColor3f(1.0, .0, 1.0);
	glRotatef(90,.0,1.0,0.0);
	glCallList(cubeSide);
	glPopMatrix();
	
	glutSwapBuffers();
}

void spinCube()
{

	theta_idle += .5;
	if( theta_idle > 360.0 ) theta_idle -= 360.0;
	
	if (a_mode == 1){
		a_scaling += 0.01; 
		if (a_scaling > a) a_mode = 0; 
	}
	
	else {
		a_scaling -= 0.01;
		if (a_scaling < 3.5) a_mode = 1;
		
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-70.0, 70.0, -70.0 * (GLfloat) h / (GLfloat) w,
            70.0 * (GLfloat) h / (GLfloat) w, -70.0, 70.0);
    else
        glOrtho(-70.0 * (GLfloat) w / (GLfloat) h,
            70.0 * (GLfloat) w / (GLfloat) h, -70.0, 70.0, -70.0, 70.0);
    glMatrixMode(GL_MODELVIEW);
}

void my_init(void)
{ 
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-70.0, 70.0, -70.0, 70.0,-70.0,70.0);
	glMatrixMode(GL_MODELVIEW);

	cubeSide = glGenLists (1);
	glNewList(cubeSide,GL_COMPILE);
		glBegin(GL_QUADS); 
			glVertex3f(-1.0, 1.0, 1.0);          
			glVertex3f(1.0, 1.0, 1.0);          
			glVertex3f(1.0, -1.0,1.0);          
			glVertex3f(-1.0, -1.0, 1.0); 
		glEnd();
	glEndList();
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500); 
	glutCreateWindow("Graphics_Project_2");

	// register callbacks
	glutDisplayFunc(render_scene_func);
	glutIdleFunc(spinCube);
	glutReshapeFunc(myReshape);

	//set attributes
	my_init();
	
	// enter GLUT event processing cycle
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 1;

}