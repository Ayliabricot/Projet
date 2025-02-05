#include <windows.h>
#include <stdio.h>


int main() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width, height;

    // R�cup�rer les infos de la console
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        printf("Taille de la fen�tre de la console : %d colonnes x %d lignes\n", width, height);
    }
    else {
        printf("Erreur : Impossible de r�cup�rer la taille de la console.\n");
    }

    return 0;
}