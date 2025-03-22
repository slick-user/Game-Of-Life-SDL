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

  std::vector<std::pair<int, int>> neighbourOffsets = {
    {-50, -50}, {0, -50}, {50, -50},
    {-50, 0  },           {50,  0 }, 
    {-50, 50 }, {0,  50}, {50, 50 }
  };

  std::vector<std::pair<int, int>> deadCells; // x and y coords of dead cells
  std::vector<int> deadCellNeighbour; // neighbour count for dead cells
  std::vector<int> toRemove; 

  for (int i=0; i<int(cell.size()); i++) { 
    int neighbours = 0;

    bool found = false;
    for (auto [dx, dy] : neighbourOffsets) {
      int nx = cell[i].cell.x + dx;
      int ny = cell[i].cell.y + dy;
  
      // This is for the live cells to check their neighbours
      for (int j=0; j < int(cell.size()); j++) {
        if (cell[j].getX() == nx && cell[j].getY() == ny) { 
          neighbours++;
          found = true;
          break;
        }
      }
      if (!found && neighbours == 0) {
        bool alreadyTracked = false;
        for (int k=0; k < int(deadCells.size()); k++) {
          if (deadCells[k].first == nx && deadCells[k].second == ny) {
            deadCellNeighbour[k]++;
            alreadyTracked = true;
            break;
          }
        }
        if (!alreadyTracked) {
          deadCells.push_back({nx, ny});
          deadCellNeighbour.push_back(1);    
        }
      }
    }

    if (neighbours < 2 || neighbours > 3)
      toRemove.push_back(i); 
   
  }

  // Revive the cells that are to live
  for (int i=0; i < int(deadCells.size()); i++) {
    if (deadCellNeighbour[i] == 3) {
      cell.push_back(Cell(deadCells[i].first, deadCells[i].second));
    }
  } 

  // Remove the cells that are to die
  for (int i = int(toRemove.size()) - 1; i >= 0; i--) {
    if (toRemove[i] >= 0 && toRemove[i] < int(cell.size()) ) { 
      cell.erase(cell.begin() + toRemove[i]);
    }
  }
}

// now we check 8 dimenstions of neighbours, and we do so iteratively and we make the changes after going through the entire array of cells instead of while iterating
