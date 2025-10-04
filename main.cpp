#include <SDL3/SDL.h>
#include "dimensional_shapes.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_CreateWindowAndRenderer("Cube Simulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	
	SDL_RenderPresent(renderer);
	
	bool running = true;
	SDL_Event event;
	while (running) {	
		
		//Rotate Hypercube
		//Project 

	 	while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
	}


	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
