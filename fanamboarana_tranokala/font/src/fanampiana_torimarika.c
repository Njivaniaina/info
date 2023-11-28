#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fanampiana_torimarika.h"

int main(int argc, char **argv){
  Torimarika torimarika={"/home/njiva/sites/Fanamboarana_tranokala/",{ "Options +ExecCGI", "", "", "", "", "", "", "", "", ""}};
  
  manomboka_cgi("html", "Fandraketana ilay torimarika.");

  mametraka_torimarika("./andrana.conf", &torimarika, 1);

  mamarana_cgi();

  return 0;
}

void manomboka_cgi(char *karazany, char *lohateny){
	printf(	"Context-Type:text/%s\n\n"
		"<!DOCTYPE html>\n"
		"<html>\n"
		"<head>\n"
		"	<meta charset=\"UTF-8\" />\n"
		"	<title>%s</title>\n"
		"	<link rel=\"stylesheet\" href=\"http://www.config.mg/style.css\">\n"
		"</head>\n"
		"<body>\n"
		, karazany, lohateny);
}

void mamarana_cgi(){
	printf(	"</body>\n"
		"</html> \n"
	      );
}

int manisa_andalana(char *lalana){
  FILE *misy=NULL;
  char teny[1000];
  int n=0;

  misy = fopen(lalana, "r");
  if(misy){
    while (fgets(teny, 1000, misy)) {
      n++;
    }
    fclose(misy);
  }
  return n;
}

char **maka_andalana_rehetra(char *lalana, int isa){
  char **teny;
  FILE *misy=NULL;

  teny = (char**)malloc(sizeof(char*)*isa);
  for(int i=0;i<isa;i++){
    teny[i] = (char*)malloc(256);
  }

  misy = fopen(lalana, "r");
  if(misy){
    for(int i=0;fgets(teny[i], 256, misy);i++);
    fclose(misy);
  }

  return teny;
}

void mametraka_torimarika(char *lalana, Torimarika *torimarika, int isa){
  FILE *misy=NULL;
  int isa_andalana=0;
  char **teny;
  int n=0, m=0;

  isa_andalana = manisa_andalana(lalana);
  teny = maka_andalana_rehetra(lalana, isa_andalana);

  misy = fopen(lalana, "w");
  if(misy){
    while (n<isa_andalana) {
      fprintf(misy, "%s", teny[n]);
      if(strstr(teny[n] , "DocumentRoot")){
        m++;
      }

      if(m == 1){
        for(int i=0;i<isa;i++){
          fprintf(misy, "\n\t<Directory %s>\n", torimarika[i].toerana);
          for(int j=0;j<10;j++){
            if(strcmp(torimarika[i].torimarika[j], "")){
              fprintf(misy, "\t\t%s\n", torimarika[i].torimarika[j]);
            }
          }
          fprintf(misy, "\t</Directory>\n");
        }
        m++;
      }

      n++;
    }

    fclose(misy);
  }
  else {
    printf("<h1>Erreur lors de l'ouverture du fichier %s</h1>\n", lalana);
  }
}
