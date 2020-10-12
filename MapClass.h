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

//---------------------Cell of Cells-----------------------------------------------------------------------

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
    void defineNeighbour(int totalRows, int totalColumns, int cellRow, int cellColumn, int neighbour);
    void visit();

    // get/set----------------------------------
    void set_row(int row);
    void set_column(int column);
    void set_value(int value);
    void set_visited(bool visited);

    int get_row();
    int get_column();
    int get_value();
    bool get_visited();
    neighbour get_neighbour(int neighbour);

    bool equal(Cell cell);
};

//---------------------Stack of Cells-----------------------------------------------------------------------

class Stack {
private:
  int item, i;
  Cell* arr_stack;
  int top;
  int m_max_size;

public:
  void initStack(int maxSize);
  void push(Cell cell);
  Cell pop();
  int get_top();
};


//------------------------------------------------------------------------------------------
class MapClass{
    
    private:
        //Variables
        int m_rows;
        int m_columns;
        int m_cellsToVisit;
        Cell** m_map;
        Cell m_currentCell;
        Cell m_initialCellHome;
        Stack m_stack;

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
        int randomRange(int min, int max);
        void visit(Cell cell);
        void visitHomeCell(int row, int column,int value);

        void createHome();
        void connectHome();
        void findcorridor(Cell homeDoor);
        
        void generateRandomMap();

        Cell checkNeighbours();
        void removeWalls(Cell nextCell);

        // get/set------------------------------------
        Cell getCell(Cell cell){
          return m_map[cell.get_row()][cell.get_column()];
        }

};

#endif