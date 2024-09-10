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
    double moveSpeed = 0.05;  // Speed of movement
    double rotSpeed = 0.03;   // Speed of rotation
    // Move forward (W)
    if (state[SDL_SCANCODE_W]) {
		double newX = posX + dirX * moveSpeed;
		double newY = posY + dirY * moveSpeed;
        
        // Check for collision with walls
        if (map[(int)newX][(int)posY] == 0) posX = newX;
        if (map[(int)posX][(int)newY] == 0) posY = newY;
	}

	// Move backward (S)
	if (state[SDL_SCANCODE_S]) {
		double newX = posX - dirX * moveSpeed;
        double newY = posY - dirY * moveSpeed;

        // Check for collision with walls
        if (map[(int)newX][(int)posY] == 0) posX = newX;
        if (map[(int)posX][(int)newY] == 0) posY = newY;
	}

	// Move left (A)
	if (state[SDL_SCANCODE_A]) {
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}

	// Move right (D)
	if (state[SDL_SCANCODE_D]) {
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
}
