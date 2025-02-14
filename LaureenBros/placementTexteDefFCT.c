#include <windows.h>
#include <stdio.h>

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour afficher un texte � une position donn�e
void afficherTexte(int x, int y, const char* texte) {
    gotoxy(x, y);
    printf("%s", texte);
}
void afficherTexteHighlight(int x, int y, const char* texte) {
    gotoxy(x, y);
    printf("\x1b[30m\x1b[47m %s \x1b[0m", texte);
}

