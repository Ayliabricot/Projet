#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "placementTexte.h"
#include "quitterJeu.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

int choisir(Ecran* ecran, int touche, char opti[4], int resultat) {

	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	if (resultat == 0) {
		afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 - 2, "Vous avez \x1b[31mperdu\x1b[0m");
	}
	else if (resultat == 1) {
		afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 - 2, "Vous avez \x1b[32mréussi\x1b[0m");
	}
	else if (resultat == 2) {
		afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 - 2, "Vous avez \x1b[34mquitté\x1b[0m");
	}

	afficherTexte(ecran->largeur / 2 - 10, ecran->hauteur / 2 - 1, "Voulez-vous quitter?");
	
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());

	if (_kbhit) {
		if (touche == 'd') {

			strcpy_s(opti, sizeof(opti), "non");
		}
		else if (touche == 'q') {

			strcpy_s(opti, sizeof(opti), "oui");
		}
		if (touche == 13 && strcmp(opti, "oui") == 0) {
			afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 - 2, "Vous avez choisi:");
			afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 - 1, "      'oui'      ");
			afficherTexte(ecran->largeur / 2 - 10, ecran->hauteur / 2 + 1, "      Quitter...    ");
			gotoxy(ecran->largeur / 2 - 9, ecran->hauteur / 2 + 1);
			printf("\x1b[31m      Quitter...    \x1b[0m");
			afficherTexte(ecran->largeur / 2 - 15, ecran->hauteur - 6, "Pressez une touche pour sortir");
			getchar();
			system("cls");
			exit(0);
		}
		else if (touche == 13 && strcmp(opti, "non") == 0) {

			return -1;
		}

	}
	if (strcmp(opti, "oui") == 0) {
		afficherTexteHighlight(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 1, " oui ");
		afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 1, " non ");
	}
	else {
		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 1, " oui ");
		afficherTexteHighlight(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 1, " non ");
	}



	return 1;
}

int jeuFiniContain(Ecran* ecran, char opti[4], int resultat) {
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
	system("cls");
	int valeur;
	Ecran* nouveauEcran = definirEcran();
	valeur = choisir(ecran, 0, opti, resultat);
	while (1) {
		int touche;
		if (_kbhit()) {
			tailleEcran(nouveauEcran);
			if (nouveauEcran->hauteur != ecran->hauteur || nouveauEcran->largeur != ecran->largeur) {
				system("cls");
				contourEcran(ecran);
			}
			touche = _getch();

			valeur = choisir(ecran, touche, opti,resultat);
			if (valeur == -1) {
				return valeur;
			}
		}
	}
	return valeur;
}
