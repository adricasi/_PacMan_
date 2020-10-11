#ifndef __MAPCLASS_H
#define __MAPCLASS_H

#define WALL 0
#define CORRIDOR 1

#define HOMEROWS 5
#define HOMECOLUMNS 4
#define CORRIDORTYPES 5

#define TOP 0
#define LEFT 1
#define RIGHT 2
#define BOT 3

struct neighbour{
  bool exists;
  int row;
  int column;
};

class Cell{
   private:
        //Variables
        int m_row;
        int m_column;
        int m_value;
        bool m_visited;

        neighbour cell_path_top;
        neighbour cell_path_right;
        neighbour cell_path_bot;
        neighbour cell_path_left;

    public:
      void initCell(int totalRows, int totalColumns, int cellRow, int cellColumn);
      void checkNeighbour();
      void defineNeighbour(int totalRows, int totalColumns, int cellRow, int cellColumn, int neighbour);

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
      neighbour get_neighbour(int neighbour){
        if(neighbour == TOP){
          return cell_path_top;
        }else if(neighbour == RIGHT){
          return cell_path_right;
        }else if(neighbour == BOT){
          return cell_path_bot;
        }else if(neighbour == LEFT){
          return cell_path_left;
        }
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