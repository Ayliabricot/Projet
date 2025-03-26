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

void afficher_regles() {
	int quitterJeu(Ecran * ecran, int touche, char opti[4]) {

		contourEcran(ecran);
		SetConsoleOutputCP(1252);
		SetConsoleCP(1252);
		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 - 1, 1, "Vous jouez Mario : récoltez le plus de pièces pour améliorer votre score.");
		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 - 2, 2, "Vous pouvez ramasser les objets que vous trouvez mais vous ne pouvez en conserver qu'un à la fois.");
		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 - 1, 3, "Vous jouez Mario : récoltez le plus de pièces pour améliorer votre score.");
		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 - 2, 2, "Vous pouvez ramasser les objets que vous trouvez mais vous ne pouvez en conserver qu'un à la fois.");

		afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2, "vouloir quitter ? ");
		//afficherTexte(ecran->largeur / 2 - 18 / 2, ecran->hauteur / 2 + 2, "oui");

		//afficherTexte(ecran->largeur / 2 + 4, ecran->hauteur / 2 + 2, "non");\n'oui'. Quitter...\n"

		SetConsoleOutputCP(GetOEMCP());
		SetConsoleCP(GetOEMCP());


		return 1;
	}
}