#ifndef MAZE_H
#define MAZE_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

/*Global Variables*/
extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool SDL(void);
void closeSDL(void);

#endif /* MAZE_H */

