#ifndef RENDERING_H
#define RENDERING_H

#include <SDL3/SDL.h>
#include "cube.h"

enum RenderingMode {
	Rainbow,
	RGB,
	White
};

void startApp(size_t, RenderingMode);
void stopApp();

void render(const Cube&, const double);
void renderButtons();
void renderShape(const Cube&, const double);

void userClickedAt(const SDL_FPoint&);
void userReleased();

size_t getUserDimension();
double getSpeed();

#endif
