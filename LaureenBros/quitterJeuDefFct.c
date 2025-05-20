#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "placementTexte.h"
#include "quitterJeu.h"

int confirmerChoix(char opti[4]) {
	int touche;
	if (_kbhit) {
		touche = _getch();
		if (touche == 13 && strcmp(opti, "oui") == 0) {
			printf("oui");
			exit(0);
		}
		else if (touche == 13 && strcmp(opti, "non") == 0) {
			printf("ok");
			return 0;

		}
	}
	return 1;
}


int quitterJeu(Ecran* ecran, int touche, char opti[4]) {
	
    contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);
	afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur/2-2, "�tes vous s�r de");
	
	afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2-1 , "vouloir quitter?");
	//afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");

	//afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");\n'oui'. Quitter...\n"
	
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());

	if (_kbhit) {
		if (touche == 'd') {
		
			strcpy_s(opti, sizeof(opti), "non");
		}
		else if (touche == 'q') {
			
			strcpy_s(opti,sizeof(opti), "oui");
		}
		if (touche == 13 && strcmp(opti, "oui") == 0) {
			afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 -2, "Vous avez choisi:");
			afficherTexte(ecran->largeur / 2 - 8, ecran->hauteur / 2 - 1, "      'oui'      ");
			afficherTexte(ecran->largeur / 2 - 10, ecran->hauteur / 2 +1, "      Quitter...    ");
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

int quitterJeuContain(Ecran* ecran, char opti[4]) {
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
	system("cls");
	int valeur;
	Ecran* nouveauEcran = definirEcran();
	valeur=quitterJeu(ecran, 0, opti);

	while (1) {
		int touche;
		if (_kbhit()) {
			tailleEcran(nouveauEcran);
			if (nouveauEcran->hauteur != ecran->hauteur || nouveauEcran->largeur != ecran->largeur) {
				system("cls");
				contourEcran(ecran);
			}
			touche = _getch();

			valeur=quitterJeu(ecran, touche, opti);
			if (valeur == -1) {
				return valeur;
			}
		}
	}
	return valeur;
}
