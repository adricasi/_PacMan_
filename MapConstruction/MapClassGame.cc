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
