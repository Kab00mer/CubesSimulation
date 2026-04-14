#include "rendering.h"
#include "string"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_FRect increaseDimensionButton;
static SDL_FRect decreaseDimensionButton;
static SDL_FRect startRenderingButton;
static SDL_FRect cycleModesButton;
static SDL_FRect speedUpButton;
static SDL_FRect speedDownButton;

static bool changeDimension;
static size_t currentDimension;

static RenderingMode mode;

static double rotationSpeed;
static const double SPEED_CHANGE = 0.00005;

static bool increasePressed = false;
static bool decreasePressed = false;
static bool cyclePressed = false;
static bool upPressed = false;
static bool downPressed = false;


void startApp(size_t startingDimension, RenderingMode startingMode) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Cubes Simulator", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	
	decreaseDimensionButton.x = 50;
	decreaseDimensionButton.y = 20;
	decreaseDimensionButton.w = 133;
	decreaseDimensionButton.h = 60;

	startRenderingButton.x = 203;
	startRenderingButton.y = 20;
	startRenderingButton.w = 393;
	startRenderingButton.h = 60;

	increaseDimensionButton.x = 616;
	increaseDimensionButton.y = 20;
	increaseDimensionButton.w = 133;
	increaseDimensionButton.h = 60;

	cycleModesButton.x = 616;
	cycleModesButton.y = 100;
	cycleModesButton.w = 133;
	cycleModesButton.h = 60;

	speedDownButton.x = 20;
	speedDownButton.y = 100;
	speedDownButton.w = 93;
	speedDownButton.h = 60;

	speedUpButton.x = 120;
	speedUpButton.y = 100;
	speedUpButton.w = 93;
	speedUpButton.h = 60;

	currentDimension = startingDimension;

	mode = startingMode;

	rotationSpeed = 0.0002;
}

void stopApp() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); 
}

void render(const Cube& currentShape, const double cubeSize) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
		
	renderButtons();
	renderShape(currentShape, cubeSize);

	SDL_RenderPresent(renderer);
}

