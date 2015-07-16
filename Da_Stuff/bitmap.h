#ifndef _CBMP_H_
#define _CBMP_H_

#include<stdio.h>
#include<stdlib.h>
#include<gl\glut.h>

typedef struct tagBMPHeader
{
	unsigned char bfType[2];
	unsigned char bfSize[4];
	unsigned char bfReserved1[2];
	unsigned char bfReserved2[2];
	unsigned char bfOffBits[4];
}BMPHeader;

typedef struct tagBMPInfoHeader
{
	unsigned char biSize[4];
	unsigned char biWidth[4];
	unsigned char biHeight[4];
	unsigned char biPlanes[2];
	unsigned char biBitCount[2];
	unsigned char biCompression[4];
	unsigned char biSizeImage[4];
	unsigned char biXPelsPerMeter[4];
	unsigned char biYPelsPerMeter[4];
	unsigned char biClrUsed[4];
	unsigned char biClrImportant[4];
}BMPInfoHeader;

class Bitmap
{
public:
	BMPHeader header;
	BMPInfoHeader infoheader;
	int width;
	int height;
	unsigned char* image_data;
	GLuint texture;

	bool load(char* szFileName);
	static GLuint loadTexture( char* szFileName, bool wrap );
	static GLuint loadTexture( Bitmap & bitmap, bool wrap);
};

#endif
