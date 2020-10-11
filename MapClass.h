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

      bool equal(Cell cell){
        if(m_row == cell.get_row() && m_column == cell.get_column()){
          return true;
        }else{
          return false;
        }
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

void push(Cell cell) {
  if(top != m_max_size){
    arr_stack[top] = cell;
    top = top+1;
  }
}

Cell pop() {
  if (top != 0){
    top = top-1;
    return arr_stack[top];
  }
}

  int get_top(){
    return top;
  }
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

        void generateRandomMap();

        Cell checkNeighbours();
        void removeWalls(Cell nextCell);

        // get/set------------------------------------
        Cell getCell(Cell cell){
          return m_map[cell.get_row()][cell.get_column()];
        }

};

#endif