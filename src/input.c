#include "../inc/maze.h"

void rotateCamera(double angle) {
    // Rotate direction vector
    double oldDirX = dirX;
    dirX = dirX * cos(angle) - dirY * sin(angle);
    dirY = oldDirX * sin(angle) + dirY * cos(angle);

    // Rotate camera plane
    double oldPlaneX = planeX;
    planeX = planeX * cos(angle) - planeY * sin(angle);
    planeY = oldPlaneX * sin(angle) + planeY * cos(angle);
}

void handleInput(void) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    // move camera with left key
    if (state[SDL_SCANCODE_LEFT]) {
	    rotateCamera(0.05);
    }
    // move camera with right key
    if (state[SDL_SCANCODE_RIGHT]) {
	    rotateCamera(-0.05);
    }
}
