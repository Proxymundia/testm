#include "../inc/maze.h"

/**
 * renderWalls - draws slice of wall to buffer
 * @maze: 2D array defining maze map
 * @map: X/Y coordinates of box of maze currently in
 * @rayPos: X/Y coordinates of ray position
 * @rayDir: direction of X/Y coordinates of ray position
 * @distToWall: distance to wall from camera
 * @x: number of ray casted
 * @side: determines whether wall is N/S or E/W
 * @textured: True if user enabled textures, otherwise False
 * Return: oid
 */
void renderWalls(int *maze, SDL_Point map, point_t rayPos, point_t rayDir, double distToWall, int x, int side, bool textured)
{
	int sliceHeight; /* height of wall slice to draw */
	int drawStart; /* lowest pixel of wall slice */
	int drawEnd; /* highest pixel of wall slice */
	int tileIndex; /* tile number of current map location */
	double wallX; /* where wall was hit */
	SDL_Point tex; /* X/Y coordinate of pixel of texture */
	uint32_t color; /* color of pixel */
	int width; /* current window width */
	int height; /* current window height */
	int y;

	if (!textured) /* flat maze */
	{
		SDL_GetWindowSize(window, &width, &height);

		/* calculate height of wall slice to draw on screen */
		sliceHeight = (int)(height / distToWall);

		/* calculate lowest and highest pixel of wall slice */
		drawStart = -sliceHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;

		drawEnd = sliceHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;

		/* set wall colors depending if it's N/S or W/E */
		if (side == 0)
			SDL_SetRenderDrawColor(renderer, 0xF7, 0xF7, 0xF7, 0xFF);
		else if (side == 1)
			SDL_SetRenderDrawColor(renderer, 0xDE, 0xDE, 0xDE, 0xFF);

		/* draw pixels of wall slice as a vertical line */
		SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}
	else /* textured maze */
	{
		/* calculate height of wall slice to draw on screen */
		sliceHeight = (int)(SCREEN_HEIGHT / distToWall);

		/* calculate lowest and highest pixel of wall slice */
		drawStart = -sliceHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;

		drawEnd = sliceHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		wallX = 0;
		if (side == 0)
			wallX = rayPos.y + distToWall * rayDir.y;
		else if (side == 1)
			wallX = rayPos.x + distToWall * rayDir.x;

		tileIndex = *((int *)maze + map.x * MAP_WIDTH + map.y) - 1;

		/* floor returns the largest integer value <= to wallX */
		wallX -= floor(wallX);

		/* get X coordinate of texture corresponding to ray hit */
		tex.x = (int)(wallX * (double)TEX_WIDTH);
		if (side == 0 && rayDir.x > 0)
			tex.x = TEX_WIDTH - tex.x - 1;
		if (side == 1 && rayDir.y < 0)
			tex.x = TEX_WIDTH - tex.x - 1;

		for (y = drawStart; y < drawEnd; y++)
		{
			tex.y = ((((y << 1) - SCREEN_HEIGHT + sliceHeight) <<
				  (int)log2(TEX_HEIGHT)) / sliceHeight) >> 1;

			color = tiles[tileIndex][tex.x][tex.y];

			/* change color of the wall depending on wall side */
			if (side == 1)
				color = (color >> 1) & 8355711;

			buffer[y][x] = color;
		}
		/* draw floor and ceiling */
		renderBGTex(map, rayDir, distToWall, wallX, drawEnd, x, side);
	}
}
