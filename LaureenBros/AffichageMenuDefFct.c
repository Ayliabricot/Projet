#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "AffichageMenu.h"

void contourEcran(Ecran* ecran) {
	tailleEcran(ecran);
	for (int i = 0; i < ecran->hauteur; i++) {
		for (int j = 0; j < ecran->largeur; j++) {
			if ((i = 0 || i == (ecran->hauteur) - 1)) {
				printf("#");
			}
			else if (j == 0 || j == (ecran->largeur) - 1) {
				printf("#");
			}
		}
	}
}


