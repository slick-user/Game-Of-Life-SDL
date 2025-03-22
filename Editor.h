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

  std::vector<Cell> cell;
  
};

void Editor::setX(int Xval) {
  x = Xval;
}
  
void Editor::setY(int Yval) {
  y = Yval;
}

void Editor::placeCell() {
  size++;
  cell.push_back(Cell(x, y));
  cell.back().update();
}

// We need to create a delete cell function that deletes the cells efficiently, and also does the computations efficiently
// 
