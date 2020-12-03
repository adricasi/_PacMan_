#include "../C_Map/Map.h"
#include "../C_Player/Player.h"

#ifndef __ENEMIES_H
#define __ENEMIES_H
//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

class GhostEnemy : public Player{

    int m_movementDirection;

    public:
        void initGhostEnemy(MapClass* map, int init_row, int init_column, int duration);

        void init_movement();
        void integrate(long t);
        void nextCell();
        void chooseMovementDirection();

        void draw();
        bool objectiveCompleted(float pacmanX, float pacmanZ, float pacmanRadius);

        void set_movementDirection(int direction);
};

class EnemiesController {
    MapClass* m_map;
    GhostEnemy* m_ghostEnemies;
    int m_numEnemies;
    int m_movementsDuration;

    public:
        EnemiesController(MapClass* map, int numEnemies, int duration);
        void spawnEnemies();
        void drawEnemies();
        void integrateEnemies(long t);
        bool enemiesObjectiveCompleted(float pacmanX, float pacmanY, float pacmanRadius);
        void freeEnemies();
};


#endif
