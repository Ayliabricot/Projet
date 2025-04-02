#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL2App;

int initSDL2(SDL2App *app, const char *title);

void cleanupSDL2(SDL2App *app);
