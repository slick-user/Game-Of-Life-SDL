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

  void step();

  std::vector<Cell> cell;
  
};

void Editor::setX(int Xval) {
  x = Xval;
}
  
void Editor::setY(int Yval) {
  y = Yval;
}

void Editor::placeCell() {
  bool is_cell = false;
  for (const auto& c : cell) {
    if ( (((x/50) * 50) == (c.x / 50) * 50) && ((y/50) * 50 == (c.y / 50) * 50)) {
      is_cell = true;
      break;
    } 
  }
  if (!is_cell) {
    cell.push_back(Cell(x, y));
    cell.back().update();
  }
  else {
    std::cout << "cannot make a size there";
  }
}

void Editor::deleteCell() {
  int index = -1;
  for (int i=0; i<int(cell.size()); i++) {
    if ( (((x/50) * 50) == (cell[i].x / 50) * 50) && ((y/50) * 50 == (cell[i].y / 50) * 50)) {
      index = i;
      break;
    } 
  }
  if (index != -1)
    cell.erase(cell.begin() + index);
}

void Editor::step() {

  for (int i=0; i<int(cell.size()); i++) { 
    int neighbours = 0;
    for (int j=0; j<int(cell.size()); j++) {
      if (j == i)
        continue;
      else {
        if (cell[i].x + 50 == cell[j].x)
          neighbours++;
        
        if (cell[i].x - 50 == cell[j].x)
          neighbours++;

        if (cell[i].y + 50 == cell[j].y)
          neighbours++;

        if (cell[i].y - 50 == cell[j].y)
          neighbours++;

      }
    }
    if (neighbours < 2)
      cell.erase(cell.begin() + i);

  }

// for now we have a system for checking neighbouring cells but tbh I'm pretty sure this is a garbage way of doing this

}
