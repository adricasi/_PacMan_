#include "CommonFunctions.h"

float get_cellPositonX(int column, int maxColumns, float cellSize){
    float position = (column*cellSize*2) - maxColumns*cellSize + cellSize;
    return position;    
}

float get_cellPositonY(int row, int maxRows){
    float y = 0;                    
    return y;
}

float get_cellPositonZ(int row, int maxRows, float cellSize){
    float position = (row*cellSize*2) - maxRows*cellSize + cellSize;
    return position;
}

//------------------------------------------------------------------

float get_cellSize(int maxRows,int maxColumns){
    float size = (HEIGHT/maxRows + WIDTH/maxColumns)/4.0;
    return size;
}

float get_radiusSphere(int row, int column, int maxRows, int maxColumns){
    float sizeWidth = ((column+1)*WIDTH/maxColumns-column*WIDTH/maxColumns)/2.0;
    float sizeHeight = ((row+1)*HEIGHT/maxRows-row*HEIGHT/maxRows)/2.0;

    return fmin(sizeWidth,sizeHeight);
}

//------------------------------------------------------------------

void draw_wall(float x,float y,float z,float size, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY){
    
    GLfloat material[4] = {red,green,blue,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_FILL);
    //glPolygonMode(GL_BACK,GL_LINE);
    
    //Define wall texture
    glBindTexture(GL_TEXTURE_2D,WALLTEXTURE);

    //FRONT
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+size,y+size,z+size);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-size,y+size,z+size);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-size,y-size,z+size);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+size,y-size,z+size);
    glEnd();
    
    //BACK
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+size,y-size,z-size);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-size,y-size,z-size);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-size,y+size,z-size);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+size,y+size,z-size);
    glEnd();

    //RIGHT
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x+size,y-size,z+size);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+size,y-size,z-size);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+size,y+size,z-size);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x+size,y+size,z+size);
    glEnd();


    //LEFT
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-size,y+size,z+size);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x-size,y+size,z-size);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x-size,y-size,z-size);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-size,y-size,z+size);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D,ROOFTEXTURE);
    //TOP
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+size,y+size,z-size);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-size,y+size,z-size);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-size,y+size,z+size);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+size,y+size,z+size);
    glEnd();
}

void draw_floor(float x,float y,float z,float size, float red, float green, float blue, float maxTexturePositionX, float minTexturePositionX, float maxTexturePositionY, float minTexturePositionY){
    GLfloat material[4] = {red,green,blue,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

    glBindTexture(GL_TEXTURE_2D,FLOORTEXTURE);
    //BOT
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(maxTexturePositionX,minTexturePositionY);glVertex3i(x+size,y-size,z-size);
    glTexCoord2f(minTexturePositionX,minTexturePositionY);glVertex3i(x-size,y-size,z-size);
    glTexCoord2f(minTexturePositionX,maxTexturePositionY);glVertex3i(x-size,y-size,z+size);
    glTexCoord2f(maxTexturePositionX,maxTexturePositionY);glVertex3i(x+size,y-size,z+size);
    glEnd();
}

void draw_sphere(float x,float y,float z,float radius, float red, float green, float blue){
    GLfloat material[4] = {red,green,blue,1.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material);

    int slices = 25;
    int stacks = 25;

    // Create a new quadric and render it normally
    GLUquadricObj *sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    
    glPushMatrix();
    glTranslated(x, y, z);
    gluSphere(sphere, radius, slices, stacks);
    //gluDeleteQuadric(sphere);
    glPopMatrix();

    // Free the quadric object
    gluDeleteQuadric(sphere);
}

