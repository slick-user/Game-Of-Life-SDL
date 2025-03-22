#include "include/SDL2/SDL.h"

#include <iostream>

struct Cell {
public:
  SDL_Rect cell;
  
  int x;
  int y;
  
  Cell(int x=0, int y=0) : x(x), y(y) { cell.x = x; cell.y = y; std::cout << "cell created" << std::endl; }
  void update();

};

void Cell::update() {
  cell.x = (x / 50) * 50;
  cell.y = (y / 50) * 50;
  cell.w = 50;
  cell.h = 50;
}

