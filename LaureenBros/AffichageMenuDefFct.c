
#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "placementTexte.h"
#include "affichageMenu.h"

void contourEcran(Ecran* ecran) {
	tailleEcran(ecran);
	char c = 219;
	int largeur = ecran->largeur - 1;
	int hauteur = ecran->hauteur - 1;
	for (int i = 0; i < ecran->hauteur; i++) {
		for (int j = 0; j < ecran->largeur; j++) {
			if ((i == 0 || i == hauteur)) {
				printf("%c", c);
			}
			else if (j == 0 || j == largeur) {
				printf("%c", c);
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

void afficherMenu(Ecran* ecran, int touche) {
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);


	int choix = 2;
	int* pChoix = &choix;



	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 1, "*");

	}
	afficherTexte(ecran->largeur / 2 - 29 / 2, 3, "*****  LAUREEN   BROS  *****");
	/*printf("*****  LAUREEN   BROS  *****\n");*/

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 5, "*");
	}

	char option[6][40] = { "1. Entre le pseudo du joueur","2. Choisir difficulté","3. Nouvelle partie","4. Continuer partie","5. Accéder au tableau des scores","6. Quitter le jeu" };
	for (int i = 0; i < 6; i++) {
		if (choix == i) {
			afficherTexteHighlight(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i, option[i]);
			/*printf("\x1b[30m\x1b[47m %s \x1b[0m", option[i]);*/
		}
		else {
			afficherTexte(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i, option[i]);
			/*printf("%s",option[i]);*/
		}
	}

	afficherTexte(ecran->largeur / 2 - 22 / 2, ecran->hauteur - 5, "Choisissez une option");

	;
	if (touche == 115 || touche == 122) {
		definirChoix(touche, pChoix);
		system("cls");
	}

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

//int main() {
//	Ecran* ecran = definirEcran();
//	while (1) {
//
//
//		contourEcran(ecran);
//		Sleep(500);
//		system("cls");
//	}
//
//	return 0;
//}

//void coordonne(int x, int y) {
//	COORD coord;
//	coord.X = x;  // position X
//	coord.Y = y;  // position Y
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}
//
//int main() {
//
//	coordonne(10, 5);
//	printf("Ceci est un texte à la position (10, 5)\n");
//
//
//	coordonne(20, 10);
//	printf("Un autre texte à la position (20, 10)\n");
//
//	return 0;
//}

