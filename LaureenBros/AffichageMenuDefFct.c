
#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "placementTexte.h"
#include "affichageMenu.h"



void afficherMenu(Ecran* ecran, int touche, int* choix) {
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);


	

	if (touche == 115 || touche == 122) {
		definirChoix(touche, choix);
		
	}

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 1, "*");

	}
	afficherTexte(ecran->largeur / 2 - 29 / 2, 3, "*****  LAUREEN   BROS  *****");
	

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 5, "*");
	}

	char option[6][40] = { "1. Entre le pseudo du joueur","2. Choisir difficulté","3. Nouvelle partie","4. Continuer partie","5. Accéder au tableau des scores","6. Quitter le jeu" };
	for (int i = 0; i < 6; i++) {
		if (*choix == i) {
			afficherTexteHighlight(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i, option[i]);
			
		}
		else {
			afficherTexte(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i, option[i]);
		
		}
	}

	afficherTexte(ecran->largeur / 2 - 22 / 2, ecran->hauteur - 5, "Choisissez une option");
	afficherTexte(ecran->largeur / 2 - 22 / 2, ecran->hauteur - 3,"(press to adjust)");

	
	

	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());

}

void definirChoix(int touche, int* choix) {
	if (touche == 122 && *choix != 0) {
		*choix = *choix - 1;
	}
	else if (touche == 122 && *choix == 0) {
		*choix = 5;
	}
	else if (touche == 115 && *choix != 5) {
		*choix = *choix + 1;
	}
	else if (touche == 115 && *choix == 5) {
		*choix = 0;
	}
}

/*
main pour affciher le menu

Ecran* ecran = definirEcran();
int touche = 0;
int* choix = malloc(sizeof(int));
if (choix == NULL) {
	printf("Erreur d'allocation mémoire\n");
	return 1;
}
*choix = 2;


afficherMenu(ecran, touche, choix);

while (1) {
	if (_kbhit()) {
		touche = _getch();


		system("cls");
		afficherMenu(ecran, touche, choix);
	}


}
free(choix);
return 0;

*/