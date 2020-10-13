#include <GL/glut.h>
#include "Wrapper.h"
#define COLUMNS 21
#define ROWS 21
#define WIDTH 300
#define HEIGHT 300

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
  glutInitWindowPosition(50, 50);
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
  struct MapClass* map = newMapClass(21,21);
  MapClass_createMap(map);
  MapClass_printMap(map);


  int i,j;

  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(i=0;i<WIDTH;i++)
    for(j=0;j<HEIGHT;j++)
      if( (keyflag==0 && (i+j)%2==0) || (keyflag==1 && (i+j)%2==1) ) 
	{
	  glColor3f(0.8,0.8,0.8);
	  glBegin(GL_QUADS);

	  glVertex2i(i*WIDTH/COLUMNS,j*HEIGHT/ROWS); 
	  glVertex2i((i+1)*WIDTH/COLUMNS,j*HEIGHT/ROWS); 
	  glVertex2i((i+1)*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS); 
	  glVertex2i(i*WIDTH/COLUMNS,(j+1)*HEIGHT/ROWS); 

	  glEnd();
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


