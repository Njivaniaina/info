#include <stdio.h>

#ifndef FIDIRANA
#define FIDIRANA

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

void maneo_hafatra(char *lohateny, char *hafatra);
int miala_na_tsia();
int tafiditra_ve();
void manomboka_cgi(char *karazany, char *lohateny);
void mamarana_cgi();
void bara_ambony();
void bara_ambony_tafiditra();
void famenoana_fidirana();
int manisa_andalana(char *lalana);
int maka_nalefa(Olona *o);
int maka_olona_misy(FILE *misy, Olona *o, int isa_andalana);
int manamarina(Olona olona);
int tafiditra(Olona olona);

#endif
