#include "../MapConstruction/MapClass.h"
#include "Wrapper.h"

extern "C" {
        MapClass* newMapClass(int row, int columns) {
                return new MapClass(row, columns);
        }

        void MapClass_createMap(MapClass* v){
            v->createMap();
        }

        void MapClass_printMap(MapClass* v){
            v->printMap();
        }

        int MapClass_getValue(MapClass* v, int row, int column){
            v->getValue(row, column);
        }
        void MapClass_freeMap(MapClass* v){
            v->freeMap();
        }

        void MapClass_drawMap(MapClass* v, int WIDTH, int HEIGHT){
            v->drawMap(WIDTH, HEIGHT);
        }
}