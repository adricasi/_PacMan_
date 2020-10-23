#include "../MapConstruction/MapClass.h"
#include "../PacMan/PacMan.h"
#include "Wrapper.h"

extern "C" {
        MapClass* newMapClass(int row, int columns, int height, int width) {
                return new MapClass(row, columns, height, width);
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

        bool MapClass_availableCell(MapClass* v, int row, int column, int neighbour){
            v->availableCell(row, column, neighbour);
        }

        //---------------------------------------------

        PacMan* newPacMan(MapClass* map, int init_row, int init_column){
            return new PacMan(map, init_row, init_column);
        }

        void PacMan_setPosition(PacMan* v, int row, int column, float x, float y){
            v->set_position(row, column, x, y);
        }

        void PacMan_setSize(PacMan* v, float sizeX, float sizeY){
            v->set_size(sizeX,sizeY);
        }

        void PacMan_initMovement(PacMan* v, int destination_row,int destination_column, int duration){
            v->init_movement(destination_row, destination_column,duration);
        }

        void PacMan_integrate(PacMan* v, long t){
            v->integrate(t);
        }

        void PacMan_draw(PacMan* v){
            v->draw();
        }

        int PacMan_getRow(PacMan* v){
            v->get_row();
        }

        int PacMan_getColumn(PacMan* v){
            v->get_column();
        }
}