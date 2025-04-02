#ifndef MUSIQUE_H
#define MUSIQUE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int initialiserAudio(void);
void jouerMusique(const char* chemin);
void arreterMusique(void);
void libererAudio(void);

#endif
