#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bitmap.h"
#include "display_lists.cpp"

#define PI 3.1415926535898
#define DEGREE PI/180.0

// NURB 1
#define BOX 1
#define GROUND 2
#define CONC 3
#define SPIKES 4
#define FIR_F 5
#define FIRS 6
#define GROUND_CONCRETE 7
#define CONCRETES 8
#define DISKS 9
#define CHARS 10
#define SKY 11
#define ROTOR 12



/*********************************************/
/** Használható billentyûk a key eljárásban **/
/*********************************************/

static int WIDTH, HEIGHT;
static double movX = -2.0, movY = -1.5, movZ = 45;
static short int fog = 1, _scissor_ = 0, lights = 0, menu = 1;
static int NURB;
static GLuint *text = new GLuint[9];
static int *dlist = new int[20];
static float szog = 0.0, szog_2 = 0.0, szog_nurbs = 0.0, forw = 0.0, rot = 0.0, ver = 0.0, ver_look = 0.0;
static double X = 0.0, Y = 0.0, Z = 0.0, rotY = 0.0;

static GLUquadricObj* qobj = gluNewQuadric();

GLfloat ctlpoints[4][4][3];
//int showPoints = 0;
GLUnurbsObj *theNurb;


static int chars;
GLubyte space[] =
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

