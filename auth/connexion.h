#include <stdio.h>
#ifndef CONNEXION
#define CONNEXION

typedef struct {
    char login[256];
    char passwd[256];
    char passwd0[256];
} Olona ;

typedef struct {
    char login[256];
    char status[256];
    char ip[256];
}   Login ;

int miala();
void manomboka_cgi(char *karazany, char *css);
void mamarana_cgi();
void bar_abony();
void bar_abony_ao();
int ao_ve();
void fenoina();
void tsy_misy();
int manisa_andalana(FILE *fichier);
int maka_olona_misy(FILE *fichier, Olona *u, int n);
int maka_nalefa(Olona *o);
int mandray(Olona user);
void voaray();
void diso();
int manamarina(Olona user);
int connecter(Olona user);

#endif