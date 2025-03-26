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

void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour afficher un texte à une position donnée
void afficherTexte(int x, int y, const char* texte) {
    gotoxy(x, y);
    printf("%s", texte);
}
void afficherTexteHighlight(int x, int y, const char* texte) {
    gotoxy(x, y);
    printf("\x1b[30m\x1b[47m %s \x1b[0m", texte);
}

