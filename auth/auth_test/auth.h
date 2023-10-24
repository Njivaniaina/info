#include <stdio.h>

#ifndef AUTH
#define AUTH
    
typedef struct {
    char date[256];
    char time[256];
    char session[256];
    char user[256];
}   User ;

int manisa_andalana(FILE *fichier);
User *maka(long *n);
int mitady_ve(User *u, User *v, long *n, char *tadiavina);
void fitadiavana();
int laharany_pejy();
void mampiseho(User *user, long n, long a, long b, char *tadiavina);
void mamarana_cgi();
void manomboka_cgi(char *karazany, char *css);
char *daty(char *date);

#endif
