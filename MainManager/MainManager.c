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