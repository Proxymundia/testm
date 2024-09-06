#ifndef MAZE_H
#define MAZE_H

/* header files */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* macros */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
typedef struct {
    int x;
    int y;
} point_t;
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
extern SDL_Texture *wallTexture;

bool init(void);
void raycaster(int *maze, bool textured);
void renderWalls(int *maze, SDL_Point map, SDL_Point rayPos, SDL_Point rayDir, double distToWall, int x, int side, bool textured);
void updateRenderer(bool textured);

/* Helper functions for texture loading and management */
bool loadMedia(void); /* Load textures and other media */
void closeMedia(void); /* Clean up textures and other media */
#endif /* MAZE_H */

