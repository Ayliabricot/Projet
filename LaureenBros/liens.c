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
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "jeu.h"

void lancer_ecran(int* choix, char option[5][40],Partie** tableau,int* nbParties, int argc, char* argv[]) {
	Ecran* ecran = definirEcran();
	Ecran* nouveauEcran = definirEcran();
	int touche = 0;
	chargerPartieUNIQUE = 0;
	while (1) {

		while (*choix == -1) {
			touche = 0;
			*choix = 0;

			SetConsoleOutputCP(GetOEMCP());
			SetConsoleCP(GetOEMCP());
			
			contourEcran(ecran);
			SetConsoleOutputCP(1252);
			SetConsoleCP(1252);
			afficherMenu(ecran, touche, choix,option,tableau,nbParties,argc,argv);
			while (1) {
				if (_kbhit()) {
					tailleEcran(nouveauEcran);
					if (nouveauEcran->hauteur != ecran->hauteur || nouveauEcran->largeur != ecran->largeur) {
						system("cls");
						contourEcran(ecran);
					}
					touche = _getch();

					afficherMenu(ecran, touche, choix, option,tableau,nbParties, argc, argv);
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
			tableau[*nbParties]=nouvelle_partie();
			demanderPseudo(ecran, tableau[*nbParties]);
			currentPartie = tableau[*nbParties];
			cacherCurseur();

			system("cls");
			ecran = definirEcran();
			*choix = choisirDifficulteContain(ecran, tableau[*nbParties]);
			*nbParties = *nbParties + 1;
			system("cls");
			lancerJeu(argc, argv);
			*choix = -1;
		}
		while (*choix == 2) {
			system("cls");
			Ecran* ecran = definirEcran();
			afficherSavePartie( ecran, tableau);
			system("cls");
			*choix = -1;
			//chargerPartieUNIQUE = 1;
			/*system("cls");*/
			//lancerJeu(argc, argv);
			/**choix = -1;*/
			/*return;*/
		}
		while (*choix == 3) {
			
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