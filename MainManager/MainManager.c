#include "MainManager.h"

int getMargin(int minimumNumber){
    int number;
    do{
        printf("Insert an odd number bigger than %d:\n",minimumNumber);
        scanf("%d",&number);
        if(isPar(number) || number<minimumNumber ){
            printf("Wrong number\n");
        }
    }while(isPar(number) || number<minimumNumber);
    return number;
}

bool isPar(int number){
    return number%2 == 0;
}

void drawWin(){
    glClearColor(0.0,0.3,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void drawLose(){
    glClearColor(0.3,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void ambientLight(){
    GLint position[4];
    GLfloat color[4];
    GLfloat diffuse[4] = {0.0,0.0,0.0,0.0};

    position[0]=0; position[1]=0; position[2]=0; position[3]=1; 
    glLightiv(GL_LIGHT0,GL_POSITION,position);

    color[0]=0.3; color[1]=0.3; color[2]=0.3; color[3]=1;
    glLightfv(GL_LIGHT0,GL_AMBIENT,color);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse);
    glEnable(GL_LIGHT0);
}