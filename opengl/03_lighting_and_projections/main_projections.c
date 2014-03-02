/**
 *	Xristina Isakoglou - 2056
 *	christci@csd.auth.gr
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

void render_scene_func(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
	// axes are ten units long.
	glBegin(GL_LINES);
		glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(20, 0, 0);
		glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 20, 0);
		glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 20);
	glEnd();
	
	// bottom
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0f, -5.0f,10.0f);
		glVertex3f(5.0f, -5.0f,-10.0f);
		glVertex3f(-5.0f, -5.0f,-10.0f);
		glVertex3f(-5.0f, -5.0f,10.0f);
    glEnd(); 
	// up
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,5.0,10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,10.0);
    glEnd();
	// front
	glColor3f(.0, 1.0, 0.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,-5.0,10.0);
		glVertex3f(5.0,5.0,10.0);
		glVertex3f(-5.0,5.0,10.0);
		glVertex3f(-5.0,-5.0,10.0);
    glEnd();
	// back
	glColor3f(1.0, .0, 0.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,-5.0,-10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,-5.0,-10.0);
    glEnd();
	// left
	glColor3f(.0, .0, 1.0);
	glBegin(GL_POLYGON);  
        glVertex3f(-5.0,-5.0,10.0);
		glVertex3f(-5.0,5.0,10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,-5.0,-10.0);
    glEnd();
	// right
	glColor3f(.0, 1.0, 1.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,-5.0,10.0);
		glVertex3f(5.0,5.0,10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(5.0,-5.0,-10.0);
    glEnd();
	// front roof triangle
	glColor3f(1.0, 1.0, .5);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,5.0,10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
		glVertex3f(-5.0,5.0,10.0);
    glEnd();
	// back roof triangle
	glColor3f(1.0, 1.0, .5);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,5.0,-10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
		glVertex3f(-5.0,5.0,-10.0);
    glEnd();
	// left roof 
	glColor3f(1.0, 1.0, .5);
	glBegin(GL_POLYGON);  
        glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,10.0);
    glEnd();
	// right roof 
	glColor3f(1.0, 1.0, .5);
	glBegin(GL_POLYGON);  
        glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(5.0,5.0,10.0);
    glEnd();

	/*cube 
	// bottom
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0f, -5.0f,5.0f);
		glVertex3f(5.0f, -5.0f,-5.0f);
		glVertex3f(-5.0f, -5.0f,-5.0f);
		glVertex3f(-5.0f, -5.0f,5.0f);
    glEnd(); 
	// up
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,5.0,5.0);
		glVertex3f(5.0,5.0,-5.0);
		glVertex3f(-5.0,5.0,-5.0);
		glVertex3f(-5.0,5.0,5.0);
    glEnd();
	// front
	glColor3f(.0, 1.0, 0.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,-5.0,5.0);
		glVertex3f(5.0,5.0,5.0);
		glVertex3f(-5.0,5.0,5.0);
		glVertex3f(-5.0,-5.0,5.0);
    glEnd();
	// back
	glColor3f(1.0, .0, 0.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,-5.0,-5.0);
		glVertex3f(5.0,5.0,-5.0);
		glVertex3f(-5.0,5.0,-5.0);
		glVertex3f(-5.0,-5.0,-5.0);
    glEnd();
	// left
	glColor3f(.0, .0, 1.0);
	glBegin(GL_POLYGON);  
        glVertex3f(-5.0,-5.0,5.0);
		glVertex3f(-5.0,5.0,5.0);
		glVertex3f(-5.0,5.0,-5.0);
		glVertex3f(-5.0,-5.0,-5.0);
    glEnd();
	// right
	glColor3f(.0, 1.0, 1.0);
	glBegin(GL_POLYGON);  
        glVertex3f(5.0,-5.0,5.0);
		glVertex3f(5.0,5.0,5.0);
		glVertex3f(5.0,5.0,-5.0);
		glVertex3f(5.0,-5.0,-5.0);
    glEnd();
	*/
	glutSwapBuffers();
}

void my_init(void)
{ 
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-30.0, 30.0, -30.0, 30.0,-60.0,60.0);
	glMatrixMode(GL_MODELVIEW);
}

void menu(int id){
	double dist;
	if (id == 5){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.0, 1.0, 1.0, 40.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(sqrt(2.0)/2.0*30.0, 0.0 ,sqrt(2.0)/2.0*30.0, 0.0, 0.0, 0.0, 0.0, 1.0,  0.0);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-30.0, 30.0, -30.0, 30.0,-60.0,60.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (id == 2){
			// katopsi
			glRotatef(90,1,0,0);
		}
		else if (id == 3){
			// deksia opsi 
			glRotatef(-90,0,1,0);
		}
		else if (id == 4) {
			// isometriki
			gluLookAt(5.0 + sqrt(2.0)/2.0*20.0, 10.0 + sqrt(2.0)/2.0*20.0, 5.0 + sqrt(2.0)/2.0*20.0, 0.0, 0.0, 0.0, 0.0, 1.0,  0.0);
			//gluLookAt(5.0 + sqrt(20.0/3.0), 5.0 + sqrt(20.0/3.0), 10.0 + sqrt(20.0/3.0), 0.0, 0.0, 0.0, 0.0, 1.0,  0.0);

			// --- cube test --- //
			// diagonal point
			//gluLookAt(5.0 + sqrt(2.0)/2.0*20.0, 5.0 + sqrt(2.0)/2.0*20.0, 5.0 + sqrt(2.0)/2.0*20.0, 0.0, 0.0, 0.0, 0.0, 1.0,  0.0);
			// dia 3
			//gluLookAt(5.0 + sqrt(20.0/3.0), 5.0 + sqrt(20.0/3.0), 5.0 + sqrt(20.0/3.0), 0.0, 0.0, 0.0, 0.0, 1.0,  0.0);
		}
	}
	glutPostRedisplay();
}

void create_menu(void)
{

	glutCreateMenu(menu);
	glutAddMenuEntry("prosopsi",1);
	glutAddMenuEntry("katopsi",2);
	glutAddMenuEntry("deksia opsi",3);
	glutAddMenuEntry("isometriki",4);
	glutAddMenuEntry("perspective",5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500); 
	glutCreateWindow("Graphics_Project_3");
	create_menu();

	// register callbacks
	glutDisplayFunc(render_scene_func);

	//set attributes
	my_init();
	
	// enter GLUT event processing cycle
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;

}