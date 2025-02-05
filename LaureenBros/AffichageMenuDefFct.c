#include <windows.h>
#include <stdio.h>
#include "ecran.h"

void contourEcran(Ecran* ecran) {
	tailleEcran(ecran);
	char c = 219;
	int largeur = ecran->largeur - 1;
	int hauteur = ecran->hauteur - 1;
	for (int i = 0; i < ecran->hauteur; i++) {
		for (int j = 0; j < ecran->largeur; j++) {
			if ((i == 0 || i == hauteur)) {
				printf("%c",c);
			}
			else if (j == 0 || j == largeur) {
				printf("%c",c);
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}


//int main() {
//	Ecran* ecran = definirEcran();
//	while (1) {
//
//
//		contourEcran(ecran);
//		Sleep(500);
//		system("cls");
//	}
//
//	return 0;
//}


