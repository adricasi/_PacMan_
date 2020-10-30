#include <GL/glut.h>
#include "Wrapper/Wrapper.h"
#include "CommonFunctions/CommonFunctionsC.h"
#include <stdio.h>


#define NUM_ENEMIES 8
#define MOVEMENT_DURATION 400

#define ROWS_COLUMNS_MINIMUM_NUMBER 10

#define INIT_PACMAN_ROW 1
#define INIT_PACMAN_COLUMN 1

#define WIDTH 600
#define HEIGHT 600

#define TOP 0
#define LEFT 1
#define RIGHT 2
#define BOT 3

//-----------------------------------------------

void display();;
void keyboard(unsigned char c,int x,int y);
void idle();
void generateMap();
void generatePacMan();
void generateEnemies();
void reset();

//-----------------------------------------------

struct PacMan* pacMan;
struct MapClass* map;
struct EnemiesController* enemiesController;
int rows;
int columns;
long last_t;
bool gameFinished;
bool memoryFree;

//-----------------------------------------------
// -- MAIN PROCEDURE
//-----------------------------------------------

int main(int argc,char *argv[])
{
  reset();

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

void reset(){
  last_t=0;
  gameFinished = false;
  memoryFree = false;

  generateMap();
  generatePacMan();
  generateEnemies();
}


//------------------------------------------------------------

void display()
{
  
  glClearColor(0.0,0.0,0.2,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  MapClass_drawMap(map);  
  PacMan_draw(pacMan);
  EnemiesController_drawEnemies(enemiesController);

  glutSwapBuffers();
}

//-----------------------------------------------
void keyboard(unsigned char c,int x,int y)
{
  // r to reset the game when the game has finsihed

  //Pacman movement w-top s-bot a-left d-right
  if(!gameFinished){
    if (c=='w'){
      PacMan_setMovementDirection(pacMan,TOP);
      PacMan_initMovement(pacMan);
    }
    
    if (c=='s'){
      PacMan_setMovementDirection(pacMan,BOT);
      PacMan_initMovement(pacMan);
    }
    
    if (c=='a'){
      PacMan_setMovementDirection(pacMan,LEFT);
      PacMan_initMovement(pacMan);
    }
    
    if (c=='d'){
      PacMan_setMovementDirection(pacMan,RIGHT);
      PacMan_initMovement(pacMan);
    }

    glutPostRedisplay();
  }else if(c=='r'){
    reset();
  }
};


//-----------------------------------------------
void idle()
{
  //Check if game finished
  if(!memoryFree){
    if(PacMan_gameFinished(pacMan)){
      gameFinished = true;
      drawWin();
    }else if(EnemiesController_gameFinished(enemiesController, PacMan_getX(pacMan), PacMan_getY(pacMan), PacMan_getSizeX(pacMan), PacMan_getSizeY(pacMan))){
      gameFinished = true;
      drawLose();
    }
  }

  //integrations
  if(!gameFinished){
    long t;

    t=glutGet(GLUT_ELAPSED_TIME); 

    if(last_t==0)
      last_t=t;
    else
      {
        PacMan_integrate(pacMan, t-last_t);
        EnemiesController_integrateEnemies(enemiesController, t-last_t);
        last_t=t;
      }
    glutPostRedisplay();
  }

  //free memory
  if(gameFinished && !memoryFree){
    memoryFree = true; 
    EnemiesController_freeMemory(enemiesController);
    MapClass_freeMemory(map);
  }
}


//---------------------------
void generateMap(){
  printf("---Rows---- \n");
  rows = getMargin(ROWS_COLUMNS_MINIMUM_NUMBER);
  printf("---Columns--- \n");
  columns = getMargin(ROWS_COLUMNS_MINIMUM_NUMBER);

  map = newMapClass(rows,columns,HEIGHT,WIDTH);
  MapClass_createMap(map);
  MapClass_printMap(map);
}

//--------------------------------------
void generatePacMan(){
  pacMan = newPacMan(map, INIT_PACMAN_ROW, INIT_PACMAN_COLUMN, MOVEMENT_DURATION);
}

//-------------------------------------
void  generateEnemies(){
  enemiesController = newEnemiesController(map, NUM_ENEMIES, MOVEMENT_DURATION);
  EnemiesController_spawnEnemies(enemiesController);
}
