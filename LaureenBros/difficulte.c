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


void affichageDifficulte(Ecran* ecran, int difficulte) {
	if (!ecran) {
		printf("problème d'allocation");
		return;
	}
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	afficherTexte(ecran->largeur / 2 - 32 / 2, ecran->hauteur / 4, "Choississez votre difficulté :");


	afficherTexte(ecran->largeur / 2 - 15, ecran->hauteur / 3, "  ------+--------+------");
	if (difficulte == 0) {
		afficherTexte(ecran->largeur / 2- 15, ecran->hauteur / 3 + 1, " |\x1b[30m\x1b[47m Easy \x1b[0m| Medium | Hard | ");
		afficherTexte(ecran->largeur / 4 + 10, ecran->hauteur / 2 + 4, "< Difficulté easy ? pfff...looser");
	}
	else if (difficulte == 1) {
		afficherTexte(ecran->largeur / 2-15, ecran->hauteur / 3 + 1, " | Easy |\x1b[30m\x1b[47m Medium \x1b[0m| Hard | ");
		afficherTexte(ecran->largeur / 4 + 10, ecran->hauteur / 2 + 4, "< Difficulté Medium ? moe basique ");
	}
	else if (difficulte == 2) {
		afficherTexte(ecran->largeur / 2-15, ecran->hauteur / 3 + 1, " | Easy | Medium |\x1b[30m\x1b[47m Hard \x1b[0m| ");
		afficherTexte(ecran->largeur / 4 + 10, ecran->hauteur / 2 + 4, "< Difficulté Hard? ah ouais l'ego du gars quoi...");
	}

	afficherTexte(ecran->largeur / 2 -15, ecran->hauteur / 3 + 2, "  ------+--------+------");
	afficherTexte(ecran->largeur / 4, ecran->hauteur / 2 + 3, " /)/)");
	afficherTexte(ecran->largeur / 4, ecran->hauteur / 2 + 4, "( -.-)");

	afficherTexte(ecran->largeur / 4, ecran->hauteur / 2 + 5, " o_(µ)(µ)");
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
}

int choisirDifficulte(int toucheDiff, int difficulte) {


	if (toucheDiff == 'd' && (difficulte != 2)) {

		(difficulte)++;
	}
	else if (toucheDiff == 'q' && (difficulte != 0)) {

		(difficulte)--;
	}
	else if (toucheDiff == 'd' && (difficulte == 2)) {
		difficulte = 0;
	}
	else if (toucheDiff == 'q' && (difficulte == 0)) {
		difficulte = 2;


	}

	return difficulte;
}


int choisirDifficulteContain(Ecran* ecran, Partie* partie) {
	system("cls");
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
	if (!ecran) {
		printf("problème d'allocation");
		return 0;
	}

	int difficulte = 0;
	affichageDifficulte(ecran, difficulte);
	int toucheDiff;
	while (1) {

		if (_kbhit()) {
			system("cls");
			toucheDiff = _getch();
			if (toucheDiff == 13) {
				partie->difficulte = difficulte;
				return 5;
			}
			difficulte = choisirDifficulte(toucheDiff, difficulte);
			affichageDifficulte(ecran, difficulte);
		}
	}
}