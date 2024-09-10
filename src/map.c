#include "../inc/maze.h"

/* Map definition*/
int map[MAP_WIDTH][MAP_HEIGHT] = 
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 2, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 2, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 1, 2, 1, 0, 1},
	{1, 0, 1, 0, 2, 1, 0, 2, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


/* Camera parameters */
double posX = 1.5, posY = 1.5; /* Player Start position */
double dirX = 1, dirY = 0;  /* Faced starting direction */
double planeX = 0, planeY = 0.6; /* Camera view  */
