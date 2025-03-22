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

  // not a data type I have used before but is an interesting thing..
  std::vector<std::pair<int, int>> neighbourOffsets = {
    {-50, -50}, {0, -50}, {50, -50},
    {-50, 0  },           {50,  0 }, 
    {-50, 50 }, {0,  50}, {50, 50 }
  };

  std::vector<int> toRemove; 

  for (int i=0; i<int(cell.size()); i++) { 
    int neighbours = 0;

    for (int j=0; j<int(cell.size()); j++) {
      if (j == i) continue;
      
      for (auto [dx, dy] : neighbourOffsets) {
        if (cell[i].cell.x + dx == cell[j].cell.x && cell[i].cell.y + dy == cell[j].cell.y) { 
          neighbours++;
        }
      }
    }

    std::cout << "CELL: " << i << " has " << neighbours << " neighbours\n";

    if (neighbours < 2)
      toRemove.push_back(i); 
  
  }

  for (int i = int(toRemove.size()) - 1; i >= 0; i--) {
    if (toRemove[i] >= 0 && toRemove[i] < int(cell.size()) ) 
      cell.erase(cell.begin() + toRemove[i]);
  }

}

// now we check 8 dimenstions of neighbours, and we do so iteratively and we make the changes after going through the entire array of cells instead of while iterating
