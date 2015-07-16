#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bitmap.h"
#include "objects.cpp"
#define size 17
#define PI 3.1415926535898
#define DEGREE PI/180.0

/*********************************************/
/** Használható billentyûk a key eljárásban **/
/*********************************************/

static int WIDTH, HEIGHT;
static double movX = -2.0, movY = -1.5, movZ = 45;
static short int fog = 1, _scissor_ = 0, lights = 0, Wspace = 1;
static int FIR, CONC, GROUND, SPIKES, FIRS, FIR_F, GROUND_CONCRETE, DISKS, CONCRETES, NURB;
static int * list = new int[10];
/*
0 - fir
1 - conc
2 - ground
3 - conc
4 - spikes
5 - fir_f
6 - firs
7 - ground_concrete
8 - concretes
9 - disks
10 - chars
*/
static float szog = 0.0, szog_2 = 0.0, szog_nurbs = 0.0, forw = 0.0, rot = 0.0, ver = 0.0, ver_look = 0.0;
static double X = 0.0, Y = 0.0, Z = 0.0, rotx = 0.0;
GLuint text[9];
GLUquadricObj* asd = gluNewQuadric();

GLfloat ctlpoints[4][4][3];
//int showPoints = 0;
GLUnurbsObj *theNurb;

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
				ctlpoints[u][v][1] = cos(double(u*v)) * sin(double(v*v))+0.1;
            else ctlpoints[u][v][1] =-1;
            x+=0.2;
        }
        z+=0.2;
    }

	NURB = glGenLists(1);
	glNewList(NURB, GL_COMPILE);
        glPushMatrix();
            /**/
            gluBeginSurface(theNurb);
                gluNurbsSurface( theNurb, 14, knots, 14, knots, 10 * 3, 3, &ctlpoints[0][0][0], 6, 6, GL_MAP2_VERTEX_3 );
				gluNurbsSurface( theNurb, 14, knots, 14, knots, 10 * 3, 3, &ctlpoints[0][0][0], 6, 6, GL_MAP2_NORMAL );
                gluNurbsSurface( theNurb, 4,  tknots, 4, tknots, 2 * 2, 2, &tcoords[0][0][0], 3, 3, GL_MAP2_TEXTURE_COORD_2 );
            gluEndSurface(theNurb);
        glPopMatrix();
	glEndList();
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
    glFogf (GL_FOG_DENSITY, 0.3);
	glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_START, 100.0);
    glFogf (GL_FOG_END, 140.0);
	/*********/

	theNurbList();
	DisplayLists(FIR, CONC, GROUND, SPIKES, FIRS, FIR_F, GROUND_CONCRETE, DISKS, CONCRETES, asd);
	
	//glShadeModel (GL_SMOOTH);
	gluQuadricDrawStyle(asd, GLU_FILL);
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
	gluQuadricTexture(asd, 1);

	glBindTexture (GL_TEXTURE_2D, text[7]);
	glPushMatrix();	
		glRotated (180, 0, 1, 0);
		glTranslated (-2.3, -1.5, 45);
		GLfloat P0[3] = { 0.5f*size, 0.5f*size, 0.5f*size };
		GLfloat P1[3] = { 0.0f,      0.5f*size, 0.5f*size };
		GLfloat P2[3] = { 0.0f,      0.0f,      0.5f*size };
		GLfloat P3[3] = { 0.5f*size, 0.0f,      0.5f*size };
		GLfloat P4[3] = { 0.5f*size, 0.0f,      0.0f };
		GLfloat P5[3] = { 0.5f*size, 0.5f*size, 0.0f };
		GLfloat P6[3] = { 0.0f,      0.5f*size, 0.0f };
		GLfloat P7[3] = { 0.0f,      0.0f,      0.0f };
		glBegin(GL_QUADS);
			/// 0-1-2-3
			glColor3f (0.7, 0.7, 0.7); //GREY
			glNormal3d (0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0); glVertex3fv( P0 );
			glTexCoord2f(1.0, 0.0); glVertex3fv( P1 );
			//glColor3f( 0.03, 0.03, 0.03 ); //
			glTexCoord2f(1.0, 1.0); glVertex3fv( P2 );
			//glColor3f( 0.2, 0.2, 0.22 ); //
			glTexCoord2f(0.0, 1.0); glVertex3fv( P3 );
			/// 0-3-4-5
			//glColor3f( 1, 0, 0.12 ); //RED
			glNormal3d(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0, 0.0); glVertex3fv( P0 );
			glTexCoord2f(1.0, 0.0); glVertex3fv( P3 );
			//glColor3f( 0.03, 0.03, 0.03 ); //
			glTexCoord2f(1.0, 1.0); glVertex3fv( P4 );
			//glColor3f( 1, 0, 0.12 ); //
			glTexCoord2f(0.0, 1.0); glVertex3fv( P5 );
			/// 0-5-6-1
			//glColor3f( 0, 1, 0.12 ); //GREEN
			glNormal3d(0.0, -1.0, 0.0);
			glTexCoord2f(0.0, 0.0); glVertex3fv( P0 );
			glTexCoord2f(1.0, 0.0); glVertex3fv( P5 );
			//glColor3f( 0.03, 0.03, 0.03 ); //
			glTexCoord2f(1.0, 1.0); glVertex3fv( P6 );
			//glColor3f( 0, 1, 0.12 ); //
			glTexCoord2f(0.0, 1.0); glVertex3fv( P1 );
			/// 6-7-2-1
			//glColor3f( 0.4, 0.4, 0.1 ); //BLUE *****
			glNormal3d(1.0, 0.0, 0.0);
			glTexCoord2f(0.0, 0.0); glVertex3fv( P6 );
			glTexCoord2f(1.0, 0.0); glVertex3fv( P7 );
			//glColor3f( 0.03, 0.03, 0.03 ); //
			glTexCoord2f(1.0, 1.0); glVertex3fv( P2 );
			//glColor3f( 0.4, 0.4, 0.1 ); //
			glTexCoord2f(0.0, 1.0); glVertex3fv( P1 );
			/// 4-3-2-7
			//glColor3f( 0.73, 0.58, 0.12 ); //YELLOW
			glNormal3d(0.0, 1.0, 0.0);
			glTexCoord2f(0.0, 0.0); glVertex3fv( P4 );
			glTexCoord2f(1.0, 0.0); glVertex3fv( P3 );
			//glColor3f( 0.03, 0.03, 0.03 ); //
			glTexCoord2f(1.0, 1.0); glVertex3fv( P2 );
			//glColor3f( 0.73, 0.58, 0.12 ); //
			glTexCoord2f(0.0, 1.0); glVertex3fv( P7 );
		glEnd();
	glPopMatrix();

    glPushMatrix();
		glTranslated(-2, 10., -50);
		glBindTexture( GL_TEXTURE_2D, text[1] );
		glCallList(SPIKES);
		glRotated(90, 0, 0, 1);
		glTranslated(-7, 7.0, 0);
		glCallList(SPIKES);
		glTranslated(0, -14.5, 0);
		glRotated(180, 0, 0, 1);
		glCallList(SPIKES);
		glRotated(270, 1, 0, 0);
		glTranslated(0.0, 8.0, -6.5);
		glCallList(SPIKES);
	glPopMatrix();

	/// **  DISZKEK ** //
	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, text[0] );
		glTranslated(-24.0, -0.5, -34.0);
		glCallList(DISKS);
	glPopMatrix();

	glPushMatrix();
		glTranslated(-24.0, 7.5, -34.0 );
		glRotatef(85, 1, 0, 0);
		glRotated(szog_2, 0, 0, 1);
		gluSphere(asd, 0.5, 100, 100);
		glBindTexture(GL_TEXTURE_2D, text[1] );
		gluPartialDisk(asd, 0.7, 3, 10, 3, 0, 45);
		gluPartialDisk(asd, 0.7, 3, 10, 3, 90, 45);
		gluPartialDisk(asd, 0.7, 3, 10, 3, 180, 45);
		gluPartialDisk(asd, 0.7, 3, 10, 3, 270, 45);
	glPopMatrix();

	glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, text[0] );
		glTranslated(25.0, -0.5, -34.0);
		glCallList(DISKS);
	glPopMatrix();

	glPushMatrix();
		glTranslated(25.0, 7.5, -34.0 );
		glRotatef(85, 1, 0, 0);
		glRotated(szog_2, 0, 0, 1);
		gluSphere(asd, 0.5, 100, 100);
		glBindTexture(GL_TEXTURE_2D, text[1] );
		gluPartialDisk(asd, 0.7, 3, 10, 3, 0, 45);
		gluPartialDisk(asd, 0.7, 3, 10, 3, 90, 45);
		gluPartialDisk(asd, 0.7, 3, 10, 3, 180, 45);
		gluPartialDisk(asd, 0.7, 3, 10, 3, 270, 45);
	glPopMatrix();

	szog_2 += 3.7;
	// *************** //

	
	// nurbs
	glBindTexture( GL_TEXTURE_2D, text[0] );
	glPushMatrix();
		glRotated (szog_nurbs, 0, 1, 0);
		glTranslatef (0, 25, -20);
		glRotated (90, 0, 1, 0);
		glRotated (45, 1, 0, 0);
		glRotatef (80, 0, 1, 0);
		glScaled (20, 20, 20);
		glCallList (NURB);
	glPopMatrix();
	glPushMatrix();
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
	egbolt(text[2], szog, asd);
	
	
