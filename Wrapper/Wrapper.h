#include <stdbool.h>
#ifndef __WRAPPER_H
#define __WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MapClass MapClass;

MapClass* newMapClass(int rows, int columns, int height, int width);

void MapClass_createMap(MapClass* v);

void MapClass_printMap(MapClass* v);

void MapClass_freeMap(MapClass* v);

void MapClass_drawMap(MapClass* v);

float MapClass_getCellPositionX(MapClass* v, int row, int column);

float MapClass_getCellPositionY(MapClass* v, int row, int column);

bool MapClass_availableCell(MapClass* v, int row, int column, int neighbour);

//--------------------------------------------------------------

typedef struct PacMan PacMan;

PacMan* newPacMan(MapClass* map, int init_row, int init_column, int duration);

void PacMan_initMovement(PacMan* v);

void PacMan_integrate(PacMan* v, long t);

void PacMan_draw(PacMan* v);

int PacMan_getRow(PacMan* v);

int PacMan_getColumn(PacMan* v);

void PacMan_setMovementDirection(PacMan* v, int direction);

//------------------------Game--------------------------------------
bool game_finished(PacMan* v);

#ifdef __cplusplus
}
#endif
#endif