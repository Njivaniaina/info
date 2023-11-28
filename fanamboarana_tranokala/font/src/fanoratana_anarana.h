#include <stdio.h>

#ifndef FANORATANA_ANARANA
#define FANORATANA_ANARANA

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

void manomboka_cgi(char *karazany, char *lohateny);
void mamarana_cgi();
void bara_ambony();
void bara_ambony_tafiditra();
void fisoratana_anarana();
int manisa_andalana(char *lalana);
int tafiditra_ve();
int nanoratra_anarana_ve(Olona *olona);
int maka_olona_misy(FILE *misy, Olona *o, int isa_andalana);
void maneo_hafatra(char *lohateny, char *hafatra);
int mametraka(Olona olona);

#endif
