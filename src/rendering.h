#ifndef RENDERING_H
#define RENDERING_H

#include <SDL3/SDL.h>
#include "cube.h"

void startApp(size_t);
void stopApp();

void render(const Cube&, const float);
void renderButtons();
void renderShape(const Cube&, const float);

void userClickedAt(const SDL_FPoint&);

bool userSetNewDimension();
size_t getNewDimension();

#endif
