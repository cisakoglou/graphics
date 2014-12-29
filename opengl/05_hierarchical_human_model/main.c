
/* Interactive Figure Program from Chapter 8 using cylinders (quadrics) */
/* Style similar to robot program but here we must traverse tree to display */
/* Cylinders are displayed as filled and light/material properties */
/* are set as in sphere approximation program */

// according to figuretree.c -> left child and siblings tree

#define NULL 0

#include <GL/glut.h>

#define HEAD_HEIGHT 1.0
#define HEAD_RADIUS 0.7

#define NECK_HEIGHT 1.0
#define NECK_RADIUS 0.55

#define TORSO_HEIGHT 5.0
#define TORSO_RADIUS 1.0

#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_ARM_RADIUS  0.3
#define LOWER_ARM_RADIUS  0.3

#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_RADIUS  0.4
#define LOWER_LEG_RADIUS  0.4

#define SOLE_HEIGHT 0.4
#define SOLE_RADIUS 0.6

#define PALM_HEIGHT 0.3
#define PALM_RADIUS 0.5

void head();
void neck();
void torso();
void left_upper_arm(); void right_upper_arm(); 
void left_lower_arm(); void right_lower_arm();
void left_upper_leg(); void right_upper_leg();
void left_lower_leg(); void right_lower_leg();
void left_palm(); void right_palm();
void left_sole(); void right_sole();

typedef float point[3];

typedef struct treenode
{
  GLfloat m[16];
  void (*f)();
  struct treenode *sibling;
  struct treenode *child;
}treenode; 

typedef treenode* t_ptr;


static GLfloat theta[16] = {0.0,0.0,0.0,0.0,180.0,
							0.0,180.0,0.0,180.0,0.0,
							180.0,0.0,0.0,0.0,0.0,0.0}; /* initial joint angles 0-15*/

static GLint angle = 2;

GLUquadricObj *t, *h, *n, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *lp, *rp, *ls, *rs;

double size=1.0;

treenode torso_node, head_node,neck_node, lua_node, rua_node, lll_node, rll_node,
				lla_node, rla_node, rul_node, lul_node, lp_node, rp_node, ls_node, rs_node;

int mode_front_camera = 1; // 1 gia front provoli, 0 gia plagia
int mode_motion = 0; // 0 - default, 1 - shkwma me lugisma tou podiou, 2 - shkwma xeriwn me skupsimo laimou

void traverse(treenode* root)
{
   if(root==NULL) return;
   glPushMatrix();
   glMultMatrixf(root->m);
   root->f();
   if(root->child!=NULL) traverse(root->child);
   glPopMatrix();
   if(root->sibling!=NULL) traverse(root->sibling);
}

void torso()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(t,TORSO_RADIUS-0.15, TORSO_RADIUS, TORSO_HEIGHT,10,10);
   glPopMatrix();
}

void head()
{
   glPushMatrix();
   glTranslatef(0.0, NECK_HEIGHT+HEAD_HEIGHT,0.0);
   glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
   gluSphere(h,1.0,10,10);
   glPopMatrix();
}

void neck()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(n,NECK_RADIUS, NECK_RADIUS-0.2, NECK_HEIGHT,10,10);
   glPopMatrix();
}

void left_upper_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lua,UPPER_ARM_RADIUS+0.1, UPPER_ARM_RADIUS-0.06, UPPER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void left_lower_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lla,LOWER_ARM_RADIUS-0.06, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void right_upper_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rua,UPPER_ARM_RADIUS+0.1, UPPER_ARM_RADIUS-0.06, UPPER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void right_lower_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rla,LOWER_ARM_RADIUS-0.06, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void left_upper_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS-0.15, UPPER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void left_lower_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lll,LOWER_LEG_RADIUS-0.15, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void right_upper_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS-0.15, UPPER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void right_lower_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rll,LOWER_LEG_RADIUS-0.15, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void left_palm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lp,PALM_RADIUS, PALM_RADIUS, PALM_HEIGHT,10,10);
   glPopMatrix();
}

void right_palm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rp,PALM_RADIUS, PALM_RADIUS, PALM_HEIGHT,10,10);
   glPopMatrix();
}

void left_sole()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(ls,SOLE_RADIUS, SOLE_RADIUS, SOLE_HEIGHT,10,10);
   glPopMatrix();
}

void right_sole()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rs,SOLE_RADIUS, SOLE_RADIUS, SOLE_HEIGHT,10,10);
   glPopMatrix();
}

