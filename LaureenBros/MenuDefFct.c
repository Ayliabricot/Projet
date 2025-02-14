#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "ecran.h"
#include "placementTexte.h"

void confirmerChoix() {

}


void quitterJeu(Ecran* ecran, int touche) {
	
    contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);
	afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur/2-1, "Êtes vous sûr de");
	
	afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 , "vouloir quitter ? ");
	//afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");

	//afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");
	
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
	char opti[4] = "oui";
	if (_kbhit) {
		if (touche == 'd') {
		
			strcpy_s(opti, sizeof(opti), "non");
		}
		else if (touche == 'q') {
			
			strcpy_s(opti,sizeof(opti), "oui");
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
	

}

void quitterJeuContain(Ecran* ecran) {
	quitterJeu(ecran, 0);
	while (1) {
		int touche;
		if (_kbhit()) {
			touche = _getch();

			
			system("cls");
			quitterJeu(ecran, touche);
		}
	}
}