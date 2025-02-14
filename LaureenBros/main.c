

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include "placementTexte.h"
#include <time.h>


int main() {
    Ecran* ecran = definirEcran();  
    int touche = 0; 
    int* choix = malloc(sizeof(int));
    if (choix == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }
    *choix = 2;
   
    
    afficherMenu(ecran, touche, choix);

    while (1) {  
        if (_kbhit()) {  
            touche = _getch();  

          
            system("cls");
            afficherMenu(ecran, touche, choix);
        }

         
    }
    free(choix);
    return 0;
}


















//int main() {
//
//	Ecran* ecran = definirEcran();
//
//	while (1) {
//
//		if (_kbhit()) {
//
//			int touche = _getch();
//			system("cls");
//			afficherMenu(ecran, touche);
//		}
//		else {
//			afficherMenu(ecran, 0);
//			Sleep(5000);
//			system("cls");
//		}
//
//
//		
//	}
//
//	return 0;
//
//
//	
//
//}