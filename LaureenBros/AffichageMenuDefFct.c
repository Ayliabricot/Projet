#include <windows.h>
#include <stdio.h>
#include "affichageMenu.h"
//hugo
//penser � faire une fonction pour free les malloc
int tailleEcran() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int* largeur;
    int* hauteur;
    largeur = malloc(sizeof(int));
    hauteur = malloc(sizeof(int));
    if (largeur == NULL || hauteur == NULL) { //s�curisation
        return 0;
    }

    // R�cup�rer les infos de la console
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)/*r�cupere id console Windows*/, &csbi)) {//csbi recoit toute les infos de la fenetre
        largeur = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        hauteur = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        printf("Taille de la fen�tre de la console : %d colonnes x %d lignes\n", largeur, hauteur);
    }
    else {
        printf("Erreur : Impossible de r�cup�rer la taille de la console.\n");
    }

    return 0;
}