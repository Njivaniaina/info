#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fanoratana_anarana.h"

int main(int argc, char **argv){
  Olona olona;

  manomboka_cgi("html", "Fanoratana anarana");

  if(tafiditra_ve()){
		printf("<meta http-equiv=\"refresh\" content=\"0; http://www.tranokala.mg/cgi/fampisehoana.cgi\">\n");
  }
  else{
    bara_ambony();
    if(nanoratra_anarana_ve(&olona)){
      mametraka(olona);
    }
    else{
      fisoratana_anarana();
    }
  }

  mamarana_cgi();

  return 0;
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

void bara_ambony(){
    printf( "<header>\n"
            "    <a href=\"#\" class=\"\">Mon site</a>\n"
            "    <div class=\"navigation\">\n"
            "        <div class=\"\">\n"
            "            <a href=\"http://www.tranokala.mg/cgi/fanoratana_anarana.cgi\">S'inscrire</a>\n"
            "            <a href=\"http://www.tranokala.mg/cgi/fidirana.cgi\">Se connecter</a>\n"
            "        </div>\n"
            "    </div>\n"
            "</header>\n"
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

void fisoratana_anarana(){
    printf( "<div class=\"\">\n"
            "         <form action=\"http://www.tranokala.mg/cgi/fanoratana_anarana.cgi\" method=\"get\">\n"
            "             <h1>Inscription</h1>\n"
            "             <input type=\"text\" name=\"anarana\" placeholder=\"Login\" class=\"text\"/><br>\n"
            "             <input type=\"password\" name=\"teny_miafina\" placeholder=\"Mot de passe\" class=\"text\" /><br>\n"
            "             <input type=\"password\" name=\"teny_miafina1\" placeholder=\"Retaper le mot de passe\" class=\"text\"/><br>\n"
            "             <input type=\"submit\" value=\"S'inscrire\" class=\"valider\">\n"
            "          </form>\n"
            "    </div>\n"
    );
}

int manisa_andalana(char *lalana){
  FILE *misy =NULL;
  char teny[1000];
  int isa=0;

  misy = fopen(lalana, "r");
  if(misy){
    while(fgets(teny, 1000, misy)){
      isa++;
    }
    fclose(misy);
  }
  return isa;
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

int nanoratra_anarana_ve(Olona *olona){
  char *teny = NULL;

  strcpy(olona->anarana, "");
  strcpy(olona->teny_miafina, "");
  strcpy(olona->fanamarinana, "");
  
  teny = getenv("QUERY_STRING");
  if(teny){
    sscanf(teny, "anarana=%[^&]&teny_miafina=%[^&]&teny_miafina1=%s", olona->anarana, olona->teny_miafina, olona->fanamarinana);
  }
  if(!strcmp(olona->anarana, "")){
    return 0;
  }
  return 1;
}

int maka_olona_misy(FILE *misy, Olona *o, int isa_andalana){
    char teny[500];
    if(isa_andalana>0){
        for(int i=0;i<isa_andalana;i++){
            fgets(teny, 500, misy);
            sscanf(teny, "%[^;];%s", o[i].anarana, o[i].teny_miafina);
        }
    }
    else{
        return 0;
    }
    return 1;
}

void maneo_hafatra(char *lohateny, char *hafatra){
  printf("<h1>%s</h1>\n", lohateny);
  printf("<p>%s</p>\n", hafatra);
}

int mametraka(Olona olona){
    int isa_andalana=0, efa_misy=0;
    FILE *misy=NULL;
    Olona *o;
    
    if(!strcmp(olona.teny_miafina, olona.fanamarinana)){
      isa_andalana = manisa_andalana("./user.conf");
      misy = fopen("./user.conf", "a+");
      if(misy != NULL){
          o = (Olona*)malloc(isa_andalana*sizeof(Olona));
          if(isa_andalana>0){
              maka_olona_misy(misy, o, isa_andalana);
              for(int i=0;i<isa_andalana;i++){
                  if(!strcmp(o[i].anarana, olona.anarana)){
                      efa_misy=1;
                  }
              }
          }
          if(efa_misy){
             maneo_hafatra("Erreur de l'écriture!","L'écriture dans le fichier a échoué : il existe déjà une utilisateur qui a ce Login.");
              return 0;
          }
          else{
              fprintf(misy, "%s;%s\n", olona.anarana, olona.teny_miafina);
              maneo_hafatra("Inscription terminé!", "L'inscription a été faite avec succes.");
          }

        fclose(misy);
      }
      else{
        maneo_hafatra("Erreur d'ouverture.", "L'ouverture de fichier a echoué .");
      }
    }
    else{
      maneo_hafatra("Erreur de l'inscription.", "L'inscription a echoué car les deux mot de passe ne sont pas identique.");
    }
    return 1;
}
