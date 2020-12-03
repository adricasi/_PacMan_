#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include "jpeglib.h"
#include <math.h>
#include "../Constants.h"

//--------------Main Manager----------------------
_Bool isPar(int number);

int getMargin(int minimumNumber);

void drawWin();

void drawLose();

void ambientLight();

//--------------Texture Manager----------------------

void ReadJPEG(char *filename,unsigned char **image,int *width, int *height);

void LoadTexture(char *filename,int dim);