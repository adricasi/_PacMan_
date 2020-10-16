#include "MapClass.h"
#include <stdio.h>
#include <GL/glut.h>

void Food::drawFood(int maxRows, int maxColumns, int cellRow, int cellColumn, int WIDTH, int HEIGHT){
    glColor3f(0.5,0.2,0.9);
    glBegin(GL_QUADS);

    float columnLowPosition = cellColumn*WIDTH/maxColumns;
    float columnHightPosition = (cellColumn+1)*WIDTH/maxColumns;
    float rowLowPosition =cellRow*HEIGHT/maxRows;
    float rowHightPosition =(cellRow+1)*HEIGHT/maxRows;

    float sizeRow = (columnHightPosition-columnLowPosition)/1.4;
    float sizeColumn = (rowHightPosition-rowLowPosition)/1.4;

    glVertex2i(columnLowPosition+sizeColumn,rowLowPosition+sizeRow); 
    glVertex2i(columnHightPosition-sizeColumn,rowLowPosition+sizeRow); 
    glVertex2i(columnHightPosition-sizeColumn,rowHightPosition-sizeRow); 
    glVertex2i(columnLowPosition+sizeColumn,rowHightPosition-sizeRow); 


    glEnd();
}