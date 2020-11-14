#include "../C_Cell/Cell.h"

#ifndef __STACK_H
#define __STACK_H


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

#endif