//void gluCylinder (GLUquadricObj *qobj, GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);

	/////////////////////
	/// **  FENYÕ  ** ///
	/////////////////////
	glPushMatrix();	
		glTranslated(30, 0, -12);
		glBindTexture(GL_TEXTURE_2D, text[4] );
		glCallList(FIR_F);
		glBindTexture(GL_TEXTURE_2D, text[3] );
		glCallList(FIRS);
		glTranslated(-90, 0, 0);
		glBindTexture(GL_TEXTURE_2D, text[4] );
		glCallList(FIR_F);
		glBindTexture(GL_TEXTURE_2D, text[3] );
		glCallList(FIRS);
	glPopMatrix();
	/// *********** ///

	////////////////////
	/// **  TALAJ ** ///
	////////////////////
	glBindTexture(GL_TEXTURE_2D, text[6]);
	glPushMatrix();
		glTranslated(100., 3.1, -100.);
		glCallList(GROUND);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, text[5]);
	glPushMatrix();
		glTranslated(1.0, -1.75, -30.0);
		glCallList(GROUND_CONCRETE);
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, text[5]);
		glTranslated(1.0, 0, -10.0);
		glTranslated(6.0, -3.0, -5.0);
		glCallList(CONCRETES);
		glTranslated(-17.0, 0.0, 0.0);
		glCallList(CONCRETES);
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

	if( Wspace )
	{
		//glViewport (0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluOrtho2D(0.0, (float) width, 0.0, (float) height);
		glOrtho(0.0, (float) WIDTH, 0.0, (float) HEIGHT, -150.0, 150.0);
		//glFrustum(0.0, (float) width, 0.0, (float) height, -100.0, 100.0);
		glMatrixMode(GL_MODELVIEW);

		glColor3d(1.0, 1.0, 1.0);
		glCallList(chars);
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
        case ' ': Wspace = !Wspace; lights = !lights; break;

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
		case 'D': case 'd': X += cos(rotx * DEGREE) * movespeed; Z -= sin(rotx * DEGREE) * movespeed; break;
		case 'A': case 'a': X -= cos(rotx * DEGREE) * movespeed; Z += sin(rotx * DEGREE) * movespeed; break;
		case 'W': case 'w': X -= sin(rotx * DEGREE) * movespeed; Z -= cos(rotx * DEGREE) * movespeed; break;
		case 'S': case 's': X += sin(rotx * DEGREE) * movespeed; Z += cos(rotx * DEGREE) * movespeed; break;
		case 'Q': case 'q': rotx += 5; break;
        case 'E': case 'e': rotx -= 5; break;
		case 'R': case 'r': Y += 1; break;
        case 'F': case 'f': Y -= 1; break;
		/*****************************/
		default: break;
    }

    glLoadIdentity();
	glRotated (-rotx, 0, 1, 0);
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
	glutFullScreen();
	//glutSetCursor(GLUT_CURSOR_);
	init();
	glutKeyboardFunc (key);
	glutReshapeFunc (resize);
	glutDisplayFunc (display);
	glutIdleFunc (idle);
	text[0] = Bitmap::loadTexture("red_dirty.bmp", true);
	text[1] = Bitmap::loadTexture("blue_dirty.bmp", true);
	text[2] = Bitmap::loadTexture("sky_stars.bmp", true);
	text[3] = Bitmap::loadTexture("green_dirty.bmp", true);
	text[4] = Bitmap::loadTexture("wood01.bmp", true);
	text[5] = Bitmap::loadTexture("ut.bmp", true);
	text[7] = Bitmap::loadTexture("wood3.bmp", true);
	text[6] = Bitmap::loadTexture("grass.bmp", true);
	text[8] = Bitmap::loadTexture("beton.bmp", true);
	glutMainLoop();
	exit(0);
}