GLubyte letters[][13] = {
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
    {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
    {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
    {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
    {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
    {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
    {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
    {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
    {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
    {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
    {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

GLuint fontOffset;

static void makeRasterFont( void )
{
    GLuint i, j;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    fontOffset = glGenLists (128);
    for (i = 0, j = 'A'; i < 26; i++,j++)
    {
        glNewList(fontOffset + j, GL_COMPILE);
            glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
        glEndList();
    }

    glNewList(fontOffset + ' ', GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
    glEndList();
}

static void printString( char *s )
{
    glPushAttrib (GL_LIST_BIT);
        glListBase(fontOffset);
        glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
    glPopAttrib ();
}

static void CharList() 
{
	makeRasterFont();
    //glClearColor(0.0, 0.0, 0.0, 0.0);

	// chars
    dlist[0] = glGenLists (0);
    glNewList (dlist[CHARS], GL_COMPILE); /// Feliratok display list-ben
        glColor3d(1.0, 1.0, 1.0);
        glRasterPos2i (530, 770);
        printString("OPENGL BEADANDO");
        glRasterPos2i (20, 740);
        printString("HASZNALHATO BILLENTYUK");
        glRasterPos2i (80, 720);
        printString("MOZGAS");
		glRasterPos2i (60, 700);
		printString("W A S D E Q");
		glRasterPos2i (80, 660);
		printString("FENYEK");
		glRasterPos2i (100, 640);
		printString("M");
		glRasterPos2i (80, 600);
		printString("SCISSOR");
		glRasterPos2i (100, 580);
		printString("X");
        glRasterPos2i (1000, 740);
        printString("FELIRATOK MEGJELENITESE");
        glRasterPos2i (1100, 720);
        printString("SPACE");
        glFlush();
    glEndList();
}

static void theNurbList()
{
    GLfloat knots[14] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 4.0, 5.9, 6.0, 6.0, 6.0, 6.0};
	  GLfloat tcoords [ 2 ][ 2 ][ 2 ] = { {{0, 0}, {0, 100}},{{100 ,0}, {100, 100}} };
	  GLfloat ctlpoints[10][10][3];
    float tknots[4] = {0, 0, 1, 1.0};

	GLUnurbsObj * theNurb = gluNewNurbsRenderer();

	GLfloat x = -1, z = -1;
    for (int u = 0; u < 10; u++)
    {
        x = -1;
        for (int v = 0; v < 10; v++)
        {
            ctlpoints[u][v][0] = x;
            ctlpoints[u][v][2] = z;
            if((u > 1) && (u < 8) && (v > 1) && (v < 8) ) 
				ctlpoints[u][v][1] = cos(double(u*v)) * sin(double(v*v)) + 0.1;
            else ctlpoints[u][v][1] = -1;
            x+=0.2;
        }
        z += 0.2;
    }

	NURB = glGenLists(11);
	glNewList(NURB, GL_COMPILE);
        glPushMatrix();
            /**/
            gluBeginSurface(theNurb);
                gluNurbsSurface( theNurb, 14, knots, 14, knots, 10 * 3, 3, 
                                 &ctlpoints[0][0][0], 6, 6, GL_MAP2_VERTEX_3 );
				gluNurbsSurface( theNurb, 14, knots, 14, knots, 10 * 3, 3, 
				                 &ctlpoints[0][0][0], 6, 6, GL_MAP2_NORMAL );
                gluNurbsSurface( theNurb, 4,  tknots, 4, tknots, 2 * 2, 2, 
                                 &tcoords[0][0][0], 3, 3, GL_MAP2_TEXTURE_COORD_2 );
            gluEndSurface(theNurb);
        glPopMatrix();
	glEndList();
}

static void LoadTextures() 
{
	text[0] = Bitmap::loadTexture("textures/red_dirty.bmp", true);
	text[1] = Bitmap::loadTexture("textures/blue_dirty.bmp", true);
	text[2] = Bitmap::loadTexture("textures/sky_stars.bmp", true);
	text[3] = Bitmap::loadTexture("textures/green_dirty.bmp", true);
	text[4] = Bitmap::loadTexture("textures/wood01.bmp", true);
	text[5] = Bitmap::loadTexture("textures/ut.bmp", true);
	text[7] = Bitmap::loadTexture("textures/wood3.bmp", true);
	text[6] = Bitmap::loadTexture("textures/grass.bmp", true);
	text[8] = Bitmap::loadTexture("textures/beton.bmp", true);
}

static void init() 
{
    glEnable (GL_SCISSOR_TEST); 
    glEnable (GL_LIGHT0);
    glEnable (GL_NORMALIZE);
    glEnable (GL_COLOR_MATERIAL);
    glEnable (GL_DEPTH);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_FOG);
	glEnable (GL_TEXTURE);
	glEnable (GL_TEXTURE_2D);
 /** glClearDepth(GLclampd depth); **/
  //  glClearDepth(GL_ACCUM_RED_BITS);
 /** glDepthMask(GLboolean flag); **/
    glDepthMask(GL_TRUE);  ///////
 /** glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha); **/
    glColorMask( 1.0, 1.0, 1.0, 0.5); //////////////////////////////////////////
 
	// **  FÉNY ** //
    GLfloat light_ambient[]  = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[]  = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 0.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 10.0, 1.0, 1.0 };
    glLightfv (GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);
	// ************ //

	/** ANYAGTULAJDONSÁG **/
    GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 50.0f };
    glMaterialfv (GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, high_shininess);
	/***********************/

	/** KÖD **/
	GLfloat fogColor[4] = {0.8, 0.8, 0.8, 1.0};
    glFogf (GL_FOG_MODE, GL_LINEAR);
    glFogf (GL_FOG_DENSITY, 0.1);
	glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_START, 30.0);
    glFogf (GL_FOG_END, 200.0);
	/*********/

	theNurbList();
	CharList();
	DisplayLists((int *)dlist, (GLuint *)text, qobj);
	
	//glShadeModel (GL_SMOOTH);
	gluQuadricDrawStyle(qobj, GLU_FILL);
}

static void display( void ) 
{

    const double t = glutGet( GLUT_ELAPSED_TIME ) / 1000.0;
    const double a = t*90.0;
	/** glClear(GLbitfield mask); ************************/
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45.0, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1, 1000.0);
	glMatrixMode (GL_MODELVIEW);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluQuadricTexture (qobj, 1);

	// doboz
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, text[7]);
		glCallList(dlist[BOX]);
	glPopMatrix();


    glPushMatrix();
		glTranslated (-2, 10., -50);
		glBindTexture ( GL_TEXTURE_2D, text[1] );
		glCallList (dlist[SPIKES]);
		glRotated (90, 0, 0, 1);
		glTranslated (-7, 7.0, 0);
		glCallList (dlist[SPIKES]);
		glTranslated (0, -14.5, 0);
		glRotated (180, 0, 0, 1);
		glCallList (dlist[SPIKES]);
		glRotated (270, 1, 0, 0);
		glTranslated (0.0, 8.0, -6.5);
		glCallList (dlist[SPIKES]);
	glPopMatrix();

	/// **  DISZKEK ** //
	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, text[0] );
		glTranslated(-24.0, -0.5, -34.0);
		glCallList(dlist[DISKS]);
	glPopMatrix();

	//prop1
	glPushMatrix();
		glTranslated(-24.0, 7.5, -34.0 );
		glRotatef(85, 1, 0, 0);
		glRotated(szog_2, 0, 0, 1);
		gluSphere(qobj, 0.5, 100, 100);
		glBindTexture(GL_TEXTURE_2D, text[1]);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 0, 45);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 90, 45);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 180, 45);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 270, 45);
	glPopMatrix();
	//

	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, text[0] );
		glTranslated(25.0, -0.5, -34.0);
		glCallList(dlist[DISKS]);
	glPopMatrix();

	//prop2
	glPushMatrix();
		glTranslated(25.0, 7.5, -34.0 );
		glRotatef(85, 1, 0, 0);
		glRotated(szog_2, 0, 0, 1);
		gluSphere(qobj, 0.5, 100, 100);
		glBindTexture(GL_TEXTURE_2D, text[1]);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 0, 45);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 90, 45);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 180, 45);
		gluPartialDisk(qobj, 0.7, 3, 10, 3, 270, 45);
	glPopMatrix();
	//

	szog_2 += 3.7;
	// *************** //

	// nurbs
	
	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, text[0] );
		glRotated (szog_nurbs, 0, 1, 0);
		glTranslatef (0, 25, -20);
		glRotated (90, 0, 1, 0);
		glRotated (45, 1, 0, 0);
		glRotatef (80, 0, 1, 0);
		glScaled (20, 20, 20);
		glCallList (NURB);
	glPopMatrix();
	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, text[0] );
		glRotated (szog_nurbs, 0, 1, 0);
		glTranslatef ( 0, 25, 15 );
		glRotated (90, 0, 1, 0);
		glRotated (45, 1, 0, 0);
		glRotatef (80, 0, 1, 0);
		glScaled (20, 20, 20);
		glCallList (NURB);
	glPopMatrix();
	szog_nurbs += 1.0;
	// 

	/// **  ÉGBOLT  ** ///	
	glBindTexture( GL_TEXTURE_2D, text[2] );
	egbolt(text[2], szog, qobj);
	glPopMatrix();
	szog += 0.02;
	
