#include "CommonFunctionsC.h"
#include <stdio.h>
#include <stdbool.h>

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

float get_cellPositonX(int column, int maxColumns, int WIDTH){
    float x = (column+0.5)*WIDTH/maxColumns;
    return x;    
}

float get_cellPositonY(int row, int maxRows, int HEIGHT){
    int inversRow = maxRows-1 - row;
    float y = (inversRow+0.5)*HEIGHT/maxRows;                    
    return y;
}

float get_cellSizeX(int column, int maxColumns, int WIDTH){
    float sizeX = ((column+1)*WIDTH/maxColumns-column*WIDTH/maxColumns)/2.0;
    return sizeX;
}

float get_cellSizeY(int row, int maxRows, int HEIGHT){
    int inversRow = maxRows-1 - row;
    float sizeY = ((inversRow+1)*HEIGHT/maxRows-inversRow*HEIGHT/maxRows)/2.0;
    return sizeY;
}
