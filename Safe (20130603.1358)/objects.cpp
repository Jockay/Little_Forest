#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define firs_width 40
#define firs_height 80

void egbolt(int Text, double Szog, GLUquadricObj * ASd) {
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, Text );
		glTranslated(0.0, -60.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotated(Szog, 0, 0, 1);
		gluSphere(ASd, 120, 100, 100);
	glPopMatrix();
	Szog += 0.02;
}

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

static void DisplayLists(int fir, int conc, int ground, int spikes, int firs, int fir_f, int ground_concrete, int disks, int concretes, GLUquadricObj * Asd)
{
	ground = glGenLists(2);
	glNewList(ground, GL_COMPILE);
		short int oldal = 5;
        glPushMatrix();
			glColor3d(1.0, 1.0, 1.0);
			for(double j = 0; j <= 200; j += oldal)
				for(double i = -200; i <= 0; i += oldal)
				{
					glBegin(GL_QUADS);
						glNormal3d(0.0, 1.0, 0.0);
						glTexCoord2f(0.0, 0.0); glVertex3f(i, -5.0, j);
						glTexCoord2f(1.0, 0.0); glVertex3f(i, -5.0, j + oldal);
						glTexCoord2f(1.0, 1.0); glVertex3f(i + oldal, -5.0, j + oldal);
						glTexCoord2f(0.0, 1.0); glVertex3f(i + oldal, -5.0, j);
					glEnd();
				}
		glPopMatrix();
	glEndList();

	ground_concrete = glGenLists(7);
	glNewList(ground_concrete, GL_COMPILE);
		short int oldal2 = 5;
        glPushMatrix();
			glColor3d(1.0, 1.0, 1.0);
			for(double j = 0; j <= 90; j += oldal)
				for(double i = -10; i <= 0; i += oldal)
				{
					glBegin(GL_QUADS);
						glNormal3d(0.0, 1.0, 0.0);
						glTexCoord2f(0.0, 0.0); glVertex3f(i, 0, j);
						glTexCoord2f(1.0, 0.0); glVertex3f(i, 0, j + oldal);
						glTexCoord2f(1.0, 1.0); glVertex3f(i + oldal, 0, j + oldal);
						glTexCoord2f(0.0, 1.0); glVertex3f(i + oldal, 0, j);
					glEnd();
				}
		glPopMatrix();
	glEndList();

	spikes = glGenLists(4);
	glNewList(spikes, GL_COMPILE);
		gluQuadricTexture(Asd, 1);
		for (double l = -5; l <= 5; l += 2)
            for (double j = -5; j <= 5; j += 2)
            {
				glPushMatrix();
					glTranslatef( j, 0, l );
					glRotatef(80, 1, 0, 0);
					gluCylinder(Asd, 0, 1.5, 2.5, 25, 25);
				glPopMatrix();
            }
	glEndList();

	fir_f = glGenLists(5);
	glNewList(fir_f, GL_COMPILE);
		gluQuadricTexture(Asd, 1);
		for(double j = 0; j < firs_width; j += 15.0 )
			for(double i = 0; i < firs_height; i += 15.0)
			{
				glPushMatrix();	
					glTranslated(j, 2, i);
					glRotatef(90, 1, 0, 0);
					glScaled(2, 2, 2);
					//glRotated(szog, 0, 0, 1);
						gluCylinder(Asd, 0.85, 0.85, 2.2, 25, 25);
				glPopMatrix();
			}
	glEndList();

	firs = glGenLists(6);
	glNewList(firs, GL_COMPILE);
		gluQuadricTexture(Asd, 1);
		for(double j = 0; j < firs_width; j += 15.0 )
			for(double i = 0; i < firs_height; i += 15.0)
			{
				glPushMatrix();	
					glTranslated(j, 2, i);
					glRotatef(90, 1, 0, 0);
					glScaled(2, 2, 2);
					glTranslated(0.0, 0.0, -1.8);
						gluCylinder(Asd, 0, 3.5, 2.5, 25, 25);
					glTranslated(0.0, 0.0, -1.5);
						gluCylinder(Asd, 0, 2.8, 2.5, 25, 25);
					glTranslated(0.0, 0.0, -1.65);
						gluCylinder(Asd, 0, 2.0, 2.5, 25, 25);		
				glPopMatrix();
			}
	glEndList();

	disks = glGenLists(9);
	glNewList(disks, GL_COMPILE);
		double i = 0.5, poz = 0.5;
		for(int j = 1, i = 8, poz = 0.0; j < 10; j++, i -= 0.09, poz += 1.0)
			{
				glPushMatrix();
					//glRotated(366, 1, 0, 0);
					glTranslatef( 0, poz, 0 );
					glRotatef(90, 1, 0, 0);
					gluDisk(Asd, 0.5, i, 10, 3);
				glPopMatrix();
			}
	glEndList();

	makeRasterFont();
    //glClearColor(0.0, 0.0, 0.0, 0.0);

    chars = glGenLists (10);
    glNewList (chars, GL_COMPILE); /// Feliratok display list-ben
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

	conc = glGenLists(3);
	glNewList(conc, GL_COMPILE);
		gluQuadricTexture(Asd, 1);
		glPushMatrix();
			//glBindTexture( GL_TEXTURE_2D, text[5] );
			glScaled(0.7, 0.7, 0.7);
			glRotatef(90, 1, 0, 0);
			//glutSolidTorus(20.0, 40.0, 40, 40);
			gluCylinder(Asd, 0.4, 0.7, 1.0, 25, 25);
			glTranslated(0.0, 0.0, -0.377);
			gluSphere(Asd, 0.55, 30, 30);
		glPopMatrix();
	glEndList();

	concretes = glGenLists(8);
	glNewList(concretes, GL_COMPILE);
		gluQuadricTexture(Asd, 1);
			for(double i = 0; i < firs_height; i += 15.0)
			{
				glPushMatrix();	
					glTranslated(0, 2, i);
					glCallList(conc);
				glPopMatrix();
			}
	glEndList();
}
