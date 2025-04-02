#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#include "ecran.h"
#include "AffichageMenu.h"
#include "placementTexte.h"
#include "quitterJeu.h"
#include "musique.h"

int main() {
    if (!initialiserAudio()) {
        return 1;
    }

    jouerMusique("SDL2/sons/Super Mario Bros (NES) Music - Overworld Theme.mp3");

    Ecran* ecran = definirEcran();
    int touche = 0;
    int* choix = malloc(sizeof(int));
    if (choix == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }
    *choix = 2;

    afficherMenu(ecran, touche, choix);

    while (1) {
        if (_kbhit()) {
            touche = _getch();
            system("cls");
            afficherMenu(ecran, touche, choix);
        }
    }

    free(choix);
    choix = NULL;

    arreterMusique();
    libererAudio();

    return 0;
}
