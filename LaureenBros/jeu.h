#ifndef JEU
#define JEU

typedef struct {
	int x;
	int y;
}Personnage;

typedef struct {
	int x;
	int y;
}Ennemi;

void genererPersonnage(Personnage* personnage, Ecran* ecran);
void genererEnnemi(Ennemi* ennemi, Ecran* ecran);
void deplacementEnnemi(Ennemi* ennemi);

int lancerJeu(int argc, char* argv[]);

#endif