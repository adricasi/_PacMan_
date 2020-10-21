#include <GL/glut.h>
#include "Wrapper/Wrapper.h"
#include "CommonFunctions/CommonFunctionsC.h"
#include <stdio.h>

#define MINIMUM_NUMBER 10

#define WIDTH 600
#define HEIGHT 600
#define MOVEMENT_DURATION 1000

//-----------------------------------------------

void display();;
void keyboard(unsigned char c,int x,int y);
void idle();
void generateMap();
void generatePacMan();

//-----------------------------------------------

struct PacMan* pacMan;
struct MapClass* map;
int rows;
int columns;
long last_t=0;

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[])
{

  generateMap();
  generatePacMan();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(500, 100);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("PacMan board");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,WIDTH-1,0,HEIGHT-1);

  glutMainLoop();
  return 0;
}

//------------------------------------------------------------
//------------------------------------------------------------

void display()
{
  
  glClearColor(0.0,0.0,0.2,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  MapClass_drawMap(map,WIDTH,HEIGHT);  
  PacMan_draw(pacMan);

  glutSwapBuffers();
}

//-----------------------------------------------
//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  //free map memory
  //MapClass_freeMap(map);
  if (c=='w')
  {
    PacMan_initMovement(pacMan, PacMan_getRow(pacMan)-1, PacMan_getColumn(pacMan), MOVEMENT_DURATION);
  }
  if (c=='s')
  {
    PacMan_initMovement(pacMan, PacMan_getRow(pacMan)+1, PacMan_getColumn(pacMan), MOVEMENT_DURATION);

  }
  if (c=='a')
  {
    PacMan_initMovement(pacMan, PacMan_getRow(pacMan), PacMan_getColumn(pacMan)-1, MOVEMENT_DURATION);

  }
  if (c=='d')
  {
    PacMan_initMovement(pacMan, PacMan_getRow(pacMan), PacMan_getColumn(pacMan)+1, MOVEMENT_DURATION);

  }

  glutPostRedisplay();
};


//-----------------------------------------------
//-----------------------------------------------
void idle()
{
  long t;

  t=glutGet(GLUT_ELAPSED_TIME); 

  if(last_t==0)
    last_t=t;
  else
    {
      PacMan_integrate(pacMan,t-last_t);
      last_t=t;
    }
  glutPostRedisplay();
}


//---------------------------
void generateMap(){
  rows =21;
  columns =21;/*
  printf("---Rows---- \n");
  rows = getMargin(MINIMUM_NUMBER);
  printf("---Columns--- \n");
  columns = getMargin(MINIMUM_NUMBER);*/

  map = newMapClass(rows,columns);
  MapClass_createMap(map);
  MapClass_printMap(map);
}

//--------------------------------------
void generatePacMan(){
  pacMan = newPacMan(rows,columns,HEIGHT,WIDTH);
  printf("PACMAN GENERATION \n");
  int init_row = 1;
  int init_column = 1;
  float positionX = get_cellPositonX(init_column, columns, WIDTH);
  float positionY = get_cellPositonY(init_row, rows, HEIGHT);
  float sizeX = get_cellSizeX(init_column, columns, WIDTH)/1.5;
  float sizeY = get_cellSizeY(init_row, rows, HEIGHT)/1.5;

  printf("x:%f, y:%f, sx: %f sy:%f\n", positionX,positionY,sizeX,sizeY);

  PacMan_setPosition(pacMan, init_row, init_column, positionX, positionY);
  PacMan_setSize(pacMan, sizeX, sizeY);
  PacMan_draw(pacMan);
}


