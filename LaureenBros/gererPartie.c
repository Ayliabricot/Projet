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
        printf("probl×me d'allocation");
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
    afficherTexte(ecran->largeur / 4 + 5, ecran->hauteur / 3, " (\\(\\");
    afficherTexte(ecran->largeur / 4 + 5, ecran->hauteur / 3 + 1, " (='.')");
    afficherTexte(ecran->largeur / 4 + 5, ecran->hauteur / 3 + 2, "o(_\")\")");

    char pseudo[50];
    gotoxy(ecran->largeur / 2 - 9, ecran->hauteur / 3 + 1);
    scanf_s("%s", pseudo, (unsigned)sizeof(pseudo)); // Corrected scanf_s usage

    // Corrected strncpy_s usage
    strncpy_s(partie->pseudo, sizeof(partie->pseudo), pseudo, sizeof(partie->pseudo) - 1);
    partie->pseudo[sizeof(partie->pseudo) - 1] = '\0';

    FILE* file = fopen("pseudo.txt", "a");
    if (file) {
        fprintf(file, " %s", pseudo);
        fclose(file);
    }

    SetConsoleOutputCP(GetOEMCP());
    SetConsoleCP(GetOEMCP());
}


//continuer partie

void afficherSavePartie(Ecran* ecran, Partie* partie) {
    while (1) {
        if (!ecran) {
            printf("probleme d'allocation");
            return;
        }
        SetConsoleOutputCP(GetOEMCP());
        SetConsoleCP(GetOEMCP());
        contourEcran(ecran);
        SetConsoleOutputCP(1252);
        SetConsoleCP(1252);

        afficherTexte(ecran->largeur / 2 - 45 / 2, ecran->hauteur / 4, "Veuillez saisir le nom de votre sauvegarde :");

        afficherTexte(ecran->largeur / 2 - 12, ecran->hauteur / 3 + 1, "-> ");
        afficherTexte(ecran->largeur / 2 - 12, ecran->hauteur / 3 + 2, "-------------------------");
        afficherTexte(ecran->largeur / 4 + 5, ecran->hauteur / 3, " (\\(\\");
        afficherTexte(ecran->largeur / 4 + 5, ecran->hauteur / 3 + 1, " (='.')  ♥");
        afficherTexte(ecran->largeur / 4 + 5, ecran->hauteur / 3 + 2, "o(_\")\")");

        char pseudo[50];
        gotoxy(ecran->largeur / 2 - 9, ecran->hauteur / 3 + 1);
        scanf_s("%s", pseudo, (unsigned)sizeof(pseudo)); // Corrected scanf_s usage

        // Corrected strncpy_s usage
        strncpy_s(currentPartie->pseudo, sizeof(currentPartie->pseudo), pseudo, sizeof(currentPartie->pseudo) - 1);
        currentPartie->pseudo[sizeof(currentPartie->pseudo) - 1] = '\0';


        if (_kbhit()) {
            char touche = _getch();
            if (touche == 49) {
                //charge save 1
                break;
            }
            else if(touche == 50) {
                //charge save 2
                break;
            }
            else if (touche == 51) {
                //charge save 3
                break;
            }
            else if (touche == 51) {
                //charge save 4
                break;
            }
            else {
                break;//sort si autre touche pressee
            }
        }

    }
}

void affichageScore(Ecran* ecran) {
    while (1) {
        if (!ecran) {
            printf("probleme d'allocation");
            return;
        }
        SetConsoleOutputCP(GetOEMCP());
        SetConsoleCP(GetOEMCP());
        contourEcran(ecran);
        SetConsoleOutputCP(1252);
        SetConsoleCP(1252);
        afficherTexte(ecran->largeur / 2 - 40 / 2, ecran->hauteur / 4-2, "╔══════════════════════════════════════════╗");
        afficherTexte(ecran->largeur / 2 - 21 / 2, ecran->hauteur / 4, "TABLEAU DES SCORES :");
    }
}