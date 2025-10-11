#include <SDL3/SDL.h>
#include <iostream>
#include "cubes.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float SHAPE_SIZE = 80.0f;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_CreateWindowAndRenderer("Cubes Simulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	Hypercube currentShape = Hypercube();	

	bool running = true;
	SDL_Event event;
	while (running) {	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		for (auto line : currentShape.returnLines()) { //function returns vector<pair<pair<float, float>, pair<float, float>>>
			int oneX = static_cast<int>(line.first.first * SHAPE_SIZE + WINDOW_WIDTH / 2);
			int oneY = static_cast<int>(line.first.second * SHAPE_SIZE + WINDOW_WIDTH / 2);
			int twoX = static_cast<int>(line.second.first * SHAPE_SIZE + WINDOW_WIDTH / 2);
			int twoY = static_cast<int>(line.second.second * SHAPE_SIZE + WINDOW_WIDTH / 2);

			//std::cout << "line:" << oneX << ", " << oneY << ", " << twoX << ", " << twoY << '\n';

			SDL_SetRenderDrawColor(renderer, SDL_rand(256), SDL_rand(256), SDL_rand(256), SDL_ALPHA_OPAQUE);
			SDL_RenderLine(renderer, oneX, oneY, twoX, twoY);
		}
		
		currentShape.rotate(0.0001);

		SDL_RenderPresent(renderer);			

		//add logic for switching shapes

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
