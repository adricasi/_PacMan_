#ifndef __MAPCLASS_H
#define __MAPCLASS_H

#define WALL 0
#define CORRIDOR 1

#define HOMEROWS 5
#define HOMECOLUMNS 4
#define CORRIDORTYPES 5

#define TOPLEFT 0
#define TOP 1
#define TOPRIGHT 2

#define LEFT 3
#define RIGHT 4

#define BOTLEFT 5
#define BOT 6
#define BOTRIGHT 7

class Cell{
   private:
        //Variables
        int m_row;
        int m_column;
        int m_value;
        bool m_visited;

        int cell_path_n[2];
        int cell_path_e[2];
        int cell_path_s[2];
        int cell_path_w[2];

    public:
      void initCell(int rows, int columns, int cellRow, int cellColumn);
      void set_row(int row){
        m_row = row;
      }
      void set_column(int column){
        m_column = column;
      }
      void set_value(int value){
        m_value = value;
      }
      void set_visited(bool visited){
        m_visited = visited;
      }

      int get_row(){
        return m_row;
      }
      int get_column(){
        return m_column;
      }
      int get_value(){
        return m_value;
      }
      bool get_visited(){
        return m_visited;
      }
};

class MapClass{
    
    private:
        //Variables
        int m_rows;
        int m_columns;
        int m_visitedCells;
        Cell** m_map;
        Cell m_initialCellHome;
        // Home definition
        int home[HOMEROWS][HOMECOLUMNS] = {{WALL,WALL,WALL,CORRIDOR},
                                  {WALL,CORRIDOR,CORRIDOR,CORRIDOR},
                                  {WALL,CORRIDOR,CORRIDOR,CORRIDOR},
                                  {WALL,CORRIDOR,CORRIDOR,CORRIDOR},
                                  {WALL,WALL,WALL,WALL}};

    public:
        //Constructor
        MapClass(int rows, int columns);    

        //Functions
        void createMap();
        void printMap();
        
        void initMap();
        void createHome();
        void defineBordersWalls();
        void writeCell(int row, int column, int value);

        int randomRange(int min, int max);

        void generateRandomMap();
};

#endif