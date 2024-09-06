#include "../inc/maze.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
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
	int maze[MAP_WIDTH * MAP_HEIGHT] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    		1, 0, 1, 1, 1, 1, 1, 0, 0, 1,
   		1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
    		1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
    		1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
    		1, 0, 1, 1, 1, 0, 1, 0, 0, 1,
    		1, 0, 0, 0, 1, 0, 1, 0, 0, 1,
    		1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
    		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

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

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        		SDL_RenderClear(gRenderer);
	    // Call raycaster to draw walls
            		raycaster(maze, false); // Change false to true if you want textures

            // Update screen
            		SDL_RenderPresent(gRenderer);
		}
	}

	/* Quit SDL subsystems */
	SDL_DestroyRenderer(gRenderer);
    	SDL_DestroyWindow(gWindow);
    	gRenderer = NULL;
    	gWindow = NULL;
	SDL_Quit();

	return (0); /* Parentheses required */
	}
}
