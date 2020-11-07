#include "CommonFunctionsC++.h"
#include <stdio.h>
#include <stdbool.h>
#include <GL/glut.h>

float get_cellPositonX(int column, int maxColumns, int WIDTH){
    float x = ((column+0.5)*WIDTH/maxColumns)-WIDTH/2;
    return x;    
}

float get_cellPositonY(int row, int maxRows, int HEIGHT){
    float y = 0;                    
    return y;
}

float get_cellPositonZ(int row, int maxRows, int HEIGHT){
    float z = ((row+0.5)*HEIGHT/maxRows)-HEIGHT/2;                    
    return z;
}

//------------------------------------------------------------------

float get_cellSizeX(int column, int maxColumns, int WIDTH){
    float sizeX = ((column+1)*WIDTH/maxColumns-column*WIDTH/maxColumns)/2.0;
    return sizeX;
}

float get_cellSizeY(int row, int maxRows, int HEIGHT){
    float sizeY = ((row+1)*HEIGHT/maxRows-row*HEIGHT/maxRows)/2.0;
    return sizeY;
}

float get_cellSizeZ(int row, int maxRows, int HEIGHT){
    float sizeZ = ((row+1)*HEIGHT/maxRows-row*HEIGHT/maxRows)/2.0;
    return sizeZ;
}

void draw_wall(float x,float y,float z,float sizeX,float sizeY,float sizeZ, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY){
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_FILL);
    //glPolygonMode(GL_BACK,GL_LINE);
    
    glEnable(GL_TEXTURE_2D);

    //Define wall texture
    glBindTexture(GL_TEXTURE_2D,0);

    //FRONT
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z+sizeZ);
    glEnd();
    
    //BACK
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z-sizeZ);
    glEnd();

    //RIGHT
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z+sizeZ);
    glEnd();


    //LEFT
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z+sizeZ);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D,1);
    //TOP
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z+sizeZ);
    glEnd();
}

void draw_square(float x,float y,float z,float sizeX,float sizeY,float sizeZ, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY){
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_FILL);
    //glPolygonMode(GL_BACK,GL_LINE);

    //FRONT
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z+sizeZ);
    glEnd();
    
    //BACK
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z-sizeZ);
    glEnd();

    //RIGHT
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z+sizeZ);
    glEnd();


    //LEFT
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z+sizeZ);
    glEnd();

    //Made bot and top more brightly
    if(red < 1){
        red = red+0.1;
    }
    if(green < 1){
        green = green+0.1;
    }
    if(blue < 1){
        blue = blue+0.1;
    }

    //TOP
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y+sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y+sizeY,z+sizeZ);
    glEnd();
}


void draw_floor(float x,float y,float z,float sizeX,float sizeY,float sizeZ, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY){
    glEnable(GL_TEXTURE_2D);

    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z-sizeZ);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-sizeX,y-sizeY,z+sizeZ);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+sizeX,y-sizeY,z+sizeZ);
    glEnd();
}


void draw_sphere(float x,float y,float z,float radius, float red, float green, float blue){
    
    int slices = 25;
    int stacks = 25;

    // Create a new quadric and render it normally
    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);

    glColor3f(red,green,blue);
    
    glPushMatrix();
    glTranslated(x, y, z);
    gluSphere(sphere, radius, slices, stacks);
    //gluDeleteQuadric(sphere);
    glPopMatrix();

    // Free the quadric object
    gluDeleteQuadric(sphere);
}

