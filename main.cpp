#include "include/SDL2/SDL.h"

#include "Editor.h"
#include "include/SDL2/SDL_keyboard.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

const int ROWS = 64;
const int COLS = 64;
const int GRID_WIDTH = 25;
const int GRID_HEIGHT = 25;

SDL_Window *window;
SDL_Renderer *renderer; 

SDL_Rect camera = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};

SDL_Rect Cell;

Editor editor;

// FUNCTION PROTOTYPES

// SET UP FUNCTIONS
void createGrid();

void kill() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int init() {
  
  if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) 
  {
    system("pause");
    return 1;
  }

  window = SDL_CreateWindow("CONWAYS GAME OF LIFE", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  SDL_RenderFillRect(renderer, &Cell); 
  SDL_SetRenderDrawColor(renderer, 140, 0, 70, 255);

  return 0;
}

void loop() {
  int offset_x = 0; // For the Camera
  int offset_y = 0;

  bool game_loop = true;
  SDL_Event event;

  while (game_loop) {
    
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          game_loop = false;
          break;
      
        case SDL_MOUSEMOTION:
          editor.setX(event.motion.x);
          editor.setY(event.motion.y);
          break; 
      
        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT) {
            editor.placeCell();
            //break;  
          }

          if (event.button.button == SDL_BUTTON_RIGHT) {
            editor.deleteCell();
            break;
          }        
      }
      
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          editor.step();
          break;
      }
      
    }

    // CAMERA MOVEMENT
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W]) {
      offset_y += 10;
    }
    else if (state[SDL_SCANCODE_S]) {
      offset_y -= 10;
    }
    else {
      offset_y = 0;
    }

    if (state[SDL_SCANCODE_A]) {
      offset_x += 10;
    }
    else if (state[SDL_SCANCODE_D]) {
      offset_x -= 10;
    }
    else {
      offset_x = 0;
    }

    for (int i=0; i<int(editor.cell.size()); i++) {
      editor.cell[i].x += offset_x;
      editor.cell[i].y += offset_y;
      editor.cell[i].update();
    }

    SDL_RenderClear(renderer);

    createGrid();
    // Rendering Cells
    for (int i=0; i<int(editor.cell.size()); i++) {
      SDL_SetRenderDrawColor(renderer, 0, 60, 70, 255);
      SDL_RenderFillRect(renderer, &editor.cell[i].cell);
    }

    // Rendering the Background
    SDL_SetRenderDrawColor(renderer, 140, 60, 70, 255);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000/60);
  }

}

int main(int argc, char* args[]) {

  // SETTING UP SOME STUFF I GUESS
  init();  
  loop();  
  kill();

  return 0;
}

void createGrid() {
  for (int i=0; i < ROWS; i++) {
    for (int j=0; j < COLS; j++) {

      SDL_Rect Grid = (SDL_Rect) {j*GRID_WIDTH, i*GRID_HEIGHT, 
                                  GRID_WIDTH, GRID_HEIGHT};

      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
      SDL_RenderDrawRect(renderer, &Grid);
    
    }
  }
}

