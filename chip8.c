#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <SDL3/SDL.h>

typedef struct{

	SDL_Window *window; // Window pointer
	SDL_Renderer *renderer;

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
			config->flags                  	// flags - see init_config function
			);

	// Check that the window was successfully created
	if (sdl->window == NULL) {
		// In the case that the window could not be made...
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return false;
	}

	sdl->renderer = SDL_CreateRenderer(sdl->window, NULL);
	if(sdl->renderer == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void chip8_cleanup(sdl_t *sdl){
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit(); // Exits SDL subsystem

}

bool init_config(config_t *config, int argc, char **argv){

	bool height_flag = false;
	bool width_flag = false;

	// If something somehow goes wrong
	if(!config){
		printf("ERROR: Config Initialization Failure!");
		return false;
	}

	config->flags = 
		SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_ALWAYS_ON_TOP;

	// If there are no additional args, we assume default config
	if(argc == 1){
		config->window_height = 480;
		config->window_width = 840;	
		return true;
	}

	if(argc != 5){
		printf("Invalid Arguments!\n"
				"Expected two arguments (any order): -h <height> -w <width>\n"
				"Flags:\n"
				"   -h   Set height of the display window\n"
				"   -w   Set width of the display window\n"
		      );
		return false;
	}

	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], "-h") == 0){
			config->window_height = atoi(argv[i + 1]);
			height_flag = true;
		}
		if(strcmp(argv[i], "-w") == 0){
			config->window_width = atoi(argv[i + 1]);
			width_flag = true;
		}
	}

	// Ensures that no double of a flag is entered
	if(height_flag == false || width_flag == false){
		printf("Invalid Arguments!\n"
				"Expected two arguments (any order): -h <height> -w <width>\n"
				"Flags:\n"
				"   -h   Set height of the display window\n"
				"   -w   Set width of the display window\n"
		      );
		return false;
	}

	return true;
}

void app(void){

	return;

}

int main(int argc, char **argv){

	// Initialize Config
	config_t config;
	if(init_config(&config, argc, argv) == false){
		exit(EXIT_FAILURE);
	}

	// Initialize SDL3
	sdl_t sdl = {.window = NULL};
	if(init_SDL(&sdl, &config) == false){
		exit(EXIT_FAILURE);
	}	

	SDL_SetRenderDrawColor(sdl.renderer,r,g,b,a)
	SDL_RenderClear(sdl.renderer);

	bool done = false;

	while (!done) {
		SDL_Event event;
		SDL_zero(event);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
			// Check if a key was pressed
			if (event.type == SDL_EVENT_KEY_DOWN) {
				// Check if the key pressed is the "Return" (Enter) key
				if (event.key.scancode == SDL_SCANCODE_RETURN) {
					done = true;  // Close the app if "Return" key is pressed
				}
			}
		}

	}

	// Clean up
	chip8_cleanup(&sdl);

	return EXIT_SUCCESS;
}
