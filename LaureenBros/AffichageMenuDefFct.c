
#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "placementTexte.h"
#include "affichageMenu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>



void afficherMenu(Ecran* ecran, int touche, int* choix, char option[5][40],Partie** tableau,int* nbParties, int argc, char* argv[]) {
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());

	contourEcran(ecran);

	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);


	

	if (touche == 115 || touche == 122) {
		definirChoix(touche, choix);
	}
	else if (touche == 13) {
		lancer_ecran(choix,option,tableau,nbParties,argc,argv);
	}

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 2, "*");

	}
	afficherTexte(ecran->largeur / 2 - 29 / 2, 4, "*****  LAUREEN   BROS  *****");
	

	for (int a = 1; a < ecran->largeur - 1; a++) {
		afficherTexte(a, 6, "*");
	}

	for (int i = 0; i < 5; i++) {
		if (*choix == i) {
			afficherTexteHighlight(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i +1, option[i]);
			
		}
		else {
			afficherTexte(ecran->largeur / 2 - strlen(option[i]) / 2, ecran->hauteur / 3 + 2 * i + 1, option[i]);
		
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