#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include "placementTexte.h"
#include <time.h>
#include "quitterJeu.h"
#include "gererParties.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "jeu.h"

Partie* currentPartie = NULL;

int main(int argc, char* argv[]) {

	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "Erreur SDL_mixer : %s\n", Mix_GetError());
		return 1;
	}

	Mix_Music* musique = Mix_LoadMUS("music/noCopr.mp3");
	if (!musique) {
		fprintf(stderr, "Erreur chargement musique : %s\n", Mix_GetError());
		return 1;
	}

	Mix_PlayMusic(musique, -1);
	


	Partie** tableau = creerTableau();

	char option[5][40] = { " 1. Règles du jeu "," 2. Nouvelle partie "," 3. Continuer partie "," 4. Accéder au tableau des scores "," 5. Quitter le jeu " };

	Ecran* ecran = definirEcran();
	int touche = 0;
	int* nbParties = malloc(sizeof(int));
	int* choix = malloc(sizeof(int));
	if (choix == NULL || nbParties==NULL) {
		printf("Erreur d'allocation mémoire\n");
		return 1;
	}
	cacherCurseur();
	*nbParties = 0;
	*choix = -1;

	lancer_ecran(choix, option, tableau, nbParties,argc,argv);

	for (int i = 0; i < *nbParties; i++) {
		free(tableau[i]);
		tableau[i] = NULL;
	}
	free(tableau);
	tableau = NULL;
	free(choix);
	choix = NULL;

	afficherCurseur();
	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	return 0;
}