void renderButtons() {
	if (increasePressed) {
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 50, 0, 225);
	}
	SDL_RenderFillRect(renderer, &increaseDimensionButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &increaseDimensionButton);	
		
	SDL_SetRenderDrawColor(renderer, 0, 0, 50, 225);
	SDL_RenderFillRect(renderer, &startRenderingButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &startRenderingButton);	
		
	if (decreasePressed) {
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
	} else {
		SDL_SetRenderDrawColor(renderer, 50, 0, 0, 225);
	}
	SDL_RenderFillRect(renderer, &decreaseDimensionButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &decreaseDimensionButton);	

	if (cyclePressed) {
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
	} else {
		SDL_SetRenderDrawColor(renderer, 70, 0, 70, 225);
	}
	SDL_RenderFillRect(renderer, &cycleModesButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &cycleModesButton);	

	if (upPressed) {
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
	} else {
		SDL_SetRenderDrawColor(renderer, 70, 70, 0, 225);
	}
	SDL_RenderFillRect(renderer, &speedUpButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &speedUpButton);	
	
	if (downPressed) {
		SDL_SetRenderDrawColor(renderer, 180, 180, 180, 180);
	} else {
		SDL_SetRenderDrawColor(renderer, 100, 50, 0, 225);
	}
	SDL_RenderFillRect(renderer, &speedDownButton);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderRect(renderer, &speedDownButton);	
			
	SDL_SetRenderScale(renderer, 1.5f, 1.5f);	
	SDL_RenderDebugText(renderer, static_cast<int>(increaseDimensionButton.x / 1.5) + 30, 
		increaseDimensionButton.y + 10, "+1D");	
	SDL_RenderDebugText(renderer, static_cast<int>(startRenderingButton.x / 1.5) + 45, 
		startRenderingButton.y + 10, "Current Dimension:");	
	SDL_RenderDebugText(renderer, static_cast<int>(decreaseDimensionButton.x / 1.5) + 30, 
		decreaseDimensionButton.y + 10, "-1D");	
	SDL_RenderDebugText(renderer, static_cast<int>(cycleModesButton.x / 1.5 + 5), 
		cycleModesButton.y - 16, "Cycle Mode");	
	SDL_RenderDebugText(renderer, static_cast<int>(speedUpButton.x / 1.5 + 5) + 2, 
		speedUpButton.y - 16, "+Speed");	
	SDL_RenderDebugText(renderer, static_cast<int>(speedDownButton.x / 1.5 + 5) + 2, 
		speedDownButton.y - 16, "-Speed");	


	SDL_SetRenderScale(renderer, 2.5f, 2.5f);	
	SDL_RenderDebugText(renderer, static_cast<int>(startRenderingButton.x / 1.5) + 65, 
		startRenderingButton.y - 4, std::to_string(currentDimension).c_str());	


	SDL_SetRenderScale(renderer, 1.25f, 1.25f);
	SDL_RenderDebugText(renderer, 235, 80, "Click on the buttons!");
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void renderShape(const Cube& currentShape, const double cubeSize) {
	std::vector<Line> lines = currentShape.returnLines();

	size_t lineCount = lines.size();

	for (size_t i = 0; i < lineCount; ++i) {
		int oneX = static_cast<int>(lines[i].x1 * cubeSize + WINDOW_WIDTH / 2);
		int oneY = static_cast<int>(lines[i].y1 * cubeSize + WINDOW_WIDTH / 2) - 45;
		int twoX = static_cast<int>(lines[i].x2 * cubeSize + WINDOW_WIDTH / 2);
		int twoY = static_cast<int>(lines[i].y2 * cubeSize + WINDOW_WIDTH / 2) - 45;

		int red, green, blue;
		switch (mode) {
			case RenderingMode::Rainbow : 
				red = SDL_rand(256);
				green = SDL_rand(256);
				blue = SDL_rand(256);
				break;
			case RenderingMode::RGB :
				switch (i % 3) {
					case 0:
						red = 255;
						blue = 0;
						green = 0;
						break;
					case 1:
						red = 0;
						blue = 255;
						green = 0;
						break;
					case 2: 
						red = 0;
						blue = 0;
						green = 255;	
				}
				break;
			case RenderingMode::White :
				red = 255;
				green = 255;
				blue = 255;
		}

		SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
		SDL_RenderLine(renderer, oneX, oneY, twoX, twoY);
	} 	
}

void userClickedAt(const SDL_FPoint& p) {
	if (SDL_PointInRectFloat(&p, &increaseDimensionButton)) {
		++currentDimension;
		increasePressed = true;
	} else if (SDL_PointInRectFloat(&p, &decreaseDimensionButton)) {
		if (currentDimension != 0) {
			--currentDimension;
			decreasePressed = true;
		}

	} else if (SDL_PointInRectFloat(&p, &cycleModesButton)) {
		switch (mode) {
			case RenderingMode::Rainbow : 
				mode = RenderingMode::RGB;
				break;
			case RenderingMode::RGB :
				mode = RenderingMode::White;
				break;
			case RenderingMode::White :
				mode = RenderingMode::Rainbow;
		}
		cyclePressed = true;

	} else if (SDL_PointInRectFloat(&p, &speedUpButton)) {
		rotationSpeed += SPEED_CHANGE;
		upPressed = true;

	} else if (SDL_PointInRectFloat(&p, &speedDownButton)) {
		if (rotationSpeed - SPEED_CHANGE > 0) {
			rotationSpeed -= SPEED_CHANGE;	
			downPressed = true;
		} else {
			rotationSpeed = 0;
		}
	}
}

void userReleased() {
	increasePressed = false;
	decreasePressed = false;
	cyclePressed = false;
	upPressed = false;
	downPressed = false;
}

size_t getUserDimension() { return currentDimension; }

double getSpeed() { return rotationSpeed; }


