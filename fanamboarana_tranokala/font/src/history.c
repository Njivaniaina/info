#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

int main(int argc, char **argv){
  Information *tantara;
  int isa_andalana=0;
  char tranokala[256]="";
  char teny[500]="";

  manomboka_cgi("html", "Historique");
  maka_nalefa(tranokala);

  if(tafiditra_ve()){
		bara_ambony_tafiditra();
    if(strcmp(tranokala, "")){
      sprintf(teny, "/var/log/apache2/%s", tranokala);
      isa_andalana = manisa_andalana(teny);
      tantara = tatarany(teny, isa_andalana);
      printf("<h1>Le fichier %s</h1>\n", teny);
      mampiseho_tantara(tantara, isa_andalana);
    }
    else {
      printf("<h1>Il n'y a pas d'historique pour ce site.</h1>\n");
    }
  }
  else{
    printf("<meta http-equiv=\"refresh\" content=\"0; http://www.tranokala.mg/cgi/fidirana.cgi\">\n");
  }

  mamarana_cgi();

  return 0;
}

int tafiditra_ve(){
    int isa_andalana=0, ao=0;
    Fidirana *olona;
    FILE *misy=NULL;
    char teny[500];
    char *ip = getenv("REMOTE_ADDR");

    isa_andalana = manisa_andalana("./login.conf");
    
    misy = fopen("./login.conf", "r");
    if(misy != NULL){
        olona = (Fidirana*)malloc(isa_andalana*sizeof(Fidirana));

        for(int i=0;i<isa_andalana;i++){
            fgets(teny, 500, misy);
            sscanf(teny, "%[^;];%[^;];%s", olona[i].anarana, olona[i].fidirana, olona[i].ip);
      }
        for(int i=0;i<isa_andalana;i++){
            if(!strcmp(ip, olona[i].ip)){
                ao=1;
            }
        }

        fclose(misy);
    }
    else{
        printf("<h1>Misy olana eo amin'ny famakiana ilay fidirana.</h1>");
    }
    return ao;
}

int maka_nalefa(char *tranokala){
  char *teny = NULL;

  teny = getenv("QUERY_STRING");
  if(teny){
    if(strstr(teny, "tranokala=")){
      sscanf(teny, "tranokala=%s", tranokala);
    }
  }
  else{
    return 0;
  }
  return 1;
}

void manomboka_cgi(char *karazany, char *lohateny){
    printf("Context-Type:text/%s\n\n", karazany);

    printf( "<!DOCTYPE html>\n"
            "<html lang=\"mg\">\n"
            "<head>\n"
            "   <meta charset=\"UTF-8\">\n"
            "   <title>%s</title>\n"
            "</head>\n"
            "<body>\n"
    , lohateny);
}

void mamarana_cgi(){
    printf( "</body>\n"
            "</html>\n"
    );
}

void bara_ambony_tafiditra(){
    printf( "<header>\n"
            "    <a href=\"#\" class=\"\">Mon site</a>\n"
            "    <div class=\"navigation\">\n"
            "        <div class=\"\">\n"
            "            <a href=\"http://www.tranokala.mg/cgi/fampisehoana.cgi\">Les sites</a>\n"
            "            <a href=\"http://www.tranokala.mg/cgi/famenoana.cgi\">Creation de sites</a>\n"
            "            <a href=\"http://www.tranokala.mg/cgi/fidirana.cgi?logout=1\">Se deconnecter</a>\n"
            "        </div>\n"
            "    </div>\n"
            "</header>\n"
    );
}


int manisa_andalana(char *lalana){
  int isa=0;
  char teny[500]="";
  FILE *misy = NULL;

  misy = fopen(lalana, "r");
  if(misy){
    while(fgets(teny, 500, misy)){
      isa++;
    }
    fclose(misy);
  }
  else {
    printf("<h1>Erreur de l'ouveture du misy %s</h1>\n", lalana);
  }
  return isa;
}

Information *tatarany(char *lalana, int isa){
  Information *tantara;
  FILE *misy=NULL;
  int i=0;
  char text[500];

  tantara = (Information*)malloc(sizeof(Information)*isa);

  misy = fopen(lalana, "r");
  if(misy){
    while (fgets(text, 500, misy)){
      sscanf(text,
             "%s %s %s [%[^]]] \"%[^\"]\" %s %s \"%[^\"]\" \"%[^\"]\"", 
             tantara[i].ip, tantara[i].identite, tantara[i].utilisateur, tantara[i].date_heure, tantara[i].requet, tantara[i].stat, tantara[i].taille, tantara[i].url, tantara[i].navigateur
             );
      i++;
    }
    fclose(misy);
  }
  else {
    printf("<h1>Impossible d'ouvire le misy %s</h1>\n", lalana);
  }
  return tantara;
}

void mampiseho_tantara(Information *tantara, int isa){
  printf("<table border=\"3\">\n");
  printf("<tr><td>IP</td><td>Identité</td><td>Utilisateur</td><td>Date et heure</td><td>Requette</td><td>status</td><td>Taille du requette</td><td>URL</td><td>Navigateur</td></tr>\n");
    
  for(int i=0;i<isa;i++){
    printf(
          "<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>\n", 
            tantara[i].ip, tantara[i].identite, tantara[i].utilisateur, tantara[i].date_heure, tantara[i].requet, tantara[i].stat, tantara[i].taille, tantara[i].url, tantara[i].navigateur
    );
  }
  printf("</table>\n");
}
