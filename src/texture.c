#include "../inc/maze.h"

/**
 * loadTextures - gives walls textures
 * @renderer: pointer to wall render
 * Return: textured walls
 */
SDL_Texture *skyTexture = NULL;
SDL_Texture *floorTexture = NULL;
SDL_Texture *wallTexture = NULL;

void loadTextures(SDL_Renderer *renderer, SDL_Texture **skyTexture, SDL_Texture **floorTexture, SDL_Texture **wallTexture)
{
	/*Load sky texture*/
	*skyTexture = IMG_LoadTexture(renderer, "img/sky.png");
	if (!*skyTexture)
	{
		printf("Failed to load sky texture! SDL_Error: %s\n",
				SDL_GetError());
	}

	*floorTexture = IMG_LoadTexture(renderer, "img/grass.png");
	if (!*floorTexture)
	{
		printf("Failed to load sky texture! SDL_Error: %s\n",
				SDL_GetError());
	}

	*wallTexture = IMG_LoadTexture(renderer, "img/redbrick.png");
	if (!*wallTexture)
	{
		printf("Failed to load sky texture! SDL_Error: %s\n",
				SDL_GetError());
	}

}

