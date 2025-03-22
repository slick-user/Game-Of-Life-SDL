#include "Cell.h"
#include <algorithm>
#include <unordered_map>
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

struct PairHash {
  std::size_t operator() (const std::pair<int, int>& p) const {
    return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
  }
};

void Editor::step() {

  std::vector<std::pair<int, int>> neighbourOffsets = {
    {-50, -50}, {0, -50}, {50, -50},
    {-50, 0  },           {50,  0 }, 
    {-50, 50 }, {0,  50}, {50, 50 }
  };

  std::unordered_map<std::pair<int, int>, int, PairHash> deadCellMap;
  std::vector<int> toRemove; 

  for (int i=0; i<int(cell.size()); i++) { 
    int neighbours = 0;

    for (auto [dx, dy] : neighbourOffsets) {
      int nx = cell[i].cell.x + dx;
      int ny = cell[i].cell.y + dy;
      bool found = false;

      // This is for the live cells to check their neighbours
      for (const auto& c : cell) {
        if (c.getX() == nx && c.getY() == ny) { 
          neighbours++;
          found = true;
          break;
        }
      }
      if (!found) {
        deadCellMap[{nx, ny}]++; 
      }
    }

    if (neighbours < 2 || neighbours > 3)
      toRemove.push_back(i);  
  }

  // Revive the cells that are to live
  for (const auto& [pos, count] : deadCellMap) {
    if (count == 3) {
      cell.push_back(Cell(pos.first, pos.second));
    }
  } 

  // Remove the cells that are to die
  std::sort(toRemove.begin(), toRemove.end(), std::greater<int>());
  for (int i = int(toRemove.size()) - 1; i >= 0; i--) {
    if (toRemove[i] >= 0 && toRemove[i] < int(cell.size()) ) { 
      cell.erase(cell.begin() + toRemove[i]);
    }
  }

  for (int i=0; i<cell.size(); i++) {
    cell[i].update();
  }
}

