#ifndef __MAPCLASS_H
#define __MAPCLASS_H

#define WALL 0
#define CORRIDOR 1

#define HOMEROWS 5
#define HOMECOLUMNS 4

#define TOP 0
#define LEFT 1
#define RIGHT 2
#define BOT 3

#define INITIAL_ROW 1
#define INITIAL_COLUMN 1

struct neighbour{
  bool exists;
  int row;
  int column;
};

//---------------------Food class-----------------------------------------------------------------------
class Food{
  private:
    float m_sizeX,m_sizeY;
    float m_x,m_y;   //-- Draw position
  public:
    void drawFood();
    void deleteFood();
    void set_position(int x,int y)
    {
      m_x = x;
      m_y = y;
    }
    void set_size(float sizeX, float sizeY)
    {
      m_sizeX = sizeX;
      m_sizeY = sizeY;
    }
};


//---------------------Cell class-----------------------------------------------------------------------

class Cell{
  private:
    //Variables
    float m_x, m_y;   //-- Draw position
    float m_sizeX,m_sizeY;
    int m_row, m_column; //-- Cell position
    int m_value;
    bool m_visited;
    Food m_food;
    
    neighbour cell_path_top;
    neighbour cell_path_right;
    neighbour cell_path_bot;
    neighbour cell_path_left;

  public:
    void drawCell(bool isHomeRange);
    void initCell(int totalRows, int totalColumns, int cellRow, int cellColumn);
    void defineNeighbour(int totalRows, int totalColumns, int neighbourRow, int neighbourColumn, int neighbour);
    void visit();
    void visitHomeCell(int value);

    // get/set----------------------------------
    void set_position(float x,float y);
    void set_size(float sizeX, float sizeY);
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
 
    bool isPar(int number){
    return number%2 == 0;
    }
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
  void freeStack();
};


//----------------------Map class---------------------------------------------------------------------
class MapClass{
    
    private:
        //Variables
        int m_rows;
        int m_columns;
        int m_cellsToVisit;
        bool m_breackWallToConnect = false;
        
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
        int getValue(int row, int column);
        void freeMap();
        void drawMap(int WIDTH, int HEIGHT);
        
        //--------
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
        void removeWallToSecondConnection();
        bool isInHomeRange(Cell cell);
        bool isAConnection(Cell cell, int neighbour);

        // get/set------------------------------------
        Cell getCell(Cell cell){
          return m_map[cell.get_row()][cell.get_column()];
        }

        bool isPar(int number){
          return number%2 == 0;
        }

};

#endif

