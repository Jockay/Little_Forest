#include "Bitmap.h"

bool Bitmap::load(char* szFileName)
{
	FILE* fp;
	fp = fopen(szFileName, "rb");
	if(fp==NULL) return false;
	fread(&header, sizeof(header), 1, fp);
	if(header.bfType[0] != 'B' && header.bfType[1] != 'M')  return false;
	fread(&infoheader, sizeof(infoheader), 1, fp);
	width = infoheader.biWidth[0] + infoheader.biWidth[1] * 256 + infoheader.biWidth[2] * 512 + infoheader.biWidth[3] * 1024;
	height = infoheader.biHeight[0] + infoheader.biHeight[1] * 256 + infoheader.biHeight[2] * 512 + infoheader.biWidth[3] * 1024;
	image_data = (unsigned char *)malloc(width * height * sizeof(unsigned char) * 4);
	fread(image_data, width * height * 4, 1, fp);
    int i;
    char tmp_char;
    for(i=0;i<(width*height);i++)
    {
        tmp_char = image_data[(i*3)];
        image_data[i*3] = image_data[(i*3)+2];
        image_data[(i*3)+2] = tmp_char;
    }

	fclose(fp);

	return true;
}

GLuint Bitmap::loadTexture(Bitmap&bitmap, bool wrap = true)
{
  GLuint texture;
  int width = bitmap.width, height = bitmap.height;
  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, bitmap.image_data );
  return texture;
}

GLuint Bitmap::loadTexture(char* file, bool wrap = true)
{
	Bitmap bitmap;
	if(!bitmap.load(file)) return 0;
	GLuint texture = loadTexture(bitmap, wrap);
	return texture;
}

