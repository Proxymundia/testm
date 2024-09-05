#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Function prototypes */
bool init(void);
int main(int argc, char *args[]);

/*
 * init- Initializes SDL and creates a window
 * Return:true if initialization succeeds, false otherwise.
 */
bool init(void)
{
	bool success = true; /* Initialization flag */

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		/* Create window */
		SDL_Window *gWindow = SDL_CreateWindow(
				"The Maze",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN
				);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			/* Get window surface */
			SDL_Surface *gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return (success); /* Parentheses required */
}

/*
 * main - Entry point for the program.
 * @argc: Argument count.
 * @args: Argument vector.
 * Return: 0 on success.
 */
int main(int argc, char *args[])
{
	bool quit = false; /* Flag to indicate if the window should close */
	SDL_Event e; /* Event handler */

	/* Start up SDL and create window */
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		/* Event loop */
		while (!quit)
		{
			/* Handle events on the queue */
			while (SDL_PollEvent(&e) != 0)
			{
				/* User requests quit */
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			/* You can add rendering code here if needed */
		}
	}

	/* Quit SDL subsystems */
	SDL_Quit();

	return (0); /* Parentheses required */
}
