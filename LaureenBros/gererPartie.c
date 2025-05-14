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
#include "gererParties.h"
#include "jeu.h"

Partie** creerTableau(void) {
    Partie** tableau = malloc(10 * sizeof(Partie*));

    for (int i = 0; i < 10; i++) {
        tableau[i] = NULL;
    }

    return tableau;
}

Partie* nouvelle_partie(void) {
    Partie* partie = malloc(sizeof(Partie));
    if (partie == NULL) {
        return NULL;
    }
    partie->difficulte = 0;
    partie->objet = 0;
    // Corrected strcpy_s usage
    strcpy_s(partie->pseudo, sizeof(partie->pseudo), "Vide");
    partie->score = 0;
    partie->vies = 3;
    partie->x = 0;
    partie->y = 0;

    return partie;
}

void demanderPseudo(Ecran* ecran, Partie* partie) {
    system("cls");
    if (!ecran) {
        printf("probleme d'allocation");
        return;
    }
    SetConsoleOutputCP(GetOEMCP());
    SetConsoleCP(GetOEMCP());
    contourEcran(ecran);
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);

    afficherTexte(ecran->largeur / 2 - 32 / 2, ecran->hauteur / 4, "Veuillez saisir votre pseudo :");

    afficherTexte(ecran->largeur / 2 - 12, ecran->hauteur / 3 + 1, "-> ");
    afficherTexte(ecran->largeur / 2 - 12, ecran->hauteur / 3 + 2, "-------------------------");

    char pseudo[50];
    gotoxy(ecran->largeur / 2 - 9, ecran->hauteur / 3 + 1);
    scanf_s("%s", pseudo, (unsigned)sizeof(pseudo)); // Corrected scanf_s usage

    // Corrected strncpy_s usage
    strncpy_s(partie->pseudo, sizeof(partie->pseudo), pseudo, sizeof(partie->pseudo) - 1);
    partie->pseudo[sizeof(partie->pseudo) - 1] = '\0';

    FILE* file = fopen("pseudo.txt", "w");
    if (file) {
        fprintf(file, "%s", pseudo);
        fclose(file);
    }

    SetConsoleOutputCP(GetOEMCP());
    SetConsoleCP(GetOEMCP());
}