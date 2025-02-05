#include <windows.h>
#include <stdio.h>
#include "ecran.h"

//hugo
//penser � faire une fonction pour free les malloc

Ecran* definirEcran() {
    Ecran* ecran = malloc(sizeof(Ecran));
    ecran = NULL;
}

void tailleEcran(Ecran* ecran) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (ecran!= NULL) { //s�curisation
        return;
    }

    // R�cup�rer les infos de la console
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)/*r�cupere id console Windows*/, &csbi)) {//csbi recoit toute les infos de la fenetre
        ecran->largeur = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        ecran->hauteur = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        printf("Taille de la fen�tre de la console : %d colonnes x %d lignes\n", ecran->largeur, ecran->hauteur);
    }
    else {
        printf("Erreur : Impossible de r�cup�rer la taille de la console.\n");
    }
}

void libererEcran(Ecran* ecran) {
    free(ecran);
    ecran = NULL;
    return 0;
}