#include <windows.h>
#include <stdio.h>
#include "ecran.h"
#include "AffichageMenu.h"

//hugo
//penser à faire une fonction pour free les malloc

Ecran* definirEcran() {
    Ecran* ecran = malloc(sizeof(Ecran));
}

void tailleEcran(Ecran* ecran) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Récupérer les infos de la console
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)/*récupere id console Windows*/, &csbi)) {//csbi recoit toute les infos de la fenetre
        ecran->largeur = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        ecran->hauteur = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        //printf("Taille de la fenêtre de la console : %d colonnes x %d lignes\n", ecran->largeur, ecran->hauteur);
    }
    else {
        printf("Erreur : Impossible de récupérer la taille de la console.\n");
    }
}

void contourEcran(Ecran* ecran) {
	tailleEcran(ecran);
	char c = 219;
	int largeur = ecran->largeur - 1;
	int hauteur = ecran->hauteur - 1;
	for (int i = 0; i < ecran->hauteur; i++) {
		for (int j = 0; j < ecran->largeur; j++) {
			if ((i == 0 || i == hauteur)) {
				gotoxy(j, i);
				printf("%c", c);
			}
			else if (j == 0 || j == largeur) {
				gotoxy(j, i);
				printf("%c", c);
			}
		}
		if (i == hauteur) {
			break;
		}
		printf("\n");
	}
}

void libererEcran(Ecran* ecran) {
    free(ecran);
    ecran = NULL;
    return 0;
}