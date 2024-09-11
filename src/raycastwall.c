#include "../inc/maze.h"

/**
 * drawWalls - Draws walls in maze
 * @renderer: renders walls
 * Return:rendered walls
 */

void drawWalls(SDL_Renderer *renderer)
{
	if (skyTexture) {
		int w, h;
		SDL_GetRendererOutputSize(renderer, &w, &h);
		SDL_Rect dstRect = {0, 0, w, h};  // Full screen
		SDL_RenderCopy(renderer, skyTexture, NULL, &dstRect);
	} else {
		// Fallback to red if skyTexture is not loaded
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
		SDL_RenderClear(renderer);
	}
	int x;

	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		/*Calculate ray position and direction*/
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		/*Map position and direction*/
		int mapX = (int)posX;
		int mapY = (int)posY;
		double sideDistX, sideDistY;
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		int stepX, stepY;
		int hit = 0;
		int side;

		/*Initialize sideDist*/
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		/*Perform DDA*/
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map[mapX][mapY] > 0)
			{
				hit = 1;
			}
		}

		/*Calculate distance and height*/
		if (side == 0)
		{
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		}
		else
		{
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		}
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		/*Calculate draw start and end*/
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

		// Calculate texture coordinates

		double wallX;
		if (side == 0) wallX = posY + perpWallDist * rayDirY;
		else wallX = posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		// Floor position for the floor casting

		int texX = (int)(wallX * (double)TEXTURE_WIDTH);
		if (side == 0 && rayDirX > 0) texX = TEXTURE_WIDTH - texX - 1;
		if (side == 1 && rayDirY < 0) texX = TEXTURE_WIDTH - texX - 1;

		// Draw the wall with texture
		SDL_Rect srcRect = { texX, 0, 1, TEXTURE_HEIGHT };
		SDL_Rect dstRect = { x, drawStart, 1, drawEnd - drawStart };
		SDL_RenderCopy(renderer, wallTexture, &srcRect, &dstRect);

		// Floor casting
		double floorXWall, floorYWall;
		if (side == 0 && rayDirX > 0) {
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		} else if (side == 0 && rayDirX < 0) {
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		} else if (side == 1 && rayDirY > 0) {
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		} else {
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}
		for (int y = drawEnd + 1; y < SCREEN_HEIGHT; y++) {
			double currentDist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);

			double weight = currentDist / perpWallDist;

			double floorX = weight * floorXWall + (1.0 - weight) * posX;
			double floorY = weight * floorYWall + (1.0 - weight) * posY;

			int floorTexX = (int)(floorX * TEXTURE_WIDTH) % TEXTURE_WIDTH;
			int floorTexY = (int)(floorY * TEXTURE_HEIGHT) % TEXTURE_HEIGHT;

			SDL_Rect floorSrcRect = { floorTexX, floorTexY, 1, 1 };
			SDL_Rect floorDstRect = { x, y, 1, 1 };
			SDL_RenderCopy(renderer, floorTexture, &floorSrcRect, &floorDstRect);
		}
	}
}

/**
 * update - Updates map
 * @void: update function
 * Return: updated function
 */

void update(void)
{
}
