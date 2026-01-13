#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

typedef struct{

	SDL_Window = 

}

bool init_SDL(void){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
		SDL_Log("SDL Initialization Failed: %s", SDL_GetError());
		return false;
	}

	return true;
}

void chip8_cleanup(void){

	SDL_Quit(); // Exits SDL subsystem

}

int main(int argc, char **argv){

	(void)argc;
	(void)argv;

	SDL_WindowFlags flags =
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE;

	SDL_Window *window;                    // Declare a pointer
	bool done = false;

	// Initialize SDL3
	if(init_SDL() == false){
		return EXIT_FAILURE;
	}	

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
			"CHIP-8",                  // window title
			840,                               // width, in pixels
			480,                               // height, in pixels
			flags                  // flags - see below
			);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	while (!done) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
		}

		// Do game logic, present a frame, etc.
	}

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	chip8_cleanup();

	return EXIT_SUCCESS;

}
