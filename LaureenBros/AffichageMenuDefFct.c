#include <windows.h>
#include <stdio.h>
#include "ecran.h"

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
void afficherMenu() {
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	while (1) {
		int choix = 0;
		char touche;
		printf("\n\n\n\n\n\n             *****  LAUREEN   BROS  *****");
		char option[6][40] = { "1. Entre le pseudo du joueur","2. Choisir difficulté","3. Nouvelle partie","4. Continuer partie","5. Accéder au tableau des scores","6. Quitter le jeu" };
		for (int i = 0; i < 6; i++) {
			if (choix == i) {
				printf("\x1b[30m\x1b[47m %s \x1b[0m", option[i]);
			}
			else {
				printf("%s",option[i]);
			}
		}
		

		printf("Choisissez une option : ");
		/*system("cls");*/
		Sleep(5000);
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

//void gotoxy(int x, int y) {
//	COORD coord;
//	coord.X = x;  // position X
//	coord.Y = y;  // position Y
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}
//
//int main() {
//
//	gotoxy(10, 5);
//	printf("Ceci est un texte à la position (10, 5)\n");
//
//
//	gotoxy(20, 10);
//	printf("Un autre texte à la position (20, 10)\n");
//
//	return 0;
//}

