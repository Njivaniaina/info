#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "famoronana.h"

int main(int argc, char *argv[]){
  Tranokala tranokala;
  char teny[500], cgi[500], cmd[400];
  Torimarika manisy_fahafahana={"", {"Require all granted", "", "", ""}};
  Torimarika manisy_cgi={"", {"Options +ExecCGI", "", "", ""}};

  manomboka_cgi("html", "Manoratra ilay torimarika");

  tranokala = maka_mahakasika();
  sprintf(teny, "./%s.conf", tranokala.mahakasika);
  if(manoratra_torimarika(teny, tranokala)) {
     if(tranokala.cgi){
      strcpy(manisy_fahafahana.toerana, tranokala.toerana);
      sprintf(cgi, "%s/cgi/", tranokala.toerana);
      strcpy(manisy_cgi.toerana, cgi);
      mametraka_torimarika(teny, &manisy_cgi, 1);
      mametraka_torimarika(teny, &manisy_fahafahana, 1);
    }
    else {
      strcpy(manisy_fahafahana.toerana, tranokala.toerana);
      mametraka_torimarika(teny, &manisy_fahafahana, 1);
    }
    sprintf(cmd, "sudo cp ./%s.conf /etc/apache2/sites-available/", tranokala.mahakasika);
    if(popen(cmd , "r")){
 //     printf("<h1>Ilay lalana dia %s</h1>\n", tranokala.mahakasika);
      maneo_hafatra("Configuration du site terminé", "La configuration du site est terminé avec succes!!!", "www.tranokala.mg/cgi/fidirana.cgi");
//      printf("<meta http-equiv=\"refresh\" content=\"3; URL=http://www.tranokala.mg/cgi/famenoana.cgi\">\n");
    }
  }
  else {
    maneo_hafatra("Echec de la creation", "La creation du fichier andrana.conf a echoué.", "www.tranokala.mg/cgi/famenoana.cgi");
  }

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

Tranokala maka_mahakasika(){
  char *teny = NULL;
  char *t = NULL;
  char *miafina;
  char misy[256];
  int alava;
  Tranokala tranokala;
  CURL *url;

  url = curl_easy_init();
  if(url){
	  teny = getenv("QUERY_STRING");
	  if(teny){
		  t = strtok(teny, "&");
		  sscanf(t, "mahakasika=%s", misy);
      miafina = curl_easy_unescape(url, misy, 0, &alava);
      strcpy(tranokala.mahakasika, miafina);
      curl_free(miafina);
		  while((t=strtok(NULL, "&"))){
		    //printf("<p>Ilay teny dia %s</p><br>\n", t);
	  	  if(strstr(t, "anarana=")){
		  	  sscanf(t, "anarana=%s", misy);
          miafina = curl_easy_unescape(url, misy, 0, &alava);
			    strcpy(tranokala.tranokala, miafina);
         curl_free(miafina);
            //printf("servername=%s\n", tranokala.tranokala);
		    }
		    if(strstr(t, "tompony=")){
			    sscanf(t, "tompony=%s", misy);
          miafina = curl_easy_unescape(url, misy, 0, &alava);
	  		  strcpy(tranokala.tompony, miafina);
          curl_free(miafina);
          //printf("serveradmin=%s\n", tranokala.tompony);
		    }
		    if(strstr(t, "toerana=")){
  			  sscanf(t, "toerana=%s", misy);
          miafina = curl_easy_unescape(url, misy, 0, &alava);
          strcpy(tranokala.toerana, miafina);
          curl_free(miafina);
			    //printf("documentroot=%s\n", tranokala.toerana);
		    }
		    if(strstr(t, "cgi=eny")){
			    tranokala.cgi = 1;
		    }
		    if(strstr(t, "cgi=tsia")){
			    tranokala.cgi = 0;
		    }
		  }
    }
	  curl_easy_cleanup(url);
  }

  return tranokala; 
}

int manoratra_torimarika(char *lalana, Tranokala tranokala){
  FILE *misy = NULL;
  int miverina=0;

  misy = fopen(lalana, "w");
  if(misy){
    fprintf(misy,
            "<VirtualHost *:80>\n"
            "\t#The ServerName directive sets the request scheme, hostname and port that\n"
            "\t#the server user uses to identify itself. This is used when creating\n"
            "\t#redirection URLs. In the context of virtual hosts, the ServerName\n"
            "\t#specifies what hostname must appear in the request's Host: header to\n"
            "\t#match this virtual hosts. For the default virtual host this\n"
            "\t#value is not decisive as it is used as a last resort host regardless.\n"
            "\t#However, you must set it for any further virtual host explicitly.\n\n"
            "\tServerName %s\n"
            "\tServerAdmin %s\n"
            "\tDocumentRoot %s\n\n"
            "\t# Available loglevels: trace8, ..., trace1, debug, info, notice, warn,\n"
            "\t# error, crit, alert, emerg.\n"
            "\t# It is also possible to configure the loglevel for particular\n"
            "\t# modules, e.g.\n"
            "\t#LogLevel info ssl:warn# Available loglevels: trace8, ..., trace1, debug, info, notice, warn,\n"
            "\t# error, crit, alert, emerg.\n"
            "\t# It is also possible to configure the loglevel for particular\n"
            "\t# modules, e.g.\n"
            "\t#LogLevel info ssl:warn\n\n"
            "\tErrorLog ${APACHE_LOG_DIR}/error.log\n"
            "\tCustomLog ${APACHE_LOG_DIR}/%s_access.log combined\n\n"
            "\t# For most configuration files from conf-available/, which are\n"
            "\t# enabled or disabled at a global level, it is possible to\n"
            "\t# include a line for only one particular virtual host. For example the\n"
            "\t# following line enables the CGI configuration for this host only\n"
            "\t# after it has been globally disabled with \"a2disconf\".\n"
            "\t#Include conf-available/serve-cgi-bin.conf\n"
            "</VirtualHost>\n"
            , tranokala.tranokala, tranokala.tompony, tranokala.toerana, tranokala.mahakasika);
    fclose(misy);
    miverina=1;
  }

  return miverina;
}

void maneo_hafatra(char *lohateny, char *hafatra, char *toerana){
  printf("<h1>%s</h1>\n", lohateny);
  printf("<p>%s</p>\n", hafatra);
  printf("<a href=\"http://%s\">Continuer</a>\n", toerana);
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
    teny[i] = (char*)malloc(500);
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
          for(int j=0;j<4;j++){
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
}
