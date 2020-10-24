#ifndef __ENEMIES_H
#define __ENEMIES_H
//-----------------------------------------------
#define MOVE 1
#define QUIET 2
//-----------------------------------------------

typedef struct MapClass MapClass;

class GhostEnemy {

    int m_movementDuration;
    int m_movementDirection;

    MapClass* m_map;
    int m_row,m_column;   //-- Current position
    int m_destinationRow, m_destinationColumn;
    float m_x,m_y;   //-- Current position
    float vx,vy; //-- Velocity vector
    int state;
    float m_sizeX,m_sizeY;

    long time_remaining;

    public:
        void initGhostEnemy(MapClass* map, int init_row, int init_column, int duration);

        void init_movement();
        void integrate(long t);
        void nextCell();

        void draw();
        bool objectiveCompleted();

        void set_movementDirection(int direction);
        void set_position(int row, int column, float x, float y);
        void set_size(float sizeX, float sizeY);

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
};


#endif
