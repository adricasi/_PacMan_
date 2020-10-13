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

#ifdef __cplusplus
}
#endif
#endif