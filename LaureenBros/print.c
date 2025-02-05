#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void afficherMenu() {
    printf("\n\n\n\n\n\n             *****  LAUREEN   BROS  *****");
    printf("1. Entre le pseudo du joueur\n");
    printf("2. Choisir difficulte\n");
    printf("3. Nouvelle partie\n");
    printf("4. Continuer partie\n");
    printf("5. Acceder au tableau des scores\n");
    printf("6. Quitter le jeu\n \n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\nChoisissez une option : ");
}

int main() {
    char pseudo[50];
    int difficulte = 1;

    printf("\n\n\n\n\n\n             *****  LAUREEN   BROS  *****\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("CHARGEMENT ...\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Appuyez sur Espace pour commencer le chargement.\n");

    while (getchar() != ' ') {}

    int i;
    int total = 50;
    printf("\n[");
    for (i = 0; i < total; i++) {
        printf(" ");
    }
    printf("]");

    printf("\r[");

    for (i = 0; i <= total; i++) {
        printf("#");
        fflush(stdout);
        usleep(100000);
    }

    printf("]\n");
    printf("\n             ***** Chargement termine ! *****\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    int choix;
    do {
        afficherMenu();
        scanf("%d", &choix);
        getchar();

        switch (choix) {
        case 1:
            printf("\nEntrez votre pseudo : ");
            fgets(pseudo, sizeof(pseudo), stdin);
            pseudo[strcspn(pseudo, "\n")] = 0;
            printf("\nBienvenue, %s !\n", pseudo);
            break;
        case 2:
            printf("\nSelectionnez la difficulte :\n");
            printf("1. Facile\n");
            printf("2. Normal\n");
            printf("3. Difficile\n");
            printf("\nVotre choix : ");
            scanf("%d", &difficulte);
            getchar();

            if (difficulte < 1 || difficulte > 3) {
                printf("\nChoix invalide, la difficulte est reglee sur Normal.\n");
                difficulte = 2;
            }
            else {
                printf("\nDifficulte selectionnee : %s\n",
                    difficulte == 1 ? "Facile" : (difficulte == 2 ? "Normal" : "Difficile"));
            }
            break;
        case 3:
            printf("\nVous avez choisi : Nouvelle partie, la partie va debute...\n\n CHARGEMENT ...");
            break;
        case 4:
            printf("\nVous avez choisi : Continuer partie\n");
            break;
        case 5:
            printf("\nVous avez choisi : Accéder au tableau des scores\n");
            break;
        case 6:
            printf("\nVous avez choisi de quitter le jeu. Au revoir !");
            break;
        default:
            printf("\nOption invalide, veuillez réessayer.\n");
            break;
        }
    } while (choix != 6);

    return 0;
}