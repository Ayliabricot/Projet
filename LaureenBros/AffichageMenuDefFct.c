#include <windows.h>
#include <stdio.h>
#include "ecran.h"

//hugo
//penser à faire une fonction pour free les malloc


int tailleEcran() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    Ecran* ecran = malloc(sizeof(Ecran));
    
    if (largeur == NULL || hauteur == NULL) { //sécurisation
        return 0;
    }

    // Récupérer les infos de la console
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE)/*récupere id console Windows*/, &csbi)) {//csbi recoit toute les infos de la fenetre
        largeur = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        hauteur = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        printf("Taille de la fenêtre de la console : %d colonnes x %d lignes\n", largeur, hauteur);
    }
    else {
        printf("Erreur : Impossible de récupérer la taille de la console.\n");
    }

    return 0;
}