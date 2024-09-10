#include "../inc/maze.h"

/**
 * SDL - intializes SDL, creates a window and renderer
 * Return: true in successfull otherwise false
 */
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool SDL(void)
{
	/*Initialise SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
		return (false);
	}
	else
		/*Create a window*/
		window = SDL_CreateWindow("The Maze", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Could not create window SDL_Error: %s\n", SDL_GetError());
		return (false);
	}
	else
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
	{
		printf("Could not create renderer SDL Error: %s\n", SDL_GetError());
		return (false);
	}
	return (true);
}

/**
 * main - The maze entry point
 */

int main(void)
{
	if (!SDL())
	{
		printf("Initialisation failed\n");
		return (1);
	}
	
	bool quit = false;
	SDL_Event e;
	
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)

		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
	/*Add functions*/
	SDL_Delay(16);
	closeSDL();
	return (0);
}

/**
 * closeSDL - clearup memory
 */

void closeSDL(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

