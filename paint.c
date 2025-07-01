#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

#define PEN_SIZE 5

#define WHITE 0xffffff
#define RED 0xff0000
#define ORANGE 0xfc7f03
#define YELLOW 0xfce303
#define GREEN 0x2dfc03
#define BLUE 0x0328fc
#define INDIGO 0x0328fc
#define VIOLET 0xfc03df
#define BLACK 0x000000

void clearScreen(SDL_Surface *pSurface) {
  SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_FillRect(pSurface, &background, BLACK);
}

void drawOnMouse(SDL_Surface *pSurface, SDL_MouseMotionEvent event) {
  SDL_Rect mark = {event.x, event.y, PEN_SIZE, PEN_SIZE};
  SDL_FillRect(pSurface, &mark, WHITE);
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL Init Failed: %s\n", SDL_GetError());
  }

  SDL_Window *pWindow = SDL_CreateWindow("Star Field", SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED, 900, 700, 0);

  if (!pWindow) {
    fprintf(stderr, "Failed to create Window");
  }

  SDL_Surface *pSurface = SDL_GetWindowSurface(pWindow);

  if (!pSurface) {
    fprintf(stderr, "Failed to get window surface");
  }

  SDL_Rect rect = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50};

  bool running = true;
  bool draw = false;

  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        running = false;
        return 0;
      }

      if(event.type == SDL_MOUSEBUTTONDOWN) {
        draw = true;
      }
      else if(event.type == SDL_MOUSEBUTTONUP) {
        draw = false;
      }

      if (draw && event.type == SDL_MOUSEMOTION) {
        drawOnMouse(pSurface, event.motion);
      }
    }
    
    SDL_UpdateWindowSurface(pWindow);
  }

}
