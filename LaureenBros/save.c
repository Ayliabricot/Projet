#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"
#include "gererParties.h"

cJSON* creer_JSON(Partie* partie) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "pseudo", partie->pseudo);
    // pour ajouter un objet à jSON commade avec le type de variable avec (struct json, nom variable, nom variable à vouloir etre partie)
    cJSON_AddNumberToObject(root, "objet", partie->objet);
    cJSON_AddNumberToObject(root, "score", partie->score);
    cJSON_AddNumberToObject(root, "difficulte", partie->difficulte);
    cJSON_AddNumberToObject(root, "vies", partie->vies);
    cJSON_AddNumberToObject(root, "x", partie->x);
    cJSON_AddNumberToObject(root, "y", partie->y);
    return root;
}
int extraire_from_JSON(cJSON* root, Partie* partie) {
    if (!root) {
        return 0;
    }
    if (!partie) {
        return 0;
    }
    // Récupération du champ "pseudo" depuis l'objet JSON 
    cJSON* pseudo = cJSON_GetObjectItem(root, "pseudo");
    if (cJSON_IsString(pseudo)) {
        strcpy_s(partie->pseudo, 50, pseudo->valuestring);
    }
    else {
        return 0;
    }
    cJSON* objet = cJSON_GetObjectItem(root, "objet");

    if (cJSON_IsNumber(objet)) {

        partie->objet = objet->valueint;
    }
    else {
        return 0;
    }


    cJSON* score = cJSON_GetObjectItem(root, "score");
    if (cJSON_IsNumber(score)) {
        partie->score = score->valueint;
    }
    else {
        return 0;
    }


    cJSON* difficulte = cJSON_GetObjectItem(root, "difficulte");
    if (cJSON_IsNumber(difficulte)) {
        partie->difficulte = difficulte->valueint;
    }
    else {
        return 0;
    }


    cJSON* vies = cJSON_GetObjectItem(root, "vies");
    if (cJSON_IsNumber(vies)) {
        partie->vies = vies->valueint;
    }
    else {
        return 0;
    }


    cJSON* x = cJSON_GetObjectItem(root, "x");
    if (cJSON_IsNumber(x)) {
        partie->x = x->valueint;
    }
    else {
        return 0;
    }

    cJSON* y = cJSON_GetObjectItem(root, "y");
    if (cJSON_IsNumber(y)) {
        partie->y = y->valueint;
    }
    else {
        return 0;
    }

    return 1;
}
int sauvegarder_partie(Partie* partie, const char* nom_fichier) {
    cJSON* root = creer_JSON(partie);
    if (!root) {
        return 0;
    }

    char* json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return 0;
    }

    // Open in binary mode
    FILE* fichier = fopen(nom_fichier, "wb");
    if (!fichier) {
        free(json_string);
        cJSON_Delete(root);
        return 0;
    }

    // Get the actual length for more accurate error checking
    size_t len = strlen(json_string);
    size_t written = fwrite(json_string, 1, len, fichier);

    fclose(fichier);
    free(json_string);
    cJSON_Delete(root);

    return (written == len) ? 1 : 0;
}


int charger_partie(Partie* partie, const char* nom_fichier) {
    // Open in binary mode to avoid text translation issues
    FILE* fichier = fopen(nom_fichier, "rb");
    if (!fichier) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return 0;
    }

    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    // Allocate buffer for the entire file
    char* json_data = (char*)malloc(taille + 1);
    if (!json_data) {
        fclose(fichier);
        return 0;
    }

    // Read the file
    size_t lu = fread(json_data, 1, taille, fichier);
    fclose(fichier);

    // Even if we didn't read the exact number of bytes, try to process what we have
    json_data[lu] = '\0'; // Null-terminate what we've read

    cJSON* root = cJSON_Parse(json_data);
    free(json_data);

    if (!root) {
        return 0;
    }

    int resultat = extraire_from_JSON(root, partie);
    cJSON_Delete(root);
    return resultat;
}

