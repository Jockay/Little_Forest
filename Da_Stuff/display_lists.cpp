#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 17
#define firs_width	40
#define firs_height 80

#define BOX	1
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

static void egbolt(int Text, double Szog, GLUquadricObj * Qobj) {
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, Text );
		glTranslated(0.0, -60.0, 0.0);
		glRotatef(270, 0, 1, 0);
		glRotated(Szog, 0, 0, 1);
		gluSphere(Qobj, 120, 100, 100);
	glPopMatrix();
	//Szog += 0.02;
}

static int *DisplayLists(int *list, GLuint *Text, GLUquadricObj *Qobj)
{
	/* list:
		 1 - box
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

	// box
	list[BOX] = glGenLists(1);
	glNewList(list[BOX], GL_COMPILE);
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
	glEndList();

	// ground
	list[GROUND] = glGenLists(2);
	glNewList(list[GROUND], GL_COMPILE);
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

	// conc
	list[CONC] = glGenLists(3);
	glNewList(list[CONC], GL_COMPILE);
		gluQuadricTexture(Qobj, 1);
		glPushMatrix();
			//glBindTexture( GL_TEXTURE_2D, text[5] );
			glScaled(0.7, 0.7, 0.7);
			glRotatef(90, 1, 0, 0);
			//glutSolidTorus(20.0, 40.0, 40, 40);
			gluCylinder(Qobj, 0.4, 0.7, 1.0, 25, 25);
			glTranslated(0.0, 0.0, -0.377);
			gluSphere(Qobj, 0.55, 30, 30);
		glPopMatrix();
	glEndList();

	// spikes
	list[SPIKES] = glGenLists(4);
	glNewList(list[SPIKES], GL_COMPILE);
		gluQuadricTexture(Qobj, 1);
		for (double l = -5; l <= 5; l += 2)
            for (double j = -5; j <= 5; j += 2)
            {
				glPushMatrix();
					glTranslatef( j, 0, l );
					glRotatef(80, 1, 0, 0);
					gluCylinder(Qobj, 0, 1.5, 2.5, 25, 25);
				glPopMatrix();
            }
	glEndList();

	// fir_f
	list[FIR_F] = glGenLists(5);
	glNewList(list[FIR_F], GL_COMPILE);
		gluQuadricTexture(Qobj, 1);
		for(double j = 0; j < firs_width; j += 15.0 )
			for(double i = 0; i < firs_height; i += 15.0)
			{
				glPushMatrix();	
					glTranslated(j, 2, i);
					glRotatef(90, 1, 0, 0);
					glScaled(2, 2, 2);
					//glRotated(szog, 0, 0, 1);
						gluCylinder(Qobj, 0.85, 0.85, 2.2, 25, 25);
				glPopMatrix();
			}
	glEndList();

	// firs
	list[FIRS] = glGenLists(6);
	glNewList(list[FIRS], GL_COMPILE);
		gluQuadricTexture(Qobj, 1);
		for(double j = 0; j < firs_width; j += 15.0 )
			for(double i = 0; i < firs_height; i += 15.0)
			{
				glPushMatrix();	
					glTranslated(j, 2, i);
					glRotatef(90, 1, 0, 0);
					glScaled(2, 2, 2);
					glTranslated(0.0, 0.0, -1.8);
						gluCylinder(Qobj, 0, 3.5, 2.5, 25, 25);
					glTranslated(0.0, 0.0, -1.5);
						gluCylinder(Qobj, 0, 2.8, 2.5, 25, 25);
					glTranslated(0.0, 0.0, -1.65);
						gluCylinder(Qobj, 0, 2.0, 2.5, 25, 25);		
				glPopMatrix();
			}
	glEndList();

	// ground concrete
	list[GROUND_CONCRETE] = glGenLists(7);
	glNewList(list[GROUND_CONCRETE], GL_COMPILE);
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

	// concretes
	list[CONCRETES] = glGenLists(8);
	glNewList(list[CONCRETES], GL_COMPILE);
		gluQuadricTexture(Qobj, 1);
			for(double i = 0; i < firs_height; i += 15.0)
			{
				glPushMatrix();	
					glTranslated(0, 2, i);
					glCallList(list[CONC]);
				glPopMatrix();
			}
	glEndList();

	// disks
	list[DISKS] = glGenLists(9);
	glNewList(list[DISKS], GL_COMPILE);
		double i = 0.5, poz = 0.5;
		for(int j = 1, i = 8, poz = 0.0; j < 10; j++, i -= 0.09, poz += 1.0)
			{
				glPushMatrix();
					//glRotated(366, 1, 0, 0);
					glTranslatef( 0, poz, 0 );
					glRotatef(90, 1, 0, 0);
					gluDisk(Qobj, 0.5, i, 10, 3);
				glPopMatrix();
			}
	glEndList();

	/*list[SKY] = glGenLists(9);
	glNewList(list[SKY], GL_COMPILE);
		glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, Text[2]);
			glTranslated(0.0, -60.0, 0.0);
			glRotatef(270, 0, 1, 0);
			gluSphere(Qobj, 120, 100, 100);
		glPopMatrix();
	glEndList();*/

	list[ROTOR] = glGenLists(12);
	glNewList(list[ROTOR], GL_COMPILE);
		glPushMatrix();
			
		glPopMatrix();
	glEndList();

	return (int *)list;
}
