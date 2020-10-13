#include <GL/glut.h>
#include "Wrapper.h"
#include "CommonFunctions.h"
#include <stdio.h>

#define MINIMUM_NUMBER 10

#define WIDTH 800
#define HEIGHT 800

//-----------------------------------------------

void display();;
void keyboard(unsigned char c,int x,int y);

//-----------------------------------------------

int keyflag=0;

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(1500, 500);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Chess board");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

  glutMainLoop();
  return 0;
}

//------------------------------------------------------------
//------------------------------------------------------------

void display()
{
  int rows=31, columns = 31;
  printf("---Rows---- \n");
  //int rows = getMargin(MINIMUM_NUMBER);
  printf("---Columns--- \n");
  //int columns = getMargin(MINIMUM_NUMBER);

  struct MapClass* map = newMapClass(rows,columns);
  MapClass_createMap(map);
  MapClass_printMap(map);

  glClearColor(0.0,0.0,0.2,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(int column=0;column<columns;column++){
    int i = column;
    int j = rows;
    for(int row=0;row<rows;row++){
      j = j-1;
      //if( (keyflag==0 && (i+j)%2==0) || (keyflag==1 && (i+j)%2==1) ) 
      if( MapClass_getValue(map,row,column) == 1 ) {
        glColor3f(0.8,0.8,0.8);
        glBegin(GL_QUADS);
        glVertex2i(i*WIDTH/columns,j*HEIGHT/rows); 
        glVertex2i((i+1)*WIDTH/columns,j*HEIGHT/rows); 
        glVertex2i((i+1)*WIDTH/columns,(j+1)*HEIGHT/rows); 
        glVertex2i(i*WIDTH/columns,(j+1)*HEIGHT/rows); 

        glEnd();
      }
    }
  }
  glutSwapBuffers();
}

//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  if(keyflag==0)
    keyflag=1;
  else
    keyflag=0;

  glutPostRedisplay();

};


