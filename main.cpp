#include <SDL3/SDL.h>
#include "cubes.h"
#include "rendering.h"

static const float ROTATE_SPEED = 0.0002f;
static const float SHAPE_SIZE = 80.0f;

int main(int argc, char* argv[]) {
	startApp();
	Cube currentCube = Cube(3);

	bool running = true;
	SDL_Event event;
	while (running) {	
		render(currentCube, SHAPE_SIZE);

		currentCube.rotate(ROTATE_SPEED);

		while (SDL_PollEvent(&event)) { 
			if (event.type == SDL_EVENT_QUIT) { 
				running = false;
			} else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				SDL_FPoint point = { event.button.x, event.button.y };
				userClickedAt(point);
			}
		}

		if (userSetNewDimension()) {
			currentCube = Cube(getNewDimension());
		}
	}

	stopApp();
	return 0;
}
