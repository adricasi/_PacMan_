#include <stdbool.h>

#ifndef __WRAPPER_H
#define __WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

//----------------------Map----------------------------------------

typedef struct MapClass MapClass;

MapClass* newMapClass(int rows, int columns, int height, int width);

void MapClass_createMap(MapClass* v);

void MapClass_printMap(MapClass* v);

void MapClass_freeMemory(MapClass* v);

void MapClass_drawMap(MapClass* v);

float MapClass_getCellPositionX(MapClass* v, int row, int column);

float MapClass_getCellPositionY(MapClass* v, int row, int column);


//----------------------PacMan----------------------------------------

typedef struct PacMan PacMan;

PacMan* newPacMan(MapClass* map, int init_row, int init_column, int duration);

void PacMan_initMovement(PacMan* v);

void PacMan_integrate(PacMan* v, long t);

void PacMan_draw(PacMan* v);

int PacMan_getRow(PacMan* v);

int PacMan_getColumn(PacMan* v);

float PacMan_getX(PacMan* v);

float PacMan_getY(PacMan* v);

float PacMan_getZ(PacMan* v);

float PacMan_getRadius(PacMan* v);

void PacMan_setMovementDirection(PacMan* v, int direction);

bool PacMan_gameFinished(PacMan* v);

void PacMan_Lights(PacMan* v);

//---------------------EnemiesController---------------------------------------

typedef struct EnemiesController EnemiesController;

EnemiesController* newEnemiesController(MapClass* map, int numEnemies, int duration);

void EnemiesController_spawnEnemies(EnemiesController* v);

void EnemiesController_drawEnemies(EnemiesController* v);

void EnemiesController_integrateEnemies(EnemiesController* v, long t);

bool EnemiesController_gameFinished(EnemiesController* v, float pacmanX, float pacmanZ, float pacmanRadius);

void EnemiesController_freeMemory(EnemiesController* v);

#ifdef __cplusplus
}
#endif
#endif