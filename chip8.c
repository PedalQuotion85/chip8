#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

typedef struct{

	SDL_Window *window; // Window pointer

}sdl_t;

typedef struct{
	// NOTE: Change var type if there's issues between 32/64 systems.
	int window_height;
	int window_width;
	SDL_WindowFlags flags;
}config_t;

bool init_SDL(sdl_t *sdl, const config_t *config){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == false) {
		SDL_Log("SDL Initialization Failed: %s", SDL_GetError());
		return false;
	}

	// Create an application window with the following settings:
	sdl->window = SDL_CreateWindow(
			"CHIP-8",			// window title
			config->window_width,           // width, in pixels
			config->window_height,          // height, in pixels
			config->flags                  	// flags - see below
			);

	// Check that the window was successfully created
	if (sdl->window == NULL) {
		// In the case that the window could not be made...
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return false;
	}


	return true;
}

void chip8_cleanup(sdl_t *sdl){
	SDL_DestroyWindow(sdl->window);
	SDL_Quit(); // Exits SDL subsystem

}

bool init_config(config_t *config){

	config->window_height = 480;
	config->window_width = 840;	
	config->flags = 
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE;

	return true;
}

void app(void){

	return;

}

int main(int argc, char **argv){
	
	// TODO: Add in a config override through command arg later.
	(void)argc;
	(void)argv;
	
	// Initialize Config
	config_t config;
	if(init_config(&config) == false){
		exit(EXIT_FAILURE);
	}
	
	// Initialize SDL3
	sdl_t sdl = {.window = NULL};
	if(init_SDL(&sdl, &config) == false){
		exit(EXIT_FAILURE);
	}	

	bool done = false;

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

	// Clean up
	chip8_cleanup(&sdl);

	return EXIT_SUCCESS;

}