//void gluCylinder (GLUquadricObj *qobj, GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);

	/////////////////////
	/// **  FENYÕ  ** ///
	/////////////////////
	glPushMatrix();	
		glTranslated(30, 0, -12);
		glBindTexture(GL_TEXTURE_2D, text[4] );
		glCallList(dlist[FIR_F]);
		glBindTexture(GL_TEXTURE_2D, text[3] );
		glCallList(dlist[FIRS]);
		glTranslated(-90, 0, 0);
		glBindTexture(GL_TEXTURE_2D, text[4] );
		glCallList(dlist[FIR_F]);
		glBindTexture(GL_TEXTURE_2D, text[3] );
		glCallList(dlist[FIRS]);
	glPopMatrix();
	/// *********** ///

	////////////////////
	/// **  TALAJ ** ///
	////////////////////
	glBindTexture(GL_TEXTURE_2D, text[6]);
	glPushMatrix();
		glTranslated(100., 3.1, -100.);
		glCallList(dlist[GROUND]);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, text[5]);
	glPushMatrix();
		glTranslated(1.0, -1.75, -30.0);
		glCallList(dlist[GROUND_CONCRETE]);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, text[5]);
		glTranslated(1.0, 0, -10.0);
		glTranslated(6.0, -3.0, -5.0);
		glCallList(dlist[CONCRETES]);
		glTranslated(-17.0, 0.0, 0.0);
		glCallList(dlist[CONCRETES]);
	glPopMatrix();
	/// ************ ///

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, text[5]);
		glTranslated(-2.2, 2.5, -48.0);
		glRotated(a, 0, 1, 0);
		glutSolidTeapot(2);
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc (GL_ONE, GL_ONE);
	//glDisable(GL_TEXTURE);
	glDepthMask (GL_FALSE);
        glPushMatrix();
            glColor4f (0, 1, 1, 0.35);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTranslatef (-2.1, 2.5, -49.5);
            glutSolidSphere (6, 30, 30);
        glPopMatrix();
		glPushMatrix();
			glRotated(szog_nurbs, 0, 1, 0);
			glTranslatef( 5, 25, -15 );
			glutSolidSphere (11, 30, 30);
		glPopMatrix();
		glPushMatrix();
			glRotated(szog_nurbs, 0, 1, 0);
			glTranslatef( 5, 25, 20 );
			glutSolidSphere (11, 30, 30);
		glPopMatrix();
    glDepthMask (GL_TRUE);
	//glEnable(GL_TEXTURE);
	glDisable(GL_BLEND);

    glClearColor(0.8, 0.8, 0.8, 1.0); 

	if( menu )
	{
		//glViewport (0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluOrtho2D(0.0, (float) width, 0.0, (float) height);
		glOrtho(0.0, (float) WIDTH, 0.0, (float) HEIGHT, -150.0, 150.0);
		//glFrustum(0.0, (float) width, 0.0, (float) height, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);

		glColor3d(1.0, 1.0, 1.0);
		glCallList(dlist[CHARS]);
	}
    glutSwapBuffers();
}

