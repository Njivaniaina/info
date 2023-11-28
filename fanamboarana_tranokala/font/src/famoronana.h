#ifndef FAMORONANA
#define FAMORONANA

typedef struct {
  char mahakasika[256];
	char tranokala[256];
	char tompony[256];
	char toerana[256];
  int cgi;
} Tranokala ;

typedef struct {
  char toerana[256];
  char torimarika[4][256];
} Torimarika;

void manomboka_cgi(char *karazany, char *lohateny);
void mamarana_cgi();
int manoratra_torimarika(char *lalana, Tranokala tranokala);
Tranokala maka_mahakasika();
void maneo_hafatra(char *lohateny, char *hafatra, char *toerana);
int manisa_andalana(char *lalana);
char **maka_analana_rehetra(char* lalana, int isa);
void mametraka_torimarika(char *lalana, Torimarika *torimarika, int isa);

#endif // !FAMORONANA
