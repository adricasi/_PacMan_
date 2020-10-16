#include <GL/glut.h>
#include "Wrapper/Wrapper.h"
#include "CommonFunctions/CommonFunctions.h"
#include <stdio.h>

#define MINIMUM_NUMBER 10

#define WIDTH 600
#define HEIGHT 600

//-----------------------------------------------

void display();;
void keyboard(unsigned char c,int x,int y);
void generateMap();

//-----------------------------------------------

struct MapClass* map;
int rows;
int columns;

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(500, 100);
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
  generateMap();
  
  glClearColor(0.0,0.0,0.2,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  MapClass_drawMap(map,WIDTH,HEIGHT);  
  glutSwapBuffers();
}

//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  //free map memory
  MapClass_freeMap(map);
  glutPostRedisplay();
};


//---------------------------
void generateMap(){
  printf("---Rows---- \n");
  rows = getMargin(MINIMUM_NUMBER);
  printf("---Columns--- \n");
  columns = getMargin(MINIMUM_NUMBER);

  map = newMapClass(rows,columns);
  MapClass_createMap(map);
  MapClass_printMap(map);
}


