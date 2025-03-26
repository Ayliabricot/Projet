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


void lancer_ecran(int* choix, char option[6][40]) {
	Ecran* ecran = definirEcran();
	int touche = 0;
	int* difficulte = 0;
	while (1) {
		while (*choix == 0) {
			touche = 0;
			afficherMenu(ecran, touche, choix,option);
			while (1) {
				if (_kbhit()) {
					touche = _getch();


					system("cls");
					afficherMenu(ecran, touche, choix, option);
				}
			}
		}
		while (*choix == 4) {
			char opti[4] = "oui";
			while (*choix == 4) {
				Ecran* ecran = definirEcran();
				*choix = quitterJeuContain(ecran, opti);
			}
			system("cls");
		}
	}
}