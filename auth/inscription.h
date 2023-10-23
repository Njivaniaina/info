#include <stdio.h>
#ifndef INSCRIPTION
#define INSCRIPTION

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
int ao_ve();
void manomboka_cgi(char *karazany, char *css);
void bar_abony();
void bar_abony_ao();
void fenoina();
void mamarana_cgi();
int maka_mombamomba(Olona *o);
int mandray(Olona user);
int tsy_mitovy();
void voaray();
int mandray_olona(Olona user);
int manisa_andalana(FILE *fichier);
int maka_olona_misy(FILE *fichier, Olona *u, int n);
int manoratra(FILE *fichier, Olona user);
void tsy_voaray(char *diso);

#endif