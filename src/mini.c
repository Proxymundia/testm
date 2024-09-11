#include "../inc/maze.h"

/**
 * miniMap - displays the mini map
 * @renderer: pointer to render
 * Return: minimap
*/

void miniMap(SDL_Renderer *renderer)
{
	bool showMap = true;

	if (!showMap)
		return;
	/*Minimap settings*/
	int mapScale = 10; /*Scale down the map for the minimap*/
	int offsetX = 10; /*Offset from the left edge of the screen*/
	int offsetY = 10; /*Offset from the top edge of the screen*/

	/*Draw the maze layout*/
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			SDL_Rect rect = { offsetX + x * mapScale, offsetY +
				y * mapScale, mapScale, mapScale };
			if (map[x][y] > 0)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /*Wall color (black)*/
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				/*Empty space (white)*/
			}
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	/*Draw the player's position*/
	SDL_Rect playerRect = { offsetX + posX * mapScale - 2,
		offsetY + posY * mapScale - 2, 4, 4 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /*set player color black*/
	SDL_RenderFillRect(renderer, &playerRect);
	/*Draw the player's line of sight*/
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /*Line of sight (red)*/
	SDL_RenderDrawLine(renderer,
			offsetX + posX * mapScale,
			offsetY + posY * mapScale,
			offsetX + (posX + dirX * 5) * mapScale,
			offsetY + (posY + dirY * 5) * mapScale);
}
