#include <SDL3/SDL.h>
#include "cube.h"
#include "rendering.h"

static const double SHAPE_SIZE = 80.0f;
static const size_t STARTING_DIMENSION = 3;

int main(int argc, char* argv[]) {
	startApp(STARTING_DIMENSION, RenderingMode::RGB);
	Cube currentCube = Cube(STARTING_DIMENSION);

	bool running = true;
	SDL_Event event;
	while (running) {	
		render(currentCube, SHAPE_SIZE);

		currentCube.rotate(getSpeed());

		while (SDL_PollEvent(&event)) { 
			if (event.type == SDL_EVENT_QUIT) { 
				running = false;
			} else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				SDL_FPoint point = { event.button.x, event.button.y };
				userClickedAt(point);
			} else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				userReleased();
			}
		}

		if (getUserDimension() != currentCube.getDimension()) {
			currentCube = Cube(getUserDimension());
		}
	}

	stopApp();
	return 0;
}
