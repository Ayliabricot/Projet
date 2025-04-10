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



int main() {

	


	Partie** tableau = creerTableau();

	char option[5][40] = { "1. Règles du jeu","2. Nouvelle partie","3. Continuer partie","4. Accéder au tableau des scores","5. Quitter le jeu" };

	Ecran* ecran = definirEcran();
	int touche = 0;
	int* nbParties = malloc(sizeof(int));
	int* choix = malloc(sizeof(int));
	if (choix == NULL || nbParties==NULL) {
		printf("Erreur d'allocation mémoire\n");
		return 1;
	}
	*nbParties = 0;
	*choix = 0;

	afficherMenu(ecran, touche, choix,option,tableau,nbParties);

	while (1) {
		if (_kbhit()) {
			touche = _getch();


			system("cls");
			afficherMenu(ecran, touche, choix,option,tableau,nbParties);
		}


	}

	for (int i = 0; i < *nbParties; i++) {
		free(tableau[i]);
		tableau[i] == NULL;
	}
	free(tableau);
	tableau = NULL;
	free(choix);
	choix = NULL;
	return 0;

}






//mettre des while(valeur= ...)  ca va dans un menu










