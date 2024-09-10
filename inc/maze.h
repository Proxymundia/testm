#ifndef MAZE_H
#define MAZE_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define MAP_WIDTH 11
#define MAP_HEIGHT 10

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


/*Global Variables*/
extern SDL_Window *window;
extern SDL_Renderer *renderer;

/* Define Map*/

extern int map[MAP_WIDTH][MAP_HEIGHT];

/*Camera Paremetres*/
extern double posX, posY;
extern double dirX, dirY;
extern double planeX, planeY;

bool SDL(SDL_Window **window, SDL_Renderer **renderer);
void closeSDL(SDL_Window *window, SDL_Renderer *renderer);
void drawWalls(SDL_Renderer *renderer);
void handleInput(void);
void rotateCamera(double angle);
void update(void);
#endif /* MAZE_H */

