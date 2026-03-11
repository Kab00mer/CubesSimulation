#include "rendering.h"
#include "cubes.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_FRect increaseDimensionButton;
static SDL_FRect decreaseDimensionButton;
static SDL_FRect startRenderingButton;

static bool changeDimension;
static size_t currentDimension;

void startApp(int startingDimension) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Cubes Simulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);	
	
	squareButtonRect.x = 50;
	squareButtonRect.y = 20;
	squareButtonRect.w = 233;
	squareButtonRect.h = 60;
	cubeButtonRect.x = 283;
	cubeButtonRect.y = 20;
	cubeButtonRect.w = 233;
	cubeButtonRect.h = 60;
	hypercubeButtonRect.x = 516;
	hypercubeButtonRect.y = 20;
	hypercubeButtonRect.w = 233;
	hypercubeButtonRect.h = 60;

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
	if (squarePressed) {
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 225);
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	}
	SDL_RenderFillRect(renderer, &squareButtonRect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &squareButtonRect);	
		
	if (cubePressed) {
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 225);
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	}
	SDL_RenderFillRect(renderer, &cubeButtonRect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &cubeButtonRect);	
		
	if (hypercubePressed) {
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 225);
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	}
	SDL_RenderFillRect(renderer, &hypercubeButtonRect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &hypercubeButtonRect);	
			
	SDL_SetRenderScale(renderer, 1.5f, 1.5f);	
	SDL_RenderDebugText(renderer, static_cast<int>(squareButtonRect.x / 1.5) + 15, squareButtonRect.y + 10
		, "Square (2D Cube)");	
	SDL_RenderDebugText(renderer, static_cast<int>(cubeButtonRect.x / 1.5) + 22, cubeButtonRect.y + 10
		, "Cube (3D Cube)");	
	SDL_RenderDebugText(renderer, static_cast<int>(hypercubeButtonRect.x / 1.5) + 4, hypercubeButtonRect.y + 10
		, "Hypercube (4D Cube)");	
	SDL_SetRenderScale(renderer, 1.25f, 1.25f);
	SDL_RenderDebugText(renderer, 210, 80, "Click on the buttons above!");
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void renderShape(const Cube& currentShape, const float cubeSize) {
	std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> currentShape;
	if (squarePressed) {
		currentShape = square.returnLines();
	} else if (cubePressed) {
		currentShape = cube.returnLines();
	} else if (hypercubePressed) {
		currentShape = hypercube.returnLines();
		hypercube.rotate(ROTATE_SPEED);
	}
	for (auto line : currentShape) {
		int oneX = static_cast<int>(line.first.first * cubeSize + WINDOW_WIDTH / 2);
		int oneY = static_cast<int>(line.first.second * cubeSize + WINDOW_WIDTH / 2) - 85;
		int twoX = static_cast<int>(line.second.first * cubeSize + WINDOW_WIDTH / 2);
		int twoY = static_cast<int>(line.second.second * cubeSize + WINDOW_WIDTH / 2) - 85;

		SDL_SetRenderDrawColor(renderer, SDL_rand(256), SDL_rand(256), SDL_rand(256), SDL_ALPHA_OPAQUE);
		SDL_RenderLine(renderer, oneX, oneY, twoX, twoY);
	} 	
}

void userClickedAt(const SDL_FPoint& point) {
	if (SDL_PointInRectFloat(&p, &squareButtonRect) || SDL_PointInRectFloat(&p, &cubeButtonRect) 
		|| SDL_PointInRectFloat(&p, &hypercubeButtonRect)) {

		squarePressed = SDL_PointInRectFloat(&p, &squareButtonRect);
		cubePressed = SDL_PointInRectFloat(&p, &cubeButtonRect);
		hypercubePressed = SDL_PointInRectFloat(&p, &hypercubeButtonRect);
	} 
}

bool userSetNewDimension() {
	return changeDimension;
}

size_t getNewDimension() {
	changeDimension = false;
	return currentDimension;
}
