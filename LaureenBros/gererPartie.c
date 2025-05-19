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
#include <tchar.h>

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

int compareScores(const void* a, const void* b) {
    double diff = ((Player*)b)->score - ((Player*)a)->score;
    return (diff > 0) - (diff < 0); // Descending
}

void floatToString(float value, char* buffer, int bufferSize) {
    snprintf(buffer, bufferSize, "%.0f", value);
}

int affichageScore(Ecran* ecran) {
    while (1) {
        while (1) {
            if (!ecran) {
                printf("probleme d'allocation");
                return -1;
            }

            WIN32_FIND_DATA findData;
            HANDLE hFind;
            Player players[MAX_PLAYERS];
            int playerCount = 0;

            hFind = FindFirstFile(_T("saves\\*.txt"), &findData);
            if (hFind == INVALID_HANDLE_VALUE) {
                _tprintf(_T("No save files found.\n"));
                return 0;
            }

            do {
                if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    TCHAR filePath[MAX_PATH];
                    _stprintf_s(filePath, _countof(filePath), _T("saves\\%s"), findData.cFileName);

                    FILE* file = _tfopen(filePath, _T("r"));
                    if (file == NULL) {
                        continue;
                    }

                    double values[100];
                    int count = 0;
                    while (count < _countof(values) && fscanf_s(file, "%lf", &values[count]) == 1) {
                        count++;
                    }
                    fclose(file);

                    if (count < 2) continue;

                    double score = values[0] * values[count - 1];

                    Player p = { 0 };

#ifdef UNICODE
                    char nameBuffer[MAX_NAME_LEN];
                    WideCharToMultiByte(CP_ACP, 0, findData.cFileName + 5, -1,
                        nameBuffer, MAX_NAME_LEN, NULL, NULL);
                    const char* nameStart = nameBuffer;
#else
                    const char* nameStart = findData.cFileName + 5;
#endif
                    size_t nameLen = strcspn(nameStart, ".");
                    if (nameLen >= MAX_NAME_LEN) {
                        nameLen = MAX_NAME_LEN - 1;
                    }
                    strncpy_s(p.name, MAX_NAME_LEN, nameStart, nameLen);
                    p.name[nameLen] = '\0';
                    p.score = (float)score;

                    if (playerCount < MAX_PLAYERS) {
                        players[playerCount++] = p;
                    }
                }
            } while (FindNextFile(hFind, &findData));
            FindClose(hFind);

            qsort(players, playerCount, sizeof(Player), compareScores);

            SetConsoleOutputCP(GetOEMCP());
            SetConsoleCP(GetOEMCP());
            contourEcran(ecran);
            SetConsoleOutputCP(65001);
            SetConsoleCP(65001);

            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 - 3, "╔══════════════════════════════════════════╗");
            afficherTexte(ecran->largeur / 2 - 45 / 2, ecran->hauteur / 4 - 1, "║            TABLEAU DES SCORES :          ║");
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 1, "╚══════════════════════════════════════════╝");
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 3, "════════════════════════════════════════════");
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 4, "║ 🏆 │ Pseudo              │ Score         ║");
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 5, "────────────────────────────────────────────");

            // Ligne 1
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 6, "║ 🥇 │                     │               ║");
            char scoreStr0[20];
            floatToString(players[0].score, scoreStr0, sizeof(scoreStr0));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 6, players[0].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 6, scoreStr0);

            // Ligne 2
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 7, "║ 🥈 │                     │               ║");
            char scoreStr1[20];
            floatToString(players[1].score, scoreStr1, sizeof(scoreStr1));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 7, players[1].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 7, scoreStr1);

            // Ligne 3
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 8, "║ 🥉 │                     │               ║");
            char scoreStr2[20];
            floatToString(players[2].score, scoreStr2, sizeof(scoreStr2));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 8, players[2].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 8, scoreStr2);

            // Ligne 4
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 9, "║ 🎖️ │                     │               ║");
            char scoreStr3[20];
            floatToString(players[3].score, scoreStr3, sizeof(scoreStr3));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 9, players[3].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 9, scoreStr3);

            // Ligne 5
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 10, "║ 🎖️ │                     │               ║");
            char scoreStr4[20];
            floatToString(players[4].score, scoreStr4, sizeof(scoreStr4));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 10, players[4].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 10, scoreStr4);

            // Ligne 6
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 11, "║ 🎖️ │                     │               ║");
            char scoreStr5[20];
            floatToString(players[5].score, scoreStr5, sizeof(scoreStr5));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 11, players[5].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 11, scoreStr5);

            // Ligne 7
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 12, "║ 🎖️ │                     │               ║");
            char scoreStr6[20];
            floatToString(players[6].score, scoreStr6, sizeof(scoreStr6));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 12, players[6].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 12, scoreStr6);

            // Ligne 8
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 13, "║ 🎖️ │                     │               ║");
            char scoreStr7[20];
            floatToString(players[7].score, scoreStr7, sizeof(scoreStr7));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 13, players[7].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 13, scoreStr7);

            // Ligne 9
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 14, "║ 🎖️ │                     │               ║");
            char scoreStr8[20];
            floatToString(players[8].score, scoreStr8, sizeof(scoreStr8));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 14, players[8].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 14, scoreStr8);

            // Ligne 10
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 15, "║ 🎖️ │                     │               ║");
            char scoreStr9[20];
            floatToString(players[9].score, scoreStr9, sizeof(scoreStr9));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 15, players[9].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 15, scoreStr9);

            // Ligne 11
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 16, "║ 🎖️ │                     │               ║");
            char scoreStr10[20];
            floatToString(players[10].score, scoreStr10, sizeof(scoreStr10));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 16, players[10].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 16, scoreStr10);

            // Ligne 12
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 17, "║ 🎖️ │                     │               ║");
            char scoreStr11[20];
            floatToString(players[11].score, scoreStr11, sizeof(scoreStr11));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 17, players[11].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 17, scoreStr11);

            // Ligne 13
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 18, "║ 🎖️ │                     │               ║");
            char scoreStr12[20];
            floatToString(players[12].score, scoreStr12, sizeof(scoreStr12));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 18, players[12].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 18, scoreStr12);

            // Ligne 14
            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 19, "║ 🎖️ │                     │               ║");
            char scoreStr13[20];
            floatToString(players[13].score, scoreStr13, sizeof(scoreStr13));
            afficherTexte(ecran->largeur / 2 - 30 / 2, ecran->hauteur / 4 + 19, players[13].name);
            afficherTexte(ecran->largeur / 2 + 7, ecran->hauteur / 4 + 19, scoreStr13);

            afficherTexte(ecran->largeur / 2 - 44 / 2, ecran->hauteur / 4 + 20, "════════════════════════════════════════════");
            SetConsoleOutputCP(1252);
            SetConsoleCP(1252);
            if (_kbhit()) {
                return 5;
            }
            break;
        }
        break;
    }
    return 0;
}
