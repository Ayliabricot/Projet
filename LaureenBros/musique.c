#include "musique.h"
#include <stdio.h>

Mix_Music* musique = NULL;

int initialiserAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL_Init (audio) : %s\n", SDL_GetError());
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur Mix_OpenAudio : %s\n", Mix_GetError());
        return 0;
    }

    return 1;
}

void jouerMusique(const char* chemin) {
    musique = Mix_LoadMUS(chemin);
    if (!musique) {
        printf("Erreur Mix_LoadMUS : %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(musique, -1);  // -1 = boucle infinie
}

void arreterMusique() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}

void libererAudio() {
    if (musique) {
        Mix_FreeMusic(musique);
        musique = NULL;
    }
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
