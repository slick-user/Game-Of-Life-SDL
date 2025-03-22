#include "Cell.h"
#include <vector>

class Editor {
private:
  int x;
  int y;
  int size = 0;
 
public:
  Editor() {} 

  // SETTERS
  void setX(int x);
  void setY(int y);

  // GETTERS
  int getCells() { return size; }

  void placeCell();
  void deleteCell();

  Cell* cell;
  //std::vector<Cell> cell;
  
};

void Editor::setX(int Xval) {
  x = Xval;
}
  
void Editor::setY(int Yval) {
  y = Yval;
}

void Editor::placeCell() {
  //size++;
  //cell.push_back(Cell(x, y));
  //cell.back().update();
  Cell *NewCell = new Cell[++size];
  for (int i=0; i<size; i++) {
    if (i < size - 1) {
      NewCell[i].x = cell[i].x;
      NewCell[i].y = cell[i].y;
    } else {
      NewCell[i].x = x;
      NewCell[i].y = y;
    }

    NewCell[i].update();
  }
  delete[] cell;
  cell = NewCell;
}

// We need to create a delete cell function that deletes the cells efficiently, and also does the computations efficiently
// 
