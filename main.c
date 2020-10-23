#include <GL/glut.h>
#include "Wrapper/Wrapper.h"
#include "CommonFunctions/CommonFunctionsC.h"
#include <stdio.h>

#define MINIMUM_NUMBER 10

#define WIDTH 600
#define HEIGHT 600
#define MOVEMENT_DURATION 400

#define TOP 0
#define LEFT 1
#define RIGHT 2
#define BOT 3

#define INIT_PACMAN_ROW 1
#define INIT_PACMAN_COLUMN 1

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
  if(!game_finished(pacMan)){
    if (c=='w' && MapClass_availableCell(map,PacMan_getRow(pacMan),PacMan_getColumn(pacMan),TOP)){
      PacMan_setMovementDirection(pacMan,TOP);
      PacMan_initMovement(pacMan);
    }
    
    if (c=='s'&& MapClass_availableCell(map,PacMan_getRow(pacMan),PacMan_getColumn(pacMan),BOT)){
      PacMan_setMovementDirection(pacMan,BOT);
      PacMan_initMovement(pacMan);

    }
    
    if (c=='a'&& MapClass_availableCell(map,PacMan_getRow(pacMan),PacMan_getColumn(pacMan),LEFT)){
      PacMan_setMovementDirection(pacMan,LEFT);
      PacMan_initMovement(pacMan);

    }
    
    if (c=='d'&& MapClass_availableCell(map,PacMan_getRow(pacMan),PacMan_getColumn(pacMan),RIGHT)){
      PacMan_setMovementDirection(pacMan,RIGHT);
      PacMan_initMovement(pacMan);

    }

    glutPostRedisplay();
  }
};


//-----------------------------------------------
//-----------------------------------------------
void idle()
{
  if(game_finished(pacMan)){
    drawWin();
  }else{
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
}


//---------------------------
void generateMap(){
  rows =21;
  columns =21;/*
  printf("---Rows---- \n");
  rows = getMargin(MINIMUM_NUMBER);
  printf("---Columns--- \n");
  columns = getMargin(MINIMUM_NUMBER);*/

  map = newMapClass(rows,columns,HEIGHT,WIDTH);
  MapClass_createMap(map);
  MapClass_printMap(map);
}

//--------------------------------------
void generatePacMan(){

  pacMan = newPacMan(map, INIT_PACMAN_ROW, INIT_PACMAN_COLUMN, MOVEMENT_DURATION);
  PacMan_draw(pacMan);
}


