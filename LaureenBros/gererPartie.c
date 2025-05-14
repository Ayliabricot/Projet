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

    FILE* file = fopen("pseudo.txt", "w");
    if (file) {
        fprintf(file, "%s", pseudo);
        fclose(file);
    }

    SetConsoleOutputCP(GetOEMCP());
    SetConsoleCP(GetOEMCP());
}


//continuer partie

void afficherSavePartie(Ecran* ecran, Partie* partie) {
    
    if (!ecran) {
        printf("probleme d'allocation");
        return;
    }
    SetConsoleOutputCP(GetOEMCP());
    SetConsoleCP(GetOEMCP());
    contourEcran(ecran);
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);
    afficherTexte(ecran->largeur / 2 - 34 / 2, 3, "Voici Vos sauvegardes de partie:");
    int margeL = ((ecran->largeur  / 2 )-45)/2;
    int margeH = ((ecran->hauteur / 2)-10)/2;
    //save slot numero 1
    char distanceA [10] = "0"; // mettre egal aux donne dans le fichier de sauvegarde
    char vieA[5] = "3";
    char mondeA[3] = "1";
    char levelA[3] = "1";
    char pseudoA[50] = "Hugo";
    

    afficherTexte(margeL+1, margeH+3, "+------------------------------------------+");
    afficherTexte(margeL + 1, margeH + 4, "| Emplacement de sauvegarde:               |");
    afficherTexte(margeL + 31, margeH + 4,pseudoA);
    afficherTexte(margeL + 1, margeH + 5, "|                                          |");
    afficherTexte(margeL + 1, margeH + 6, "| monde: -                                 |");
    afficherTexte(margeL + 9, margeH + 6, mondeA);
    afficherTexte(margeL + 11, margeH + 6, levelA);
    afficherTexte(margeL + 1, margeH + 7, "| Distance:    m                           |");
    afficherTexte(margeL + 13, margeH + 7,distanceA);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    if (strcmp("3", vieA) == 0) {
        afficherTexte(margeL + 1, margeH + 8, "| vies: [♥][♥][♥]                          |");
    }
    else if (strcmp("2", vieA) == 0) {
        afficherTexte(margeL + 1, margeH + 8, "| vies: [♥][♥]                             |");
    }
    else if (strcmp("1", vieA) == 0) {
        afficherTexte(margeL + 1, margeH + 8, "| vies: [♥]                                |");
    }
    afficherTexte(margeL + 1, margeH + 9, "| Personnage: Mario                        |");
    afficherTexte(margeL + 1, margeH + 10, "|                                          |");
    afficherTexte(margeL + 1, margeH + 11, "| → (Press [1] to Load)                    |");
    afficherTexte(margeL + 1, margeH + 12, "+------------------------------------------+");
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);


    //save slot numero 2
    char distanceB[10] = "150"; // mettre egal aux donne dans le fichier de sauvegarde
    char vieB[5] = "3";
    char mondeB[3] = "1";
    char levelB[3] = "1";
    char pseudoB[50] = "Celian";


    afficherTexte(ecran->largeur/2+margeL + 1, margeH + 3, "+------------------------------------------+");
    afficherTexte(ecran->largeur/2 + margeL + 1, margeH + 4, "| Emplacement de sauvegarde:               |");
    afficherTexte(ecran->largeur / 2 + margeL + 31, margeH + 4, pseudoB);
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 5, "|                                          |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 6, "| monde: -                                 |");
    afficherTexte(ecran->largeur / 2 + margeL + 9, margeH + 6, mondeB);
    afficherTexte(ecran->largeur / 2 + margeL + 11, margeH + 6, levelB);
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 7, "| Distance:    m                           |");
    afficherTexte(ecran->largeur / 2 + margeL + 13, margeH + 7, distanceB);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    if (strcmp("3", vieB) == 0) {
        afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 8, "| vies: [♥][♥][♥]                          |");
    }
    else if (strcmp("2", vieB) == 0) {
        afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 8, "| vies: [♥][♥]                             |");
    }
    else if (strcmp("1", vieB) == 0) {
        afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 8, "| vies: [♥]                                |");
    }
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 9, "| Personnage: Mario                        |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 10, "|                                          |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 11, "| → (Press [2] to Load)                    |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, margeH + 12, "+------------------------------------------+");
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);

    //save slot numero 3
    char distanceC[10] = "100"; // mettre egal aux donne dans le fichier de sauvegarde
    char vieC[5] = "3";
    char mondeC[3] = "1";
    char levelC[3] = "1";
    char pseudoC[50] = "Aylia";

  
    afficherTexte(margeL + 1, ecran->hauteur / 2+margeH+1 , "+------------------------------------------+");
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH +2, "| Emplacement de sauvegarde:               |");
    afficherTexte(margeL + 31, ecran->hauteur / 2 + margeH + 2, pseudoC);
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 3, "|                                          |");
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 4, "| monde: -                                 |");
    afficherTexte(margeL + 9, ecran->hauteur / 2 + margeH + 4, mondeC);
    afficherTexte(margeL + 11, ecran->hauteur / 2 + margeH + 4, levelC);
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 5, "| Distance:    m                           |");
    afficherTexte(margeL + 13, ecran->hauteur / 2 + margeH + 5, distanceC);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    if (strcmp("3", vieC) == 0) {
        afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 6, "| vies: [♥][♥][♥]                          |");
    }
    else if (strcmp("2", vieC) == 0) {
        afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 6, "| vies: [♥][♥]                             |");
    }
    else if (strcmp("1", vieC) == 0) {
        afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 6, "| vies: [♥]                                |");
    }
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 7, "| Personnage: Mario                        |");
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 8, "|                                          |");
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 9, "| → (Press [3] to Load)                    |");
    afficherTexte(margeL + 1, ecran->hauteur / 2 + margeH + 10, "+------------------------------------------+");
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);

    //save slot numero 4
    char distanceD[10] = "50"; // mettre egal aux donne dans le fichier de sauvegarde
    char vieD[5] = "1";
    char mondeD[3] = "1";
    char levelD[3] = "1";
    char pseudoD[50] = "Arthur";


    afficherTexte(ecran->largeur / 2+margeL + 1, ecran->hauteur / 2 + margeH + 1, "+------------------------------------------+");
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 2, "| Emplacement de sauvegarde:               |");
    afficherTexte(ecran->largeur / 2 + margeL + 31, ecran->hauteur / 2 + margeH + 2, pseudoD);
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 3, "|                                          |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 4, "| monde: -                                 |");
    afficherTexte(ecran->largeur / 2 + margeL + 9, ecran->hauteur / 2 + margeH + 4, mondeD);
    afficherTexte(ecran->largeur / 2 + margeL + 11, ecran->hauteur / 2 + margeH + 4, levelD);
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 5, "| Distance:    m                           |");
    afficherTexte(ecran->largeur / 2 + margeL + 13, ecran->hauteur / 2 + margeH + 5, distanceD);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    if (strcmp("3", vieD) == 0) {
        afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 6, "| vies: [♥][♥][♥]                          |");
    }
    else if (strcmp("2", vieD) == 0) {
        afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 6, "| vies: [♥][♥]                             |");
    }
    else if (strcmp("1", vieD) == 0) {
        afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 6, "| vies: [♥]                                |");
    }
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 7, "| Personnage: Mario                        |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 8, "|                                          |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 9, "| → (Press [4] to Load)                    |");
    afficherTexte(ecran->largeur / 2 + margeL + 1, ecran->hauteur / 2 + margeH + 10, "+------------------------------------------+");
    SetConsoleOutputCP(1252);
    SetConsoleCP(1252);



    Sleep(5000);
}