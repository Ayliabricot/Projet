#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "placementTexte.h"

void contourEcran(Ecran* ecran) {
	tailleEcran(ecran);
	char c = 219;
	int largeur = ecran->largeur - 1;
	int hauteur = ecran->hauteur - 1;
	for (int i = 0; i < ecran->hauteur; i++) {
		for (int j = 0; j < ecran->largeur; j++) {
			if ((i == 0 || i == hauteur)) {
				printf("%c",c);
			}
			else if (j == 0 || j == largeur) {
				printf("%c",c);
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

void afficherMenu(Ecran* ecran) {
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	
		int choix = 0;
		char touche;
		int x = 1;

		int y = 1;
		coordonne(x, y);
		for (int a = 1; a < ecran->largeur - 1; a++) {
			printf("*");
		}
		printf("\n\n\n\n\n\n             *****  LAUREEN   BROS  *****\n");
		char option[6][40] = { "1. Entre le pseudo du joueur","2. Choisir difficulté","3. Nouvelle partie","4. Continuer partie","5. Accéder au tableau des scores","6. Quitter le jeu" };
		for (int i = 0; i < 6; i++) {
			if (choix == i) {
				printf("\x1b[30m\x1b[47m %s \x1b[0m\n", option[i]);
			}
			else {
				printf("%s\n",option[i]);
			}
		}
		

		printf("Choisissez une option : ");
		
		SetConsoleOutputCP(GetOEMCP());
		SetConsoleCP(GetOEMCP());
	
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

