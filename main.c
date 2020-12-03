#include "Constants.h"
#include "Wrapper/Wrapper.h"
#include "MainManager/MainManager.h"

//-----------------------------------------------

void display();;
void keyboard(unsigned char c,int x,int y);
void idle();
void generateMap();
void generatePacMan();
void generateEnemies();
void reset();

/*--- Global variables that determine the viewpoint location ---*/
int anglealpha = 90;
int anglebeta = 60;

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
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(500, 100);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("PacMan board");
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(idle);

  glBindTexture(GL_TEXTURE_2D,WALLTEXTURE);
  LoadTexture("Images/wall.jpg",64);

  glBindTexture(GL_TEXTURE_2D,ROOFTEXTURE);
  LoadTexture("Images/roof.jpg",64);

  glBindTexture(GL_TEXTURE_2D,FLOORTEXTURE);
  LoadTexture("Images/floor.jpg",64);
  
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

void PositionObserver(float alpha,float beta,int radi)
{
  float x,y,z;
  float upx,upy,upz;
  float modul;

  x = (float)radi*cos(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);
  y = (float)radi*sin(beta*2*PI/360.0);
  z = (float)radi*sin(alpha*2*PI/360.0)*cos(beta*2*PI/360.0);

  if (beta>0)
    {
      upx=-x;
      upz=-z;
      upy=(x*x+z*z)/y;
    }
  else if(beta==0)
    {
      upx=0;
      upy=1;
      upz=0;
    }
  else
    {
      upx=x;
      upz=z;
      upy=-(x*x+z*z)/y;
    }


  modul=sqrt(upx*upx+upy*upy+upz*upz);

  upx=upx/modul;
  upy=upy/modul;
  upz=upz/modul;

  gluLookAt(x,y,z,    0.0, 0.0, 0.0,     upx,upy,upz);
}

//------------------------------------------------------------

void display()
{
  glClearColor(1,1,1,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  PositionObserver(anglealpha,anglebeta,450);

  //Projection parameters
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-WIDTH*glOrtho_range,WIDTH*glOrtho_range,-HEIGHT*glOrtho_range,HEIGHT*glOrtho_range,10,2000);

  glMatrixMode(GL_MODELVIEW);

  //Lights
  ambientLight();
  PacMan_drawFieldOfViewLight(pacMan);

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

  if (c=='i' && anglebeta<=(90-4))
    anglebeta=(anglebeta+3);
  else if (c=='k' && anglebeta>=(-90+4))
    anglebeta=anglebeta-3;
  else if (c=='j')
    anglealpha=(anglealpha+3)%360;
  else if (c=='l')
    anglealpha=(anglealpha-3+360)%360;

};


//-----------------------------------------------
void idle()
{
  //Check if game finished
  if(!memoryFree){
    if(PacMan_gameFinished(pacMan)){
      gameFinished = true;
      drawWin();
    }else if(EnemiesController_gameFinished(enemiesController, PacMan_getX(pacMan), PacMan_getZ(pacMan), PacMan_getRadius(pacMan))){
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
