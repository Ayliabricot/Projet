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
		SetConsoleOutputCP(GetOEMCP());
		SetConsoleCP(GetOEMCP());
		system("cls");
		contourEcran(ecran);
		SetConsoleOutputCP(1252);
		SetConsoleCP(1252);

		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 9, "1. Vous jouez Mario : r�coltez le plus de pi�ces pour am�liorer votre score.");
		afficherTexte(ecran->largeur / 2 - 50 , ecran->hauteur / 2 - 7, "2. Vous pouvez ramasser les objets que vous trouvez mais vous ne pouvez en conserver qu'un � la fois.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 5, "3. Vous commencez avec 3 vies : � chaque fois que vous touchez un ennemi, vous mourrez et perdez une vie.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 3, "4. Contr�les de base : d pour avancer / q pour reculer.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 - 1, "5. Vous pouvez quitter la partie gr�ce au menu, une sauvegarde sera cr��e.");
		afficherTexte(ecran->largeur / 2 - 50, ecran->hauteur / 2 + 3, "A vous de jouer!");
		
		getchar();
		//afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");

		//afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");\n'oui'. Quitter...\n"

		SetConsoleOutputCP(GetOEMCP());
		SetConsoleCP(GetOEMCP());


		return -1;
}

