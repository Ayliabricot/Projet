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

int affichageScore(Ecran* ecran) {
    while (1) {
        if (!ecran) {
            printf("probleme d'allocation");
            return;
        }
        SetConsoleOutputCP(GetOEMCP());
        SetConsoleCP(GetOEMCP());
        contourEcran(ecran);
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);


        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 - 2, "╔══════════════════════════════════════════╗");
     

        afficherTexte(ecran->largeur / 2 - 45 / 2, ecran->hauteur / 4, "║            TABLEAU DES SCORES :          ║");
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 +2 , "╚══════════════════════════════════════════╝");

        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 4, "════════════════════════════════════════════");
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 5, "║ 🏆 │ Pseudo              │ Score         ║");
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 6, "────────────────────────────────────────────");
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 7, "║ 🥇 │                     │               ║");
        char pseudoA[50] = "hugo";
        char scoreA[20] = "2070";
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 7, pseudoA);
        afficherTexte(ecran->largeur / 2 +7, ecran->hauteur / 4 + 7,scoreA);

        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 8, "║ 🥈 │                     │               ║");
        char pseudoB[50] = "Aylia";
        char scoreB[20] = "2050";
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 8, pseudoB);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 8, scoreB);


        char pseudo3[50] = "Celian";
        char score3[20] = "1000";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 9, "║ 🥉 │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 9, pseudo3);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 9, score3);

        // Ligne 4
        char pseudo4[50] = "Lina";
        char score4[20] = "980";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 10, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 10, pseudo4);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 10, score4);

        // Ligne 5
        char pseudo5[50] = "Jade";
        char score5[20] = "930";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 11, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 11, pseudo5);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 11, score5);

        // Ligne 6
        char pseudo6[50] = "Noah";
        char score6[20] = "880";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 12, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 12, pseudo6);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 12, score6);

        // Ligne 7
        char pseudo7[50] = "Sasha";
        char score7[20] = "860";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 13, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 13, pseudo7);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 13, score7);

        // Ligne 8
        char pseudo8[50] = "Ethan";
        char score8[20] = "820";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 14, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 14, pseudo8);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 14, score8);

        // Ligne 9
        char pseudo9[50] = "Léo";
        char score9[20] = "800";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 15, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 15, pseudo9);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 15, score9);

        // Ligne 10
        char pseudo10[50] = "Mia";
        char score10[20] = "750";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 16, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 16, pseudo10);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 16, score10);

        // Ligne 11
        char pseudo11[50] = "Nina";
        char score11[20] = "730";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 17, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 17, pseudo11);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 17, score11);

        // Ligne 12
        char pseudo12[50] = "Tom";
        char score12[20] = "710";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 18, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 18, pseudo12);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 18, score12);

        // Ligne 13
        char pseudo13[50] = "Inès";
        char score13[20] = "690";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 19, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 19, pseudo13);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 19, score13);

        // Ligne 14
        char pseudo14[50] = "Loris";
        char score14[20] = "670";
        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 20, "║ 🎖️ │                     │               ║");
        afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 20, pseudo14);
        afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 20, score14);

        afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 21, "════════════════════════════════════════════");
        SetConsoleOutputCP(1252);
        SetConsoleCP(1252);
        if (_kbhit()) {
            return 5;
        }
    }
    
}

