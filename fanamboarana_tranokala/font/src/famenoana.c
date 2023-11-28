#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "famenoana.h"

int main(int argc, char **argv){

  manomboka_cgi("html", "Fanaovana tranokala");
  
  if(tafiditra_ve()){
    bara_ambony_tafiditra();
    fanovana_tranokala();
  }
  else{
    printf("<meta http-equiv=\"refresh\" content=\"0; URL=http://www.tranokala.mg/cgi/fidirana.cgi\">\n");
  }
  
  mamarana_cgi();
	return  0;
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

void manomboka_cgi(char *karazany, char *lohateny){
	printf(	"Context-Type:text/%s\n\n"
		"<!DOCTYPE html>\n"
		"<html>\n"
		"<head>\n"
		"	<meta charset=\"UTF-8\" />\n"
		"	<title>%s</title>\n"
		"	<link rel=\"stylesheet\" href=\"http://www.tranokala.mg/style.css\">\n"
		"</head>\n"
		"<body>\n"
		, karazany, lohateny);
}

void mamarana_cgi(){
	printf(	"</body>\n"
		"</html> \n"
	      );
}

void fanovana_tranokala(){
	printf(	"<form action=\"http://www.tranokala.mg/cgi/famoronana.cgi\" method=\"get\">\n"
		"	<h1>Configuration du site</h1>\n"
    "<label>Domaine du site : </label><input type=\"text\" name=\"mahakasika\" placeHolder=\"En une seul mot\"/><br>\n"
		"	<label>Nom du serveur : </label><input type=\"text\" name=\"anarana\" placeHolder=\"www.ohatra.mg\"/><br>\n"
		"	<label>L'administrateur du server : </label><input type=\"email\" name=\"tompony\" value=\"webmaster@localhost\" /><br>\n"
		"	<label>Repertoire du  server : </label><input type=\"text\" name=\"toerana\"placeHolder=\"/home/njiva/sites/nom_de_mon_site\"/><br>\n"
		"	<label>Execution des scripts cgi : </label><br>\n"
		"		<input type=\"radio\" name=\"cgi\" value=\"tsia\" id=\"oui\" />\n"
		"			<label for=\"oui\" >Je ne souhaite pas éxecuter des scriptes cgi dans cette sites.</label><br>\n"
    "     <label for=\"oui\">Le réperoire d'éxecution des scripts cgi/ est dans une repertoire appeller cgi dans le repertoire du site.</label><br>\n"
		"		<input type=\"radio\" name=\"cgi\" value=\"eny\" id=\"non\" />\n"
		"			<label for=\"non\">Je souhaite éxecuter des scriptes cgi dans cette sites.</label><br>\n"
		"	<input type=\"submit\" value=\"Confirmer\"><br>\n"
		"</form>\n"
    );
}
