#include "MapClass.h"
#include "../CommonFunctions/CommonFunctionsC++.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

void MapClass::eatFood(int row, int column){
    m_map[row][column].eatFood();
}

bool MapClass::allFoodEated(){
    for(int row=0; row<m_rows;row++){
        for(int column=0; column<m_columns; column++){
            Cell cell = m_map[row][column];
            if(cell.get_value()==CORRIDOR && m_map[row][column].haveFood() && !isInHomeRange(cell)){
                return false;
            }
        }
    }
    return true;
}