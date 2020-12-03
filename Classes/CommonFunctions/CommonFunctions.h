#include "../../Constants.h"

#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>


float get_cellPositonX(int column, int maxColumns, float cellSize);

float get_cellPositonY(int row, int maxRow);

float get_cellPositonZ(int row, int maxRows, float cellSize);

float get_cellSize(int maxRows,int maxColumns);

float get_radiusSphere(int row, int column, int maxRows, int maxColumns);

void draw_wall(float x,float y,float z,float size, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY);

void draw_floor(float x,float y,float z,float size, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY);

void draw_sphere(float x,float y,float z, float radius, float red, float green, float blue);