void setUpTree(){
		// torso
		glLoadIdentity();
        glRotatef(theta[0], 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,torso_node.m);
		torso_node.f = torso;
		torso_node.sibling = NULL;
		torso_node.child =  &neck_node;

		// neck
		glLoadIdentity();
        glTranslatef(0.0, TORSO_HEIGHT, 0.0);
        glRotatef(theta[3], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,neck_node.m);
		neck_node.f = neck;
		neck_node.sibling = &lua_node;
		neck_node.child = &head_node;

		// head
		glLoadIdentity();
        glTranslatef(0.0,-0.5*HEAD_HEIGHT, 0.0);
        glRotatef(theta[1], 1.0, 0.0, 0.0);
        glRotatef(theta[2], 0.0, 1.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,head_node.m);
		head_node.f = head;
		head_node.sibling = NULL;
		head_node.child = NULL;

		// left upper arm
		glLoadIdentity();
        glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), TORSO_HEIGHT, 0.0);
        glRotatef(theta[6], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lua_node.m);
		lua_node.f = left_upper_arm;
		lua_node.sibling =  &rua_node;
		lua_node.child = &lla_node;

		// left lower arm
		glLoadIdentity();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
        glRotatef(theta[7], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lla_node.m);
		lla_node.f = left_lower_arm;
		lla_node.sibling =  NULL;
		lla_node.child = &lp_node;

		// left palm 
		glLoadIdentity();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, -LOWER_ARM_RADIUS);
        glRotatef(theta[12], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lp_node.m);
		lp_node.f = left_palm;
		lp_node.sibling =  NULL;
		lp_node.child = NULL;

		// right upper arm
		glLoadIdentity();
        glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, TORSO_HEIGHT, 0.0);
        glRotatef(theta[4], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rua_node.m);
		rua_node.f = right_upper_arm;
		rua_node.sibling =  &lul_node;
		rua_node.child = &rla_node;


		// right lower arm
		glLoadIdentity();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
        glRotatef(theta[5], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rla_node.m);
		rla_node.f = right_lower_arm;
		rla_node.sibling =  NULL;
		rla_node.child = &rp_node;

		// right palm
		glLoadIdentity();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, -LOWER_ARM_RADIUS);
        glRotatef(theta[13], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rp_node.m);
		rp_node.f = right_palm;
		rp_node.sibling =  NULL;
		rp_node.child = NULL;

		// left upper leg
		glLoadIdentity();
        glTranslatef(-(TORSO_RADIUS/2), 0.1*UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[10], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lul_node.m);
		lul_node.f = left_upper_leg;
		lul_node.sibling =  &rul_node;
		lul_node.child = &lll_node;
		
		// left lower leg
		glLoadIdentity();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[11], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lll_node.m);
		lll_node.f = left_lower_leg;
		lll_node.sibling =  NULL;
		lll_node.child = &ls_node;

		// left sole
		glLoadIdentity();
        glTranslatef(0.0, LOWER_LEG_HEIGHT, -LOWER_LEG_RADIUS);
        glRotatef(theta[14], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,ls_node.m);
		ls_node.f = left_sole;
		ls_node.sibling =  NULL;
		ls_node.child = NULL;

		// right upper leg
		glLoadIdentity();
        glTranslatef(TORSO_RADIUS/2, 0.1*UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[8], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rul_node.m);
		rul_node.f = right_upper_leg;
		rul_node.sibling =  NULL;
		rul_node.child = &rll_node;

		// right lower leg
		glLoadIdentity();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[9], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rll_node.m);
		rll_node.f = right_lower_leg;
		rll_node.sibling =  NULL;
		rll_node.child = &rs_node;

		// right sole
		glLoadIdentity();
        glTranslatef(0.0, LOWER_LEG_HEIGHT, -LOWER_LEG_RADIUS);
        glRotatef(theta[15], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rs_node.m);
		rs_node.f = left_sole;
		rs_node.sibling =  NULL;
		rs_node.child = NULL;

		glLoadIdentity();
		
}

