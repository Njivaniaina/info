#ifndef HISTORY
#define HISTORY

typedef struct{
  char anarana[256];
  char teny_miafina[256];
  char fanamarinana[256];
} Olona ;

typedef struct {
    char anarana[256];
    char fidirana[256];
    char ip[256];
}   Fidirana ;

typedef struct {
  char ip[15];
  char identite[256];
  char utilisateur[256];
  char date_heure[256];
  char requet[256];
  char stat[10];
  char taille[256];
  char url[256];
  char navigateur[256];
} Information;

int tafiditra_ve();
int maka_nalefa(char *tranokala);
void manomboka_cgi(char *karazany, char *lohateny);
void mamarana_cgi();
void bara_ambony_tafiditra();
int manisa_andalana(char *lalana);
Information *tatarany(char *lalana, int isa);
void mampiseho_tantara(Information *tantara, int isa);

#endif

