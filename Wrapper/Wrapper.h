#include <stdbool.h>
#ifndef __WRAPPER_H
#define __WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MapClass MapClass;

MapClass* newMapClass(int rows, int columns);

void MapClass_createMap(MapClass* v);

void MapClass_printMap(MapClass* v);

int MapClass_getValue(MapClass* v, int row, int column);

void MapClass_freeMap(MapClass* v);

void MapClass_drawMap(MapClass* v, int WIDTH, int HEIGHT);

float MapClass_getCellPositionX(MapClass* v, int row, int column);

float MapClass_getCellPositionY(MapClass* v, int row, int column);

//--------------------------------------------------------------

typedef struct PacMan PacMan;

PacMan* newPacMan(int maxRows, int maxColumns, int height, int width);

void PacMan_setPosition(PacMan* v, int row, int column, float x, float y);

void PacMan_setSize(PacMan* v, float sizeX, float sizeY);

void PacMan_initMovement(PacMan* v, int destination_row,int destination_column, int duration);

void PacMan_integrate(PacMan* v, long t);

void PacMan_draw(PacMan* v);

int PacMan_getRow(PacMan* v);

int PacMan_getColumn(PacMan* v);

#ifdef __cplusplus
}
#endif
#endif