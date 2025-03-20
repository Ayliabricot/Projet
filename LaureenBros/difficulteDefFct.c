#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "menu.h"
#include "ecran.h"
#include "placementTexte.h"


void affichageDifficulte(Ecran* ecran, int choixDiff) {
	if (!ecran) {
		printf("problème d'allocation");
		return 0;
	}
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	afficherTexte(ecran->largeur / 2 - 32 / 2, ecran->hauteur /4, "Choississez votre difficulté :");


	afficherTexte(ecran->largeur / 3+6, ecran->hauteur / 3, "  ------+--------+-------");
	if (choixDiff == 0) {
		afficherTexte(ecran->largeur / 3 + 6, ecran->hauteur / 3 + 1, " |\x1b[30m\x1b[47m Easy \x1b[0m | Medium | Hard | ");
	}
	else if (choixDiff == 1) {
		afficherTexte(ecran->largeur / 3 + 6, ecran->hauteur / 3 + 1, " | Easy |\x1b[30m\x1b[47m Medium \x1b[0m | Hard | ");
	}
	else if (choixDiff == 2) {
		afficherTexte(ecran->largeur / 3 + 6, ecran->hauteur / 3 + 1, " | Easy | Medium |\x1b[30m\x1b[47m Hard \x1b[0m | ");
	}
	
	afficherTexte(ecran->largeur / 3+6, ecran->hauteur / 3 + 2, "  ------+--------+-------");
	afficherTexte(ecran->largeur / 4  , ecran->hauteur / 2+3, " /)/)");
	afficherTexte(ecran->largeur / 4 , ecran->hauteur / 2+4, "( -.-)");
	afficherTexte(ecran->largeur / 4 , ecran->hauteur / 2+5, " o_(µ)(µ)");
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
}

int choisirDifficulte() {
	int choixDiff = 0;
	char toucheDiff;
	if (_kbhit) {
		toucheDiff = _getch();
		if (toucheDiff == 'd'&&choixDiff !=2) {

			choixDiff += choixDiff;
		}
		else if (toucheDiff == 'q'&&choixDiff !=0) {

			choixDiff -= choixDiff;
		}
		else if (toucheDiff == 'd' && choixDiff == 2) {
			choixDiff = 0;
		}
		else if (toucheDiff == 'q' && choixDiff == 0) {
			choixDiff = 2;


		}
		return choixDiff;

	}

	else {
		return choixDiff;
	}

	

}


void choisirDifficulteContain(Ecran* ecran) {
	if (!ecran) {
		printf("problème d'allocation");
			return 0;
	}
	int choixDiff=0;
	void affichageDifficulte(ecran, choixDiff);
	while (1) {
		int touche;
		if (_kbhit()) {
			touche = _getch();


			system("cls");
			quitterJeu(ecran, touche, opti);
		}
	}
}
int main() {
	while (1) {

		system("cls");
		Ecran* ecran = definirEcran();
		int choixDiff = choisirDifficulte();
		affichageDifficulte(ecran,choixDiff);

		Sleep(600);
	}
}