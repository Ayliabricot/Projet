
#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "placementTexte.h"
#include "affichageMenu.h"



void afficherMenu(Ecran* ecran, int touche, int* choix, char option[5][40],Partie** tableau,int* nbParties) {
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);


	

	if (touche == 115 || touche == 122) {
		definirChoix(touche, choix);
	}
	else if (touche == 13) {
		lancer_ecran(choix,option,tableau,nbParties);
	}

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 1, "*");

	}
	afficherTexte(ecran->largeur / 2 - 29 / 2, 3, "*****  LAUREEN   BROS  *****");
	

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 5, "*");
	}

	for (int i = 0; i < 5; i++) {
		if (*choix == i) {
			afficherTexteHighlight(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i, option[i]);
			
		}
		else {
			afficherTexte(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i, option[i]);
		
		}
	}

	afficherTexte(ecran->largeur / 2 - 22 / 2, ecran->hauteur - 5, "Choisissez une option");
	afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur - 4,"(press to adjust)");

	
	

	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());

}

void definirChoix(int touche, int* choix) {
	if (touche == 122 && *choix != 0) {
		*choix = *choix - 1;
	}
	else if (touche == 122 && *choix == 0) {
		*choix = 4;
	}
	else if (touche == 115 && *choix != 4) {
		*choix = *choix + 1;
	}
	else if (touche == 115 && *choix == 4) {
		*choix = 0;
	}
}

void cacherCurseur(void) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void afficherCurseur(void) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}