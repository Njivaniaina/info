#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fakana.h"

int main(int argc, char **argv){
  Torimarika *t;
  int isa=0;

  isa = manisa_torimarika("./andrana.conf");
  t = maka_torimarika("./andrana.conf", isa);
  mampiseho(t, isa);

  return 0;
}

int manisa_torimarika(char *lalana){
  int n=0;
  char teny[255];
  FILE *misy=NULL;

  misy = fopen(lalana, "r");
  if(misy){
    while(fgets(teny, 255, misy)){
      if(strstr(teny, "<Directory ")){
        n++;
      }
    }
    fclose(misy);
  }
  else{
    printf("Erreur de l'ouverture du fichier.\n");
  }
  return n;
}

Torimarika *maka_torimarika(char *lalana, int isa){
  Torimarika *t;
  int m=0;
  int i=0, j=0;
  char teny[255];
  FILE *misy = NULL;

  t = (Torimarika *)malloc(sizeof(Torimarika)*isa);
  misy = fopen(lalana, "r");
  if(misy){
    while(fgets(teny, 255, misy)){
      if(strstr(teny, "\t<Directory ")){
        m=1;
        sscanf(teny, "\t<Directory %[^>]", t[i].toerana);
        fgets(teny, 255, misy);
      }
      if(m){
        j=0;
        while(NULL == strstr(teny, "</Directory>")) {
          sscanf(teny, "%[^\n]", t[i].torimarika[j]);
          fgets(teny, 255, misy);
          j++;
        }
        m=0;
        i++;
      }   
    }
    fclose(misy);
  }
  else{
    printf("Erreur lors de l'ouverture du fichier dans le 2eme.\n");
  }

  return t;
}

void mampiseho(Torimarika *t, int isa){
  for(int i=0;i<isa;i++){
    printf("\t%s:\n", t[i].toerana);
    for(int j=0;j<5;j++){
      if(strcmp(t[i].torimarika[j], ""))
        printf("%s\n", t[i].torimarika[j]);
    }
  }
}
