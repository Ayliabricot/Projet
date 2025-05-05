#include "musique.h"
#include <stdio.h>

Mix_Music* musique = NULL;

int demarrerMusique(const char* cheminMusique) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Erreur SDL_mixer : %s\n", Mix_GetError());
        return -1;
    }

    musique = Mix_LoadMUS(cheminMusique);
    if (!musique) {
        fprintf(stderr, "Erreur chargement musique : %s\n", Mix_GetError());
        return -1;
    }

    Mix_PlayMusic(musique, -1); // -1 = boucle infinie
    return 0;
}

void arreterMusique() {
    if (musique) {
        Mix_FreeMusic(musique);
        musique = NULL;
    }
    Mix_CloseAudio();
}
