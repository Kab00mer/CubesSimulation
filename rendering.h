#ifndef "RENDERING_H"
#define "RENDERING_H"

#include <SDL3/SDL.h>

void startApp(size_t);
void stopApp();

void render(const Cube&);
void renderButtons();
void renderShape(const Cube&);

void userClickedAt(const SDL_FPoint&);

bool userSetNewDimension();
size_t getNewDimension();

#endif
