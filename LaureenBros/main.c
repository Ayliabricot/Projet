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


int main() {
	char option[6][40] = { "1. Règles du jeu","2. Choisir difficulté","3. Nouvelle partie","4. Continuer partie","5. Accéder au tableau des scores","6. Quitter le jeu" };

	Ecran* ecran = definirEcran();
	int touche = 0;
	int* choix = malloc(sizeof(int));
	if (choix == NULL) {
		printf("Erreur d'allocation mémoire\n");
		return 1;
	}
	*choix = 0;


	afficherMenu(ecran, touche, choix,option);

	while (1) {
		if (_kbhit()) {
			touche = _getch();


			system("cls");
			afficherMenu(ecran, touche, choix,option);
		}


	}
	free(choix);
	choix = NULL;
	return 0;

}






//mettre des while(valeur= ...)  ca va dans un menu










