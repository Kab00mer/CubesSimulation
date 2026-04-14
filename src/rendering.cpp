#include "rendering.h"
#include "string"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_FRect increaseDimensionButton;
static SDL_FRect decreaseDimensionButton;
static SDL_FRect startRenderingButton;

static bool changeDimension;
static size_t currentDimension;

void startApp(size_t startingDimension) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Cubes Simulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	
	increaseDimensionButton.x = 50;
	increaseDimensionButton.y = 20;
	increaseDimensionButton.w = 133;
	increaseDimensionButton.h = 60;

	startRenderingButton.x = 203;
	startRenderingButton.y = 20;
	startRenderingButton.w = 393;
	startRenderingButton.h = 60;

	decreaseDimensionButton.x = 616;
	decreaseDimensionButton.y = 20;
	decreaseDimensionButton.w = 133;
	decreaseDimensionButton.h = 60;

	changeDimension = false;
	currentDimension = startingDimension;
}

void stopApp() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); 
}

void render(const Cube& currentShape, const float cubeSize) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
		
	renderButtons();
	renderShape(currentShape, cubeSize);

	SDL_RenderPresent(renderer);
}

void renderButtons() {
	SDL_SetRenderDrawColor(renderer, 0, 50, 0, 225);
	SDL_RenderFillRect(renderer, &increaseDimensionButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &increaseDimensionButton);	
		
	SDL_SetRenderDrawColor(renderer, 0, 0, 50, 225);
	SDL_RenderFillRect(renderer, &startRenderingButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &startRenderingButton);	
		
	SDL_SetRenderDrawColor(renderer, 50, 0, 0, 225);
	SDL_RenderFillRect(renderer, &decreaseDimensionButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &decreaseDimensionButton);	
			
	SDL_SetRenderScale(renderer, 1.5f, 1.5f);	
	SDL_RenderDebugText(renderer, static_cast<int>(increaseDimensionButton.x / 1.5) + 30, 
		increaseDimensionButton.y + 10, "+1D");	
	SDL_RenderDebugText(renderer, static_cast<int>(startRenderingButton.x / 1.5) + 45, 
		startRenderingButton.y + 10, "Current Dimension:");	
	SDL_RenderDebugText(renderer, static_cast<int>(decreaseDimensionButton.x / 1.5) + 30, 
		decreaseDimensionButton.y + 10, "-1D");	

	SDL_SetRenderScale(renderer, 2.5f, 2.5f);	
	SDL_RenderDebugText(renderer, static_cast<int>(startRenderingButton.x / 1.5) + 65, 
		startRenderingButton.y - 4, std::to_string(currentDimension).c_str());	

	SDL_SetRenderScale(renderer, 1.25f, 1.25f);
	SDL_RenderDebugText(renderer, 210, 80, "Click on the buttons above!");
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void renderShape(const Cube& currentShape, const float cubeSize) {
	std::vector<Line> lines = currentShape.returnLines();

	for (Line l : lines) {
		int oneX = static_cast<int>(l.x1 * cubeSize + WINDOW_WIDTH / 2);
		int oneY = static_cast<int>(l.y1 * cubeSize + WINDOW_WIDTH / 2) - 85;
		int twoX = static_cast<int>(l.x2 * cubeSize + WINDOW_WIDTH / 2);
		int twoY = static_cast<int>(l.y2 * cubeSize + WINDOW_WIDTH / 2) - 85;

		SDL_SetRenderDrawColor(renderer, SDL_rand(256), SDL_rand(256), SDL_rand(256), SDL_ALPHA_OPAQUE);
		SDL_RenderLine(renderer, oneX, oneY, twoX, twoY);
	} 	
}

void userClickedAt(const SDL_FPoint& p) {
	if (SDL_PointInRectFloat(&p, &increaseDimensionButton) || SDL_PointInRectFloat(&p, &startRenderingButton) 
		|| SDL_PointInRectFloat(&p, &decreaseDimensionButton)) {

		bool decrease = SDL_PointInRectFloat(&p, &increaseDimensionButton);
		//update = SDL_PointInRectFloat(&p, &cubeButtonRect);
		bool increase = SDL_PointInRectFloat(&p, &decreaseDimensionButton);

		if (decrease || increase) {
			changeDimension = true;
		}
	} 
}

bool userSetNewDimension() {
	return changeDimension;
}

size_t getNewDimension() {
	changeDimension = false;
	return currentDimension;
}
