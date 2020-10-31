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

        void MapClass_freeMemory(MapClass* v){
            v->freeMap();
        }

        void MapClass_drawMap(MapClass* v){
            v->drawMap();
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
        
        float PacMan_getX(PacMan* v){
            v->get_x();
        }
        
        float PacMan_getY(PacMan* v){
            v->get_y();
        }

        float PacMan_getSizeX(PacMan* v){
            v->get_sizeX();
        }
        
        float PacMan_getSizeY(PacMan* v){
            v->get_sizeY();
        }

        void PacMan_setMovementDirection(PacMan* v, int direction){
            v->set_movementDirection(direction);
        }

        bool PacMan_gameFinished(PacMan* v){
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

        bool EnemiesController_gameFinished(EnemiesController* v, float pacmanX, float pacmanY, float pacmanSizeX, float pacmanSizeY){
            v->enemiesObjectiveCompleted(pacmanX, pacmanY, pacmanSizeX, pacmanSizeY);
        }
        void EnemiesController_freeMemory(EnemiesController* v){
            v->freeEnemies();
        }
}