#include "../inc/maze.h"

void drawWalls(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer,135, 206, 250, 255); 
	SDL_RenderClear(renderer);
	int x;
    for (x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // Map position and direction
        int mapX = (int)posX;
        int mapY = (int)posY;
        double sideDistX, sideDistY;
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;
        int stepX, stepY;
        int hit = 0;
        int side;

        // Initialize sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapX][mapY] > 0) {
                hit = 1;
            }
        }

        // Calculate distance and height
        if (side == 0) {
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        } else {
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
        }
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        // Calculate draw start and end
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        // Draw the wall
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Wall color (red)
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }
}

void update(void) {
}
