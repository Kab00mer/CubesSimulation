#include <SDL3/SDL.h>
#include <iostream>
#include "cubes.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float SHAPE_SIZE = 80.0f;
const float ROTATE_SPEED = 0.0002f;

static SDL_FRect squareButtonRect;
static SDL_FRect cubeButtonRect;
static SDL_FRect hypercubeButtonRect;
static bool squarePressed = true;
static bool cubePressed = false;
static bool hypercubePressed = false;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window;
	SDL_Renderer* renderer;
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

	Square square = Square();
	Cube cube = Cube();
	Hypercube hypercube = Hypercube();

	bool running = true;
	SDL_Event event;
	while (running) {	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		
		//Cube rendering
		std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> currentShape;
		if (squarePressed) {
			currentShape = square.returnLines();
			square.rotate(ROTATE_SPEED);
		} else if (cubePressed) {
			currentShape = cube.returnLines();
			cube.rotate(ROTATE_SPEED);
		} else if (hypercubePressed) {
			currentShape = hypercube.returnLines();
			hypercube.rotate(ROTATE_SPEED);
		}
		for (auto line : currentShape) {
			int oneX = static_cast<int>(line.first.first * SHAPE_SIZE + WINDOW_WIDTH / 2);
			int oneY = static_cast<int>(line.first.second * SHAPE_SIZE + WINDOW_WIDTH / 2) - 85;
			int twoX = static_cast<int>(line.second.first * SHAPE_SIZE + WINDOW_WIDTH / 2);
			int twoY = static_cast<int>(line.second.second * SHAPE_SIZE + WINDOW_WIDTH / 2) - 85;

			SDL_SetRenderDrawColor(renderer, SDL_rand(256), SDL_rand(256), SDL_rand(256), SDL_ALPHA_OPAQUE);
			SDL_RenderLine(renderer, oneX, oneY, twoX, twoY);
		} 	

		//UI for buttons
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
		SDL_RenderDebugText(renderer, static_cast<int>(squareButtonRect.x / 1.5) + 15, squareButtonRect.y + 10, "Square (2D Cube)");	
		SDL_RenderDebugText(renderer, static_cast<int>(cubeButtonRect.x / 1.5) + 22, cubeButtonRect.y + 10, "Cube (3D Cube)");	
		SDL_RenderDebugText(renderer, static_cast<int>(hypercubeButtonRect.x / 1.5) + 4, hypercubeButtonRect.y + 10, "Hypercube (4D Cube)");	
		SDL_SetRenderScale(renderer, 1.25f, 1.25f);
		SDL_RenderDebugText(renderer, 210, 80, "Click on the buttons above!");
		SDL_SetRenderScale(renderer, 1.0f, 1.0f);

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) { 
			if (event.type == SDL_EVENT_QUIT) { 
				running = false;
			} else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				SDL_FPoint p = { event.button.x, event.button.y };
				if (SDL_PointInRectFloat(&p, &squareButtonRect) || SDL_PointInRectFloat(&p, &cubeButtonRect) || SDL_PointInRectFloat(&p, &hypercubeButtonRect)) {
					squarePressed = SDL_PointInRectFloat(&p, &squareButtonRect);
					cubePressed = SDL_PointInRectFloat(&p, &cubeButtonRect);
					hypercubePressed = SDL_PointInRectFloat(&p, &hypercubeButtonRect);
				}
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit(); return 0;
}
