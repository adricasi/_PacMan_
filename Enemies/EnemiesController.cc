#include "Enemies.h"
#include "../MapConstruction/MapClass.h"
#include <stdio.h>
#include <stdlib.h>

EnemiesController::EnemiesController(MapClass* map, int numEnemies, int duration){
    m_map = map;
    m_numEnemies = numEnemies;
    m_ghostEnemies = (GhostEnemy *)malloc(m_numEnemies * sizeof(GhostEnemy));    
    m_movementsDuration = duration;
}

void EnemiesController::spawnEnemies(){
    for(int i=0; i<m_numEnemies; i++){
        //Generate random position
        Cell cell = m_map->chooseRandomCellHome();
        //Init ghost
        m_ghostEnemies[i].initGhostEnemy(m_map, cell.get_row(), cell.get_column(), m_movementsDuration);
    }
}

void EnemiesController::drawEnemies(){
    for(int i=0; i<m_numEnemies; i++){
        m_ghostEnemies[i].draw();
    }
}