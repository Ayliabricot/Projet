#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include <unistd.h>



void afficherMenu() {
    printf( "\n**\n");
    printf("                 LAUREEN BROS            \n");
    printf("**\n" );
    printf( "1. Entre le pseudo du joueur\n");
    printf("2. Choisir difficulte\n");
    printf("3. Nouvelle partie\n");
    printf("4. Continuer partie\n");
    printf("5. Acceder au tableau des scores\n");
    printf("6. Quitter le jeu\n" );
    printf( "**\n" );
    printf("\nChoisissez une option : ");
}

void chargement() {
    printf( "\n\nChargement en cours...\n" );
    printf( "[" );
    for (int i = 0; i < 50; i++) {
        printf( "#" );
        fflush(stdout);
        Sleep(50); // Délai réduit pour un effet plus fluide
    }
    printf( "]\n" );
    printf( "\nChargement termine !\n\n" );
}

int main() {
    char pseudo[50];
    int difficulte = 1;

    printf( "\n\n\n\n\n\n\n\n\n\n                **\n");
    printf("                                 LAUREEN BROS            \n");
    printf("                **\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
    printf( "CHARGEMENT ...\n" );
    printf("Appuyez sur Espace pour commencer le chargement.\n");

    while (getchar() != ' ') {}

    chargement();

    int choix;
    do {
        afficherMenu();
        scanf_s("%d", &choix);
        getchar();
        switch (choix) {
        case 1:
            printf("\nEntrez votre pseudo : ");
            fgets(pseudo, sizeof(pseudo), stdin);
            pseudo[strcspn(pseudo, "\n")] = 0;
            printf( "\nBienvenue, %s !\n\n" , pseudo);
            break;
        case 2:
            printf("\nSelectionnez la difficulté :\n");
            printf( "1. Facile\n2. Normal\n3. Difficile\n" );
            printf("\nVotre choix : ");
            scanf_s("%d", &difficulte);
            getchar();

            if (difficulte < 1 || difficulte > 3) {
                printf( "\nChoix invalide, la difficulté est réglée sur Normal.\n" );
                difficulte = 2;
            }
            else {
                printf( "\nDifficulté sélectionnée : %s\n\n" ,
                    difficulte == 1 ? "Facile" : (difficulte == 2 ? "Normal" : "Difficile"));
            }
            break;
        case 3:
            printf( "\nNouvelle partie sélectionnee. La partie va commencer...\n\n" );
            chargement();
            break;
        case 4:
            printf( "\nContinuer partie sélectionnee.\n\n" );
            break;
        case 5:
            printf( "\nAcces au tableau des scores.\n\n" );
            break;
        case 6:
            printf( "\nVous avez choisi de quitter le jeu. Au revoir !\n" );
            break;
        default:
            printf( "\nOption invalide, veuillez réessayer.\n\n" );
            break;
        }
    } while (choix != 6);

    return 0;
}