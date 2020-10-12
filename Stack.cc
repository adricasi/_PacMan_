#include "MapClass.h"
#include <stdlib.h>

void Stack::initStack(int maxSize) {
    top = 0;
    m_max_size = maxSize;
    arr_stack = (Cell *)malloc(m_max_size * sizeof(Cell));
}

void Stack::push(Cell cell) {
  if(top != m_max_size){
    arr_stack[top] = cell;
    top = top+1;
  }
}

Cell Stack::pop() {
  if (top != 0){
    top = top-1;
    return arr_stack[top];
  }
}

int Stack::get_top(){
  return top;
}