#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "ecran.h"
#include "placementTexte.h"

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
	afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur/2-1, "Êtes vous sûr de");
	
	afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 , "vouloir quitter ? ");
	//afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");

	//afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");
	
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
			  printf("Vous avez choisi 'oui'. Quitter...\n");
			exit(0);
		}
		else if (touche == 13 && strcmp(opti, "non") == 0) {
			return 0;


		}
		
	}
	if (strcmp(opti, "oui") == 0) {
		afficherTexteHighlight(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");
		afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");
	}
	else {
		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");
		afficherTexteHighlight(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");
	}
	
		

	return 1;
}

void quitterJeuContain(Ecran* ecran, char opti[4]) {
	quitterJeu(ecran, 0, opti);
	while (1) {
		int touche;
		if (_kbhit()) {
			touche = _getch();

			
			system("cls");
			quitterJeu(ecran, touche, opti);
		}
	}
}