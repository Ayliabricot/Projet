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
		while (*choix == -1) {
			touche = 0;
			*choix = 0;
			afficherMenu(ecran, touche, choix,option);
			while (1) {
				if (_kbhit()) {
					touche = _getch();


					system("cls");
					afficherMenu(ecran, touche, choix, option);
				}
			}
		}
		if (*choix == 0) {
			Ecran* ecran = definirEcran();
			*choix = afficher_regles(ecran);
			system("cls");
		}
		while (*choix == 5) {
			char opti[4] = "oui";
			while (*choix == 5) {
				Ecran* ecran = definirEcran();
				*choix = quitterJeuContain(ecran, opti);
			}
			system("cls");
		}
	}
}