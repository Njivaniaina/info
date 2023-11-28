#include <stdio.h>

#ifndef FAMPISEHOANA
#define FAMPISEHOANA

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

int manisa_andalana_misy(char *lalana);
int tafiditra_ve();
void bara_ambony_tafiditra();
void manajanona_mandefa();
void manomboka_cgi(char *karazany, char *lohateny);
void mamarana_cgi();
void maneo_hafatra(char *lohateny, char *hafatra, char *toerana);
int manisa_andalana(char *baiko);
void mampiseho_tranokala();
char **maka_misy(FILE *misy, int isa);
char **maka_tsy_miasa(char **tranokala, int isa, char **tranokala_miasa, int isa_miasa);

#endif 


