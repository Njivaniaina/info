#ifndef INFO
#define INFO

typedef struct Pc{
	char marque[256];
	char nom[256];
	int numero;
	char mac[256];
} Pc ;

typedef struct Personne{
	char nom[256];
	char prenom[256];
	int numero;
	char tel[256];
	char email[256];
	char adresse[256];
	char naissance[256];
	char lieu[256];
	int bacc;
	char genre[256];
	char cin[256];
	char url[256];
} Personne ;

void lire(char *texte);
void copier(Personne *copie, Personne Acopie);
void tri(char texte[256][256], int l);
void trier_nom(Personne *olona, int n);
void trier_prenom(Personne *olona, int n);
void copier_pc(Pc *copie, Pc Acopie);
Pc *tri_num_mac(Pc *pc, int n);
int principal();

#endif