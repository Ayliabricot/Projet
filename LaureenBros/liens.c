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
#include "gererParties.h"


void lancer_ecran(int* choix, char option[5][40],Partie** tableau,int* nbParties) {
	Ecran* ecran = definirEcran();
	int touche = 0;
	while (1) {
		while (*choix == -1) {
			touche = 0;
			*choix = 0;
			afficherMenu(ecran, touche, choix,option,tableau,nbParties);
			while (1) {
				if (_kbhit()) {
					touche = _getch();


					system("cls");
					afficherMenu(ecran, touche, choix, option,tableau,nbParties);
				}
			}
		}
		while (*choix == 0) {
			Ecran* ecran = definirEcran();
			*choix = afficher_regles(ecran);
			system("cls");
		}
		while (*choix == 1) {
			Ecran* ecran = definirEcran();
			adapterMemoire(tableau, *nbParties + 1);
			printf("ok");
			tableau[*nbParties]=nouvelle_partie();
			demanderPseudo(ecran, tableau[*nbParties]);
			
			system("cls");
			ecran = definirEcran();
			*choix = choisirDifficulteContain(ecran, tableau[*nbParties]);
			*nbParties = *nbParties + 1;
			system("cls");
		}
		while (*choix == 4) {
			char opti[4] = "oui";
			while (*choix == 5) {
				Ecran* ecran = definirEcran();
				*choix = quitterJeuContain(ecran, opti);
			}
			system("cls");
		}
	}
}