//
//int main() {
//    Partie partie;
//    char choix;
//    const char* nom_fichier = "sauvegarde.txt";
//
//    printf("===== GESTION DE PARTIE =====\n\n");
//
//    // Tenter de charger une sauvegarde existante
//    if (charger_partie(&partie, nom_fichier)) {
//        printf("Sauvegarde trouvée et chargée avec succès!\n\n");
//
//        // Afficher les données chargées
//        printf("Données de la partie chargée:\n");
//        printf("Pseudo: %s\n", partie.pseudo);
//        printf("Objet: %d\n", partie.objet);
//        printf("Score: %d\n", partie.score);
//        printf("Difficulté: %d\n", partie.difficulte);
//        printf("Vies: %d\n", partie.vies);
//        printf("Position: (%d, %d)\n\n", partie.x, partie.y);
//    }
//    else {
//        printf("Aucune sauvegarde trouvée ou erreur lors du chargement.\n");
//        printf("Initialisation d'une nouvelle partie...\n\n");
//
//        // Initialiser avec des valeurs par défaut
//        strcpy_s(partie.pseudo, 50, "Joueur");
//        partie.objet = 0;
//        partie.score = 0;
//        partie.difficulte = 1;
//        partie.vies = 3;
//        partie.x = 0;
//        partie.y = 0;
//    }
//
//    // Menu de modification
//    do {
//        printf("\n===== MENU =====\n");
//        printf("1. Modifier le pseudo\n");
//        printf("2. Modifier l'objet\n");
//        printf("3. Modifier le score\n");
//        printf("4. Modifier la difficulté\n");
//        printf("5. Modifier les vies\n");
//        printf("6. Modifier la position (x,y)\n");
//        printf("7. Afficher les données actuelles\n");
//        printf("8. Sauvegarder et quitter\n");
//        printf("9. Quitter sans sauvegarder\n");
//        printf("Votre choix: ");
//        scanf_s(" %c", &choix, 1);
//
//        switch (choix) {
//        case '1':
//            printf("Nouveau pseudo: ");
//            scanf_s("%49s", partie.pseudo, (unsigned)_countof(partie.pseudo));
//            break;
//
//        case '2':
//            printf("Nouvel objet (entier): ");
//            scanf_s("%d", &partie.objet);
//            break;
//
//        case '3':
//            printf("Nouveau score: ");
//            scanf_s("%d", &partie.score);
//            break;
//
//        case '4':
//            printf("Nouvelle difficulté (1-3): ");
//            scanf_s("%d", &partie.difficulte);
//            break;
//
//        case '5':
//            printf("Nombre de vies: ");
//            scanf_s("%d", &partie.vies);
//            break;
//
//        case '6':
//            printf("Position X: ");
//            scanf_s("%d", &partie.x);
//            printf("Position Y: ");
//            scanf_s("%d", &partie.y);
//            break;
//
//        case '7':
//            printf("\nDonnées actuelles:\n");
//            printf("Pseudo: %s\n", partie.pseudo);
//            printf("Objet: %d\n", partie.objet);
//            printf("Score: %d\n", partie.score);
//            printf("Difficulté: %d\n", partie.difficulte);
//            printf("Vies: %d\n", partie.vies);
//            printf("Position: (%d, %d)\n", partie.x, partie.y);
//            break;
//
//        case '8':
//            if (sauvegarder_partie(&partie, nom_fichier)) {
//                printf("\nPartie sauvegardée avec succès dans %s\n", nom_fichier);
//                printf("À bientôt!\n");
//            }
//            else {
//                printf("\nErreur lors de la sauvegarde!\n");
//            }
//            break;
//
//        case '9':
//            printf("\nQuitter sans sauvegarder. À bientôt!\n");
//            break;
//
//        default:
//            printf("\nOption invalide. Veuillez réessayer.\n");
//        }
//
//    } while (choix != '8' && choix != '9');
//
//    return 0;
//}