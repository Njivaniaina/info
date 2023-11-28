#ifndef FANAMPIANA_TORIMARIKA
#define FANAMPIANA_TORIMARIKA

typedef struct {
  char toerana[256];
  char torimarika[10][256];
} Torimarika;

void manomboka_cgi(char *karazany, char *lohateny);
void mamarana_cgi();

int manisa_andalana(char *lalana);
char **maka_andalana_rehetra(char *lalana, int isa);
void mametraka_torimarika(char *lalana, Torimarika *torimarika, int isa);

#endif // !FANAMPIANA_TORIMARIKA