static void idle( void ) 
{
    glutPostRedisplay();
}

static void resize( int width, int height ) 
{
	WIDTH = width;
	HEIGHT = height;
    glViewport (0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 0.0,  0.0, 0.0, -1.0,  0.0, 1.0, 0.0);
}

static void key( unsigned char Key, int x, int y )
{
	float movespeed = 2;
    switch (Key)
    {
        case 27: exit (0); break;
        case ' ': menu = !menu; lights = !lights; break;

		/*case 'W': case 'w': forw += 5; break;
        case 'S': case 's': forw -= 5; break;
        case 'A': case 'a': rot -= 5; break;
        case 'D': case 'd': rot += 5; break;
		case 'E': case 'e': ver -= 2; break;
        case 'Q': case 'q': ver += 2; break;
		case 'R': case 'r': ver_look -= 1; break;
        case 'F': case 'f': ver_look += 1; break;
        /****************************/
		
		/***      Igazítás      ***
		case 'U': case 'u': movY += 0.5; printf("movY: %lf\n", movY); break;
		case 'J': case 'j': movY -= 0.5; printf("movY: %lf\n", movY); break;
		case 'H': case 'h': movX -= 0.5; printf("movX: %lf\n", movX); break;
		case 'K': case 'k': movX += 0.5; printf("movX: %lf\n", movX); break;
		case 'O': case 'o': movZ -= 0.5; printf("movZ: %lf\n", movZ); break;
		case 'L': case 'l': movZ += 0.5; printf("movZ: %lf\n", movZ); break;
		/**************************/

        /********************************/
        /**        SCISSOR TEST        **/
        /********************************/
		case 'X': case 'x': _scissor_ = !_scissor_; break;
        /********************************/

		case 'M': case 'm': lights = !lights; break;
		case 'B': case 'b': fog = !fog; break;
			
		/****************************/
        /**        LookAt          **/
        /****************************/
		case 'D': case 'd': X += cos(rotY * DEGREE) * movespeed, Z -= sin(rotY * DEGREE) * movespeed; break;
		case 'A': case 'a': X -= cos(rotY * DEGREE) * movespeed; Z += sin(rotY * DEGREE) * movespeed; break;
		case 'W': case 'w': X -= sin(rotY * DEGREE) * movespeed; Z -= cos(rotY * DEGREE) * movespeed; break;
		case 'S': case 's': X += sin(rotY * DEGREE) * movespeed; Z += cos(rotY * DEGREE) * movespeed; break;
		case 'Q': case 'q': rotY += 5; break;
		case 'E': case 'e': rotY -= 5; break;
		case 'R': case 'r': Y += 1; break;
		case 'F': case 'f': Y -= 1; break;
		/*****************************/
		default: break;
    }

    glLoadIdentity();
	glRotated (-rotY, 0, 1, 0);
	glTranslated (-X, -Y, -Z);
    //glRotated (rot, 0, 1, 0);
	
    gluLookAt (0.0, 0.0, 0.0,  0.0, 0.0, -1.0,  0.0, 1.0, 0.0);

    _scissor_ == 1 ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
	lights	  == 1 ? glEnable (GL_LIGHTING)    : glDisable (GL_LIGHTING);
	fog       == 1 ? glEnable(GL_FOG)		   : glDisable(GL_FOG);
	/** glScissor(GLint x, GLint y, GLsizei width, GLsizei height); **/
    glScissor( 100, 100, 800, 500); //////////////////////////
    glutPostRedisplay();
}

int main( int argc, char** argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	/*glutInitWindowSize (1000, 600);
	glutInitWindowPosition (100, 100);*/
	
	glutCreateWindow (argv[0]);
	
	//glutSetCursor(GLUT_CURSOR_);
	glutFullScreen();
	init();
	LoadTextures();
	glutKeyboardFunc (key);
	glutReshapeFunc (resize);
	glutDisplayFunc (display);
	glutIdleFunc (idle);
	glutMainLoop();

	exit(0);
}
