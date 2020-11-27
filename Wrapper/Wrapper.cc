#include "Wrapper.h"
#include "../Classes/C_PacMan/PacMan.h"
#include "../Classes/C_Enemies/Enemies.h"
#include "../Classes/C_Map/Map.h"



extern "C" {
    //----------------------Map----------------------------------------

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


    //----------------------PacMan----------------------------------------

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
        return v->get_row();
    }

    int PacMan_getColumn(PacMan* v){
        return v->get_column();
    }
    
    float PacMan_getX(PacMan* v){
        return v->get_x();
    }
    
    float PacMan_getY(PacMan* v){
        return v->get_y();
    }

    float PacMan_getZ(PacMan* v){
        return v->get_z();
    }
    
    float PacMan_getRadius(PacMan* v){
        return v->get_radius();
    }

    void PacMan_setMovementDirection(PacMan* v, int direction){
        v->set_movementDirection(direction);
    }

    bool PacMan_gameFinished(PacMan* v){
        return v->objectiveCompleted();
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

    bool EnemiesController_gameFinished(EnemiesController* v, float pacmanX, float pacmanZ, float pacmanRadius){
        return v->enemiesObjectiveCompleted(pacmanX, pacmanZ, pacmanRadius);
    }
    void EnemiesController_freeMemory(EnemiesController* v){
        v->freeEnemies();
    }
}