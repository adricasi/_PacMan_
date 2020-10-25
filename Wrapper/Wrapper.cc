#include "../MapConstruction/MapClass.h"
#include "../PacMan/PacMan.h"
#include "../Enemies/Enemies.h"
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

        void MapClass_freeMap(MapClass* v){
            v->freeMap();
        }

        void MapClass_drawMap(MapClass* v){
            v->drawMap();
        }

        bool MapClass_availableCell(MapClass* v, int row, int column, int neighbour){
            v->availableCell(row, column, neighbour);
        }

        //---------------------------------------------

        PacMan* newPacMan(MapClass* map, int init_row, int init_column, int duration){
            return new PacMan(map, init_row, init_column, duration);
        }

        void PacMan_initMovement(PacMan* v){
            v->init_movement();
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

        void PacMan_setMovementDirection(PacMan* v, int direction){
            v->set_movementDirection(direction);
        }

        bool game_finished(PacMan* v){
            v->objectiveCompleted();
        }

        //---------------------EnemiesController---------------------------------------

        EnemiesController* newEnemiesController(MapClass* map, int numEnemies, int duration){
            return new EnemiesController(map, numEnemies, duration);
        }

        void EnemiesController_spawnEnemies(EnemiesController* v){
            v->spawnEnemies();
        }

        void EnemiesController_drawEnemies(EnemiesController* v){
            v->drawEnemies();
        }

        void EnemiesController_integrateEnemies(EnemiesController* v, long t){
            v->integrateEnemies(t);
        } 
}