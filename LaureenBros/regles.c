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

int afficher_regles(Ecran* ecran) {
		int continuer = 1;
		
		SetConsoleOutputCP(GetOEMCP());
		SetConsoleCP(GetOEMCP());
		system("cls");
		contourEcran(ecran);
		SetConsoleOutputCP(1252);
		SetConsoleCP(1252);

		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 9, "1. Vous jouez Mario : récoltez le plus de pièces possibles pour améliorer votre score.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 7, "2. Vous pouvez écraser les ennemis et utiliser les étoiles pour être invincible quelques secondes.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 5, "3. Vous commencez avec un certains nombre de vies : si vous touchez la lave ou un ennemi, vous mourrez.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 3, "4. Contrôles de base : d ou > pour avancer / q ou < pour reculer / espace pour sauter");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 1, "5. Vous pouvez quitter la partie en fermant la fenêtre du jeu, une sauvegarde sera créée.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 + 4, "A vous de jouer!");

		afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 3, " /)~~/)");
		afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 4, "( •.• )");
		afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 5, "(<    )");

		afficherTexte(ecran->largeur / 2 - 15 , ecran->hauteur - 5, "(Pressez une touche pour sortir)");
	
		

		while (1) {
			afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 4, "( •.• )");
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
			Sleep(500);
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
			Sleep(500);
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
			Sleep(500);
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
			afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 4, "( -.- )");
			Sleep(100);
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
			afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 4, "( •.• )");
			Sleep(200);
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
			afficherTexte(ecran->largeur / 2 - 30, ecran->hauteur / 2 + 4, "( -.- )");
			Sleep(100);
			if (_kbhit()) {
				int touche = _getch();
				break;
			}
		}
		return -1;
}
