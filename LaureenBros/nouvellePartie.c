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


/*void affichageDifficulte(Ecran* ecran, int* difficulte) {
	if (!ecran) {
		printf("problème d'allocation");
		return;
	}
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	afficherTexte(ecran->largeur / 2 - 32 / 2, ecran->hauteur / 4, "Veuillez saisir votre pseudo :");


	afficherTexte(ecran->largeur / 3 + 6, ecran->hauteur / 3, "  ------+--------+------");
	
	int test;
	gotoxy(ecran->largeur / 3 + 6, ecran->hauteur / 3 + 1);
	scanf_s("%d", &test);

	afficherTexte(ecran->largeur / 3 + 6, ecran->hauteur / 3 + 2, "  ------+--------+------");
	afficherTexte(ecran->largeur / 4, ecran->hauteur / 2 + 3, " /)/)");
	afficherTexte(ecran->largeur / 4, ecran->hauteur / 2 + 4, "( -.-)");

	afficherTexte(ecran->largeur / 4, ecran->hauteur / 2 + 5, " o_(µ)(µ)");
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
}

int* choisirDifficulte(int toucheDiff, int* difficulte) {


	if (toucheDiff == 'd' && (*difficulte != 2)) {

		(*difficulte)++;
	}
	else if (toucheDiff == 'q' && (*difficulte != 0)) {

		(*difficulte)--;
	}
	else if (toucheDiff == 'd' && (*difficulte == 2)) {
		*difficulte = 0;
	}
	else if (toucheDiff == 'q' && (*difficulte == 0)) {
		*difficulte = 2;


	}

	return *difficulte;





}


int choisirDifficulteContain(Ecran* ecran, int* difficulte) {
	system("cls");
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
	if (!ecran) {
		printf("problème d'allocation");
		return 0;
	}

	affichageDifficulte(ecran, difficulte);
	int toucheDiff;
	while (1) {

		if (_kbhit()) {
			system("cls");
			toucheDiff = _getch();
			if (toucheDiff == 13) {
				return -1;
			}
			*difficulte = choisirDifficulte(toucheDiff, difficulte);
			affichageDifficulte(ecran, difficulte);
		}
	}
}*/