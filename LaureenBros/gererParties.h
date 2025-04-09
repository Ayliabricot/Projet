#ifndef PARTIES_H
#define PARTIES_H

typedef struct {
	char pseudo[30];
	int objet;
	int score;
	int difficulte;
	int vies;
	int x;
	int y;
}Partie;

Partie** creerTableau(void);
void adapterMemoire(Partie** tableau, int nbParties);
Partie* nouvelle_partie(void);

#endif