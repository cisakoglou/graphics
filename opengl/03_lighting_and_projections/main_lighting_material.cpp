/**
 *	Xristina Isakoglou - 2056
 *	christci@csd.auth.gr
 */
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

typedef float point[4];

GLfloat x_sun = -50.0;
GLfloat theta_sun = 0.0;

GLfloat theta_camera = 0.0;

GLfloat light_position[] = { x_sun, .0, .0, 1.0 };

/* initial tetrahedron */

point v[]={{0.0, 0.0, 1.0}, {0.0, 0.942809, -0.33333},
          {-0.816497, -0.471405, -0.333333}, {0.816497, -0.471405, -0.333333}};

int n=3;
int mode=2;

void cross(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* d);
void spinSunAndCamera();

void triangle( point a, point b, point c);
void normal(point p);
void divide_triangle(point a, point b, point c, int m);
void tetrahedron( int m);

void render_scene_func(void) {
	GLfloat i,j;
	GLfloat a[] = {0.0,0.0,0.0};
	GLfloat b[] = {0.0,0.0,0.0};
	GLfloat c[] = {0.0,0.0,0.0};
	GLfloat d[] = {0.0,0.0,0.0};

	GLfloat home_shininess[] = { 0.0 };
	GLfloat home_ambient[]={80.0/255.0,30.0/255.0,5.0/255.0,1.0};
	GLfloat home_diffuse[]={139.0/255.0,69.0/255.0,19.0/255.0,1.0};
	GLfloat home_specular[]={.0,.0,.0,.0};

	GLfloat roof_shininess[] = {100.0};
	GLfloat roof_ambient[]={0.1,0.1,0.1,1.0};
	GLfloat roof_diffuse[]={0.9,0.9,0.9,1.0};
	GLfloat roof_specular[]={1.0,1.0,1.0,1.0};

	GLfloat terrain_shininess[] = {0.0};
	GLfloat terrain_ambient[]={0.,0.2,0.0,1.0};
	GLfloat terrain_diffuse[]={0.2,0.8,0.1,1.0};
	GLfloat terrain_specular[]={.0,.0,.0,.0};

	GLfloat sun_shininess[] = {0.0};
	GLfloat sun_ambient[]={1.0,1.0,.0,1.0};
	GLfloat sun_diffuse[]={1.0,1.0,.0,1.0};
	GLfloat sun_specular[]={.0,.0,.0,.0};
	GLfloat sun_emission[]={.0,.1,.1,1.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(80.0,80.0,0.0,.0,.0,.0,.0,1.0,0.0);
	glRotatef(theta_camera,.0,1.0,0.0);
	glScalef(2.0,2.0,2.0);
	
	//______________________________   main home  ___________________________________//
   glMaterialfv(GL_FRONT, GL_SPECULAR, home_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, home_shininess);
   glMaterialfv(GL_FRONT, GL_AMBIENT, home_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, home_diffuse);
    // front
	glBegin(GL_POLYGON); 
		a[0] = 5.0; a[1] = 5.0; a[2] = 10.0; 
		b[0] = -5.0; b[1] = 5.0; b[2] = 10.0;
		c[0] = -5.0; c[1] = -5.0; c[2] = 10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
		glVertex3f(5.0,5.0,10.0);
		glVertex3f(-5.0,5.0,10.0);
		glVertex3f(-5.0,-5.0,10.0);
		glVertex3f(5.0,-5.0,10.0);
    glEnd();

	// bottom
	glBegin(GL_POLYGON);  
		a[0] = 5.0; a[1] = -5.0; a[2] = 10.0; 
		b[0] = 5.0; b[1] = -5.0; b[2] = -10.0;
		c[0] = -5.0; c[1] = -5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
        glVertex3f(5.0f, -5.0f,10.0f);
		glVertex3f(5.0f, -5.0f,-10.0f);
		glVertex3f(-5.0f, -5.0f,-10.0f);
		glVertex3f(-5.0f, -5.0f,10.0f);
    glEnd(); 

	// up
	glBegin(GL_POLYGON); 
		a[0] = 5.0; a[1] = 5.0; a[2] = 10.0; 
		b[0] = 5.0; b[1] = 5.0; b[2] = -10.0;
		c[0] = -5.0; c[1] = 5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
        glVertex3f(5.0,5.0,10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,10.0);
    glEnd();

	// back
	glBegin(GL_POLYGON);
		a[0] = -5.0; a[1] = -5.0; a[2] = -10.0; 
		b[0] = -5.0; b[1] = 5.0; b[2] = -10.0;
		c[0] = 5.0; c[1] = 5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
		glVertex3f(-5.0,-5.0,-10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(5.0,-5.0,-10.0);
    glEnd();

	// left
	glBegin(GL_POLYGON);
        a[0] = -5.0; a[1] = -5.0; a[2] = 10.0; 
		b[0] = -5.0; b[1] = 5.0; b[2] = 10.0;
		c[0] = -5.0; c[1] = 5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
		glVertex3f(-5.0,-5.0,10.0);
		glVertex3f(-5.0,5.0,10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,-5.0,-10.0);
    glEnd();

	// right
	glBegin(GL_POLYGON);
		a[0] = 5.0; a[1] = -5.0; a[2] = 10.0; 
		b[0] = 5.0; b[1] = -5.0; b[2] = -10.0;
		c[0] = 5.0; c[1] = 5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
        glVertex3f(5.0,-5.0,10.0);
		glVertex3f(5.0,-5.0,-10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(5.0,5.0,10.0);	
    glEnd();

	//______________________________   roof  ___________________________________//
	glMaterialfv(GL_FRONT, GL_SPECULAR, roof_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, roof_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, roof_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, roof_diffuse);

	// front roof triangle
	glBegin(GL_POLYGON);
		//glNormal3f(0.0,0.0,1.0);
		a[0] = .0;a[1] = 5.0+10.0*(sqrt(3.0)/2.0); a[2] = 10.0; 
		b[0] = -5.0; b[1] = 5.0; b[2] = 10.0;
		c[0] = 5.0; c[1] = 5.0; c[2] = 10.0; 
		cross(a,b,c,d);
		glNormal3fv(d);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0); // 5+a(sqrt(3)/2) = 13.6602540378444	
		glVertex3f(-5.0,5.0,10.0);
        glVertex3f(5.0,5.0,10.0);	
    glEnd();

	// back roof triangle
	glBegin(GL_POLYGON);
		//glNormal3f(0.0,0.0,-1.0);
		a[0] = 5.0; a[1] = 5.0; a[2] = -10.0; 
		b[0] = -5.0; b[1] = 5.0; b[2] = -10.0;
		c[0] = .0; c[1] = 5.0+10.0*(sqrt(3.0)/2.0); c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
        glVertex3f(5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
		
    glEnd();

	// left roof 
	glBegin(GL_POLYGON);  
		//glNormal3fv(calcNormal(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0,.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0));
		a[0] = .0; a[1] = 5.0+10.0*(sqrt(3.0)/2.0); a[2] = 10.0; 
		b[0] = .0; b[1] = 5.0+10.0*(sqrt(3.0)/2.0); b[2] = -10.0;
		c[0] = -5.0; c[1] = 5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
        glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
		glVertex3f(-5.0,5.0,-10.0);
		glVertex3f(-5.0,5.0,10.0);
    glEnd();

	// right roof 
	glBegin(GL_POLYGON);  
		//glNormal3fv(calcNormal(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0,5.0,5.0,10.0));
		a[0] = .0; a[1] = 5.0+10.0*(sqrt(3.0)/2.0); a[2] = 10.0;
		b[0] = 5.0; b[1] = 5.0; b[2] = 10.0;
		c[0] = 5.0; c[1] = 5.0; c[2] = -10.0;
		cross(a,b,c,d);
		glNormal3fv(d);
        glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),10.0);
		glVertex3f(5.0,5.0,10.0);
		glVertex3f(5.0,5.0,-10.0);
		glVertex3f(.0,5.0+10.0*(sqrt(3.0)/2.0),-10.0); // 5+a(sqrt(3)/2) = 13.6602540378444
    glEnd();

	//______________________________   terrain  ___________________________________//
	glMaterialfv(GL_FRONT, GL_SPECULAR, terrain_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, terrain_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, terrain_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, terrain_diffuse);
	/*
	glBegin(GL_POLYGON);  
		glNormal3fv(calcNormal(50.0,-5.0,50.0,-50.0,-5.0,50.0));
        glVertex3f(50.0,-5.0,50.0);
		glVertex3f(-50.0,-5.0,50.0);
		glVertex3f(-50.0,-5.0,-50.0);
		glVertex3f(50.0,-5.0,-50.0); 
    glEnd();
	*/
	///*
	i = -50.0;j = -50.0;
	while (i<=0.0){
		j = -50.0;
		while (j<=0.0) {
			glBegin(GL_POLYGON);  
				//glNormal3fv(calcNormal(i,-5.0,j,i+10.0,-5.0,j));
				//glNormal3f(0.0,1.0,0.0);
				c[0] = i; c[1] = -5.0; c[2] = j; 
				b[0] = i+10.0; b[1] = -5.0; b[2] = j;
				a[0] = i+10.0; a[1] = -5.0; a[2] = j+10.0;
				cross(a,b,c,d);
				glNormal3fv(d);
				glVertex3f(i,-5.0,j);
				glVertex3f(i+10.0,-5.0,j);
				glVertex3f(i+10.0,-5.0,j+10.0);
				glVertex3f(i,-5.0,j+10.0); 
			glEnd();
			j += 10.0;
		}
		i += 10.0;
	}
	i = 0.0;j = 0.0;
	while (i<=50.0){
		j = 0.0;
		while (j<=50.0) {
			glBegin(GL_POLYGON);  
				//glNormal3f(0.0,1.0,0.0);
				c[0] = i; c[1] = -5.0; c[2] = j; 
				b[0] = i+10.0; b[1] = -5.0; b[2] = j;
				a[0] = i+10.0; a[1] = -5.0; a[2] = j+10.0;
				cross(a,b,c,d);
				glNormal3fv(d);
				glVertex3f(i,-5.0,j);
				glVertex3f(i+10.0,-5.0,j);
				glVertex3f(i+10.0,-5.0,j+10.0);
				glVertex3f(i,-5.0,j+10.0); 
			glEnd();
			j += 10.0;
		}
		i += 10.0;
	}
	i = 0.0;j = -50.0;
	while (i<=50.0){
		j = -50.0;
		while (j<=0.0) {
			glBegin(GL_POLYGON);  
				//glNormal3f(0.0,1.0,0.0);
				c[0] = i; c[1] = -5.0; c[2] = j; 
				b[0] = i+10.0; b[1] = -5.0; b[2] = j;
				a[0] = i+10.0; a[1] = -5.0; a[2] = j+10.0;
				cross(a,b,c,d);
				glNormal3fv(d);
				glVertex3f(i,-5.0,j);
				glVertex3f(i+10.0,-5.0,j);
				glVertex3f(i+10.0,-5.0,j+10.0);
				glVertex3f(i,-5.0,j+10.0); 
			glEnd();
			j += 10.0;
		}
		i += 10.0;
	}
	i = -50.0;j = 0.0;
	while (i<=0.0){
		j = 0.0;
		while (j<=50.0) {
			glBegin(GL_POLYGON);  
				//glNormal3f(0.0,1.0,0.0);
				c[0] = i; c[1] = -5.0; c[2] = j; 
				b[0] = i+10.0; b[1] = -5.0; b[2] = j;
				a[0] = i+10.0; a[1] = -5.0; a[2] = j+10.0;
				cross(a,b,c,d);
				glNormal3fv(d);
				glVertex3f(i,-5.0,j);
				glVertex3f(i+10.0,-5.0,j);
				glVertex3f(i+10.0,-5.0,j+10.0);
				glVertex3f(i,-5.0,j+10.0); 
			glEnd();
			j += 10.0;
		}
		i += 10.0;
	}
	//______________________________   sun ___________________________________//

	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, sun_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
		
	// spinning

	// rotate light source
	glRotatef(theta_sun,0.0,0.0,1.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// rotate sun object
	glTranslatef(-50.0,0.0,0.0);
	glScalef(4.0,4.0,4.0);
	tetrahedron(n);

	glutSwapBuffers();
}

void cross(GLfloat* a,GLfloat* b,GLfloat* c,GLfloat* d){
	GLfloat dist;
	d[0] = (b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
	d[1] = (b[2]-a[2])*(c[0]-a[0])-(b[0]-a[0])*(c[2]-a[2]);
	d[2] = (b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0]);
	dist = sqrt(pow(d[0],2) + pow(d[1],2) + pow(d[2],2));
	d[0] /= dist; d[1] /= dist; d[2] /= dist;

}

void my_init(void)
{ 
	GLfloat light_ambient[]={192.0/255.0,192.0/255.0,192.0/255.0,1.0};

	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0,0.0,300.0);
	glMatrixMode(GL_MODELVIEW);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0,GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glEnable(GL_DEPTH_TEST);
}

void spinSunAndCamera()
{

	if (theta_sun <= -180.0){
		theta_sun = 0;
	}
	else {
		theta_sun -= .05;
	}

	if (theta_camera >= 360.0){
		theta_camera = 0.0;
	}
	else {
		theta_camera += 0.005;
	}
	glutPostRedisplay();
}

void triangle( point a, point b, point c)

/* display one triangle using a line loop for wire frame, a single
normal for constant shading, or three normals for interpolative shading */
{
    if (mode==0) glBegin(GL_LINE_LOOP);
    else glBegin(GL_POLYGON);
       if(mode==1) glNormal3fv(a);
       if(mode==2) glNormal3fv(a);
       glVertex3fv(a);
       if(mode==2) glNormal3fv(b);
       glVertex3fv(b);
       if(mode==2) glNormal3fv(c);
       glVertex3fv(c);
    glEnd();
}

void normal(point p)
{

/* normalize a vector */

    float d=0.0;
    int i;
    for(i=0; i<3; i++) d+=p[i]*p[i];
    d=sqrt(d);
    if(d>0.0) for(i=0; i<3; i++) p[i]/=d;
}

void divide_triangle(point a, point b, point c, int m)
{

/* triangle subdivision using vertex numbers
righthand rule applied to create outward pointing faces */

    point v1, v2, v3;
    int j;
    if(m>0)
    {
        for(j=0; j<3; j++) v1[j]=a[j]+b[j];
        normal(v1);
        for(j=0; j<3; j++) v2[j]=a[j]+c[j];
        normal(v2);
        for(j=0; j<3; j++) v3[j]=b[j]+c[j];
         normal(v3);
        divide_triangle(a, v1, v2, m-1);
        divide_triangle(c, v2, v3, m-1);
        divide_triangle(b, v3, v1, m-1);
        divide_triangle(v1, v3, v2, m-1);
    }
    else(triangle(a,b,c)); /* draw triangle at end of recursion */
}

void tetrahedron( int m)
{

/* Apply triangle subdivision to faces of tetrahedron */

    divide_triangle(v[0], v[1], v[2], m);
    divide_triangle(v[3], v[2], v[1], m);
    divide_triangle(v[0], v[3], v[1], m);
    divide_triangle(v[0], v[2], v[3], m);
}


int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500); 
	glutCreateWindow("Graphics_Project_3_lighting");

	// register callbacks
	glutDisplayFunc(render_scene_func);
	glutIdleFunc(spinSunAndCamera);
	//glutReshapeFunc(myReshape);

	//set attributes
	my_init();
	
	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;

}