void moveBody()
{
	
	if ((mode_motion == 1)&&((theta[8] > 455.0) || theta[8] < 360.0)){
		// move upper leg
		theta[8] -= 0.5;
		if( theta[8] < 360.0 ) theta[8] += 360.0;
		if (theta[8] <= 455.0) mode_motion = 0;
		glLoadIdentity();
        glTranslatef(-(TORSO_RADIUS/2), 0.1*UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[8], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lul_node.m);

		// move lower leg
		theta[9] += 0.5;
        if( theta[9] > 360.0 ) theta[9] -= 360.0;
		glLoadIdentity();
        glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
        glRotatef(theta[9], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lll_node.m);

		// move sole
		theta[15] += 0.2;
        if( theta[15] > 360.0 ) theta[15] -= 360.0;
		glLoadIdentity();
        glTranslatef(0.0, LOWER_LEG_HEIGHT, -LOWER_LEG_RADIUS);
        glRotatef(theta[15], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,ls_node.m);
	}
	else if ((mode_motion == 2)&&((theta[6] > 425)||(theta[6] < 360.0))){
		// move upper arm
		theta[6] -= 0.5;
		if( theta[6] < 360.0 ) theta[6] += 360.0;
		if (theta[6] <= 425.0) mode_motion = 0;
		glLoadIdentity();
		glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), TORSO_HEIGHT, 0.0);
        glRotatef(theta[6], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lua_node.m);

		// move lower arm
		theta[7] -= 0.3;
		if( theta[7] < 360.0 ) theta[7] += 360.0;
		glLoadIdentity();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
        glRotatef(theta[7], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lla_node.m);

		// move palm
		theta[12] += 0.2;
        if( theta[12] > 360.0 ) theta[12] -= 360.0;
		glLoadIdentity();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, -LOWER_ARM_RADIUS);
        glRotatef(theta[12], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,lp_node.m);

		// same for the other arm

		// move upper arm
		theta[4] -= 0.5;
		if( theta[4] < 360.0 ) theta[4] += 360.0;
		if (theta[4] <= 425.0) mode_motion = 0;
		glLoadIdentity();
		glTranslatef((TORSO_RADIUS+UPPER_ARM_RADIUS), TORSO_HEIGHT, 0.0);
        glRotatef(theta[4], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rua_node.m);

		// move lower arm
		theta[5] -= 0.3;
		if( theta[5] < 360.0 ) theta[5] += 360.0;
		glLoadIdentity();
        glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
        glRotatef(theta[5], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rla_node.m);

		// move palm
		theta[13] += 0.2;
        if( theta[13] > 360.0 ) theta[13] -= 360.0;
		glLoadIdentity();
        glTranslatef(0.0, LOWER_ARM_HEIGHT, -LOWER_ARM_RADIUS);
        glRotatef(theta[12], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,rp_node.m);

		// neck
		theta[3] += 0.1;
        if( theta[3] > 360.0 ) theta[3] -= 360.0;
		glLoadIdentity();
        glTranslatef(0.0, TORSO_HEIGHT, 0.0);
        glRotatef(theta[3], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,neck_node.m);

		// head
		theta[1] += 0.08;
        if( theta[1] > 360.0 ) theta[1] -= 360.0;
		glLoadIdentity();
        glTranslatef(0.0,-0.5*HEAD_HEIGHT, 0.0);
        glRotatef(theta[1], 1.0, 0.0, 0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,head_node.m);
	}
	else{
	}
	glutPostRedisplay();
}


void myinit()
{

        GLfloat mat_specular[]={.0, .0, .0, 1.0};
        GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess={100.0};
        GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
        GLfloat light_diffuse[]={1.0, 0.0, 0.0, 1.0};
        GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        glEnable(GL_SMOOTH);
        glEnable(GL_LIGHTING); 
        glEnable(GL_LIGHT0);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST); 

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glColor3f(1.0, 0.0, 0.0);

	/* allocate quadrics with filled drawing style */

        h=gluNewQuadric();
        gluQuadricDrawStyle(h, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
		n=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        lua=gluNewQuadric();
        gluQuadricDrawStyle(lua, GLU_FILL);
        lla=gluNewQuadric();
        gluQuadricDrawStyle(lla, GLU_FILL);
        rua=gluNewQuadric();
        gluQuadricDrawStyle(rua, GLU_FILL);
        rla=gluNewQuadric();
        gluQuadricDrawStyle(rla, GLU_FILL);
        lul=gluNewQuadric();
        gluQuadricDrawStyle(lul, GLU_FILL);
        lll=gluNewQuadric();
        gluQuadricDrawStyle(lll, GLU_FILL);
        rul=gluNewQuadric();
        gluQuadricDrawStyle(rul, GLU_FILL);
        rll=gluNewQuadric();
        gluQuadricDrawStyle(rll, GLU_FILL);
		lp=gluNewQuadric();
        gluQuadricDrawStyle(lp, GLU_FILL);
		rp=gluNewQuadric();
        gluQuadricDrawStyle(rp, GLU_FILL);
		ls=gluNewQuadric();
        gluQuadricDrawStyle(ls, GLU_FILL);
		rs=gluNewQuadric();
        gluQuadricDrawStyle(rs, GLU_FILL);

		setUpTree();
}


void menu(int id)
{
   if(id == 6 ) exit(0);
   else if (id == 1) mode_front_camera = 0; 
   else if(id == 2) mode_front_camera = 1;
   else if(id == 4) mode_motion = 1;
   else if(id == 3){
		theta[0] = 0.0; theta[1] = 0.0; theta[2] = 0.0; theta[3] = 0.0;
		theta[4] = 180.0; theta[5] = 0.0; theta[6] = 180.0; theta[7] = 0.0;
		theta[8] = 180.0; theta[9] = 0.0; theta[10] = 180.0; theta[11] = 0.0;
		theta[12] = 0.0; theta[13] = 0.0; theta[14] = 0.0; theta[15] = 0.0;
		setUpTree();
		mode_motion = 0;
		glutPostRedisplay();
   }
   if(id == 5) mode_motion = 2;
}

void 
display(void)
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	if (mode_front_camera == 0){ // plagia 
		glRotatef(90, 0.0, 1.0, 0.0);
	}
	glMatrixMode(GL_MODELVIEW);

    traverse(&torso_node);

    glutSwapBuffers();
}

void 
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
            10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("human");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	glutIdleFunc(moveBody);

    glutCreateMenu(menu);
    glutAddMenuEntry("plagia provoli", 1);
	glutAddMenuEntry("front provoli", 2);
	glutAddMenuEntry("default", 3);
	glutAddMenuEntry("lugisma podiou", 4);
	glutAddMenuEntry("shkwma xeriwn kai skupsimo laimou", 5);
	glutAddMenuEntry("quit", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
