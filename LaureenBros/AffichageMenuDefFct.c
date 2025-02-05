#include <windows.h>
#include <stdio.h>
#include "ecran.h"

void contourEcran(Ecran* ecran) {
	tailleEcran(ecran);
	int largeur = ecran->largeur - 1;
	int hauteur = ecran->hauteur - 1;
	for (int i = 0; i < ecran->hauteur; i++) {
		for (int j = 0; j < ecran->largeur; j++) {
			if ((i == 0 || i == hauteur)) {
				printf("#");
			}
			else if (j == 0 || j == largeur) {
				printf("#");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}


