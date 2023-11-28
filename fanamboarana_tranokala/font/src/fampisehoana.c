#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fampisehoana.h"

int main(int argc, char **argv){
  
  manomboka_cgi("html", "Liste des sites disponibles");
  
  if(tafiditra_ve()){
    bara_ambony_tafiditra();
    manajanona_mandefa();
    mampiseho_tranokala();
  }
  else {
    printf("<meta http-equiv=\"refresh\" content=\"0; URL=http://www.tranokala.mg/cgi/fidirana.cgi\">\n");
  }

  mamarana_cgi();

  return 0;
}

int manisa_andalana_misy(char *lalana){
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

    isa_andalana = manisa_andalana_misy("./login.conf");
    
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

void manajanona_mandefa(){
  char *hafatra;
  char tranokala[100]="", baiko[156]="";
  int m=0;
  FILE *b = NULL;
  FILE *r = NULL;

  hafatra = getenv("QUERY_STRING");
  if(hafatra){
    sscanf(hafatra, "tsy_miasa=%d&tranokala=%s", &m, tranokala);
    if(strcmp(tranokala, "")){
      if(m){
        sprintf(baiko, "sudo a2ensite %s", tranokala);
        b = popen(baiko, "r");
        if(b){
          r = popen("sudo systemctl reload apache2", "r");
          if(r){
            pclose(r);
          }
          else{
            printf("<h1>Misy olana eo amin'ilay famerenana ilay apache2 (1)</h1>\n");
          }
          pclose(b);
        }
        else{
          printf("<h1>Misy olana eo amin'ny fanaovana ilay fandefasana ilay torimarika.</h1>\n");
        }


 //       system("sudo systemctl reload apache2");
        printf("<h1>Vita ilay baiko!!!</h1>\n");
        printf("<meta http-equiv=\"refresh\" content=\"0; http://www.tranokala.mg/cgi/fampisehoana.cgi\">\n");
      }
      else {
        sprintf(baiko, "sudo a2dissite %s", tranokala);
         b = popen(baiko, "r");
        if(b){
          r = popen("sudo systemctl reload apache2", "r");
          if(r){
            pclose(r);
          }
          else{
            printf("<h1>Misy olana eo amin'ilay famerenana ilay apache2 (2)</h1>\n");
          }
          pclose(b);
        }
        else{
          printf("<h1>Misy olana eo amin'ny fanaovana ilay fandefasana ilay torimarika.</h1>\n");
        }

 //       system("sudo systemctl reload apache2");
        printf("<h1>Vita ilay baiko!!!</h1>\n");
        printf("<meta http-equiv=\"refresh\" content=\"0; http://www.tranokala.mg/cgi/fampisehoana.cgi\">\n");
      }
    }
  }
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

int manisa_andalana(char *baiko){
  int isa = 0;
  char teny[100];
  FILE *misy = NULL;

  misy = popen(baiko, "r");
  if(misy){
    while(fgets(teny, 100, misy))
      isa++;
    pclose(misy);
  }

  return isa;
}

void maneo_hafatra(char *lohateny, char *hafatra, char *toerana){
  printf("<h1>%s</h1>\n", lohateny);
  printf("<p>%s</p>\n", hafatra);
  printf("<a href=\"http://%s\">Continuer</a>\n", toerana);
}

char  **maka_misy(FILE *misy, int isa){
  char **tranokala;
  tranokala = (char **)malloc(sizeof(char*)*isa);
  for(int i=0;i<isa;i++){
    tranokala[i] = (char *)malloc(sizeof(char)*100);
  }

  for(int i=0;i<isa;i++){
    fgets(tranokala[i], 100, misy);
  }

  return tranokala;
}

char **maka_tsy_miasa(char **tranokala, int isa, char **tranokala_miasa, int isa_miasa){
  char **tranokala_tsy_miasa;
  int m=0, n=0;

  tranokala_tsy_miasa = (char **)malloc(sizeof(char*)*(isa-isa_miasa));
  for(int i=0;i<(isa-isa_miasa);i++){
    tranokala_tsy_miasa[i] = (char *)malloc(100);
  }

  for(int i=0;i<isa;i++){
    for(int j=0;j<isa_miasa;j++){
      if(!strcmp(tranokala[i], tranokala_miasa[j])){
        m=1;
      }
    }
    if(!m){
      strcpy(tranokala_tsy_miasa[n], tranokala[i]);
      n++;
    }
    m=0;
  }

  return tranokala_tsy_miasa;
}

void mampiseho_tranokala(){
  FILE *misy = NULL;
  FILE *miasa = NULL;
  char **tranokala;
  char **tranokala_miasa, **tranokala_tsy_miasa;
  char teny[255];
  int isa=0, isa_miasa=0;


  isa = manisa_andalana("ls -1 /etc/apache2/sites-available/");
  isa_miasa = manisa_andalana("ls -1 /etc/apache2/sites-enabled/");
  misy = popen("ls -1 /etc/apache2/sites-available/", "r"); 
  miasa = popen("ls -1 /etc/apache2/sites-enabled/", "r");

  if(misy){
     
    tranokala = maka_misy(misy, isa);
    tranokala_miasa = maka_misy(miasa, isa_miasa);
    tranokala_tsy_miasa = maka_tsy_miasa(tranokala, isa, tranokala_miasa, isa_miasa);

    printf("<h1>Les configurations des sites dans cette ordinateur sont : </h1>\n");
    printf("<table>\n");
    for(int i=0;i<isa;i++){
      if(strcmp(tranokala[i], "000-default.conf\n")){
        sscanf(tranokala[i], "%[^.].conf", teny);
        printf("<tr><td><h4>%s</h4></td><td><a href=\"http://www.tranokala.mg/cgi/history.cgi?tranokala=%s_access.log\">apropos</a></td></tr>\n", tranokala[i], teny);
      }
      else {
        printf("<tr><td><h4>%s</h4></td><td><a href=\"http://www.tranokala.mg/cgi/history.cgi?tranokala=access.log\">apropos</a></td></tr>\n", tranokala[i]);
      }
    }
    printf("</table>\n");

    printf("<h1>Les configurations activées : </h1>\n");
    printf("<table>\n");
    for(int i=0;i<isa_miasa;i++){
      printf("<tr><td><h4>%s</h4></td><td><a href=\"http://www.tranokala.mg/cgi/fampisehoana.cgi?tsy_miasa=0&tranokala=%s\">Desactivée</a></td></tr>\n", tranokala_miasa[i], tranokala_miasa[i]);
    }
    printf("</table>\n");

    printf("<h1>Les configurations desactivées : </h1>\n");
    printf("<table>\n");
    for(int i=0;i<(isa-isa_miasa);i++){
      printf("<tr><td><h4>%s</h4></td><td><a href=\"http://www.tranokala.mg/cgi/fampisehoana.cgi?tsy_miasa=1&tranokala=%s\">Activée</a></td></tr>\n", tranokala_tsy_miasa[i], tranokala_tsy_miasa[i]);
    }
    printf("</table>\n");

    pclose(misy);
    free(tranokala);
  }
  else{
    maneo_hafatra("Erreur du commande ls", "La commande ls sur le dossier /etc/apache2/sites-available/ a echoué", "www.tranokala.mg/cgi/fampisehoana.cgi");
  }
}
