#include "include/SDL2/SDL.h"

#include <iostream>

struct Cell {
public:
  SDL_Rect cell;
  
  int x;
  int y;
  
  Cell(int x=0, int y=0) : x(x), y(y) { cell.x = x; cell.y = y;}
  void update();

  // GETTERS
  int getX() const { return cell.x; }
  int getY() const { return cell.y; }

};

void Cell::update() {
  cell.x = (x / 25) * 25;
  cell.y = (y / 25) * 25;
  cell.w = 25;
  cell.h = 25;
}

