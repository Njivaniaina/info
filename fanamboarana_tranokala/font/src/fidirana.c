#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fidirana.h"

int main(int argc, char **argv){
  Olona olona={"", "", ""};

  manomboka_cgi("html", "Fidirana");

  miala_na_tsia();
  if(tafiditra_ve()){
		printf("<meta http-equiv=\"refresh\" content=\"0; http://www.tranokala.mg/cgi/fampisehoana.cgi\">\n");
  }
  else{
    bara_ambony();
    maka_nalefa(&olona);
    if(!strcmp(olona.anarana, "")){
	  	  famenoana_fidirana();
	  }
	  else{
		  if(manamarina(olona)){
			  tafiditra(olona);
			  printf("<meta http-equiv=\"refresh\" content=\"0; http://www.tranokala.mg/cgi/fampisehoana.cgi\">\n");
		  }
		  else{
			  maneo_hafatra("Connexion echoué", "Erreur de login ou de mot de passe incorrecte!!!!!");
		  }
	  }
  }

  mamarana_cgi();

  return 0;
}

void maneo_hafatra(char *lohateny, char *hafatra){
  printf("<h1>%s</h1>\n", lohateny);
  printf("<p>%s</p>\n", hafatra);
}

int miala_na_tsia(){
    int isa_andalana=0;
    char *teny=NULL;
    Fidirana *fidirana;
    FILE *misy=NULL;
    char *ip = getenv("REMOTE_ADDR");

	isa_andalana = manisa_andalana("./login.conf");
    teny = getenv("QUERY_STRING");
    if(!strcmp(teny, "logout=1")){
        misy = fopen("./login.conf", "r");
        if(misy != NULL){
            fidirana = (Fidirana*)malloc(isa_andalana*sizeof(Fidirana));

            for(int i=0;i<isa_andalana;i++){
                fgets(teny, 500, misy);
                sscanf(teny, "%[^;];%[^;];%s", fidirana[i].anarana, fidirana[i].fidirana, fidirana[i].ip);
            } 
            fclose(misy);
        }
        else{
            printf("<h1>Erreur de l'ouverture du fichier login.</h1>");
        }

        misy = fopen("./login.conf", "w");
        if(misy != NULL){
            for(int i=0;i<isa_andalana;i++){
                if(strcmp(ip, fidirana[i].ip)){
                    fprintf(misy, "%s;%s;%s", fidirana[i].anarana, fidirana[i].fidirana, fidirana[i].ip);
                }
            }
            
            fclose(misy);
        }
        else{
            printf("<h1>Erreur de l'ouverture du fichier login.</h1>");
        }
    }
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
            "            <a href=\"http://www.tranokala.mg/cgi/fanoratana_anarana.cgi\">Les sites</a>\n"
            "            <a href=\"http://www.tranokala.mg/cgi/fidirana.cgi?logout=1\">Se deconnecter</a>\n"
            "        </div>\n"
            "    </div>\n"
            "</header>\n"
    );
}

void famenoana_fidirana(){
    printf( ""
            "<div class=\"\">\n"
            "    <form action=\"\" method=\"get\">\n"
            "         <h1>Connexion</h1>\n"
            "         <input type=\"text\" name=\"anarana\" placeholder=\"Login\" class=\"\"/><br>\n"
            "         <input type=\"password\" name=\"tenyMiafina\" placeholder=\"Mot de passe\" class=\"\"/><br>\n"
            "         <input type=\"submit\" value=\"Se connecter\" class=\"\">\n"
            "     </form>\n"
            "</div>\n"
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

int maka_nalefa(Olona *o){
    char *text=NULL;
    text = getenv("QUERY_STRING");
    
//  printf("<h1>Maka ny nalefa dia %s</h1>\n", text);
    if(text != NULL && (strcmp(text, "logout=1") != 0)){
        sscanf(text, "anarana=%[^&]&tenyMiafina=%s", o->anarana, o->teny_miafina);
//        printf("<h1>Maka ananarana nisy  dia anarana : %s teny miafina : %s</h1>\n", o->anarana, o->teny_miafina);
    }
    else{
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

int manamarina(Olona olona){
    int isa_andalana=0, misy_anarana=0, marina=0;
    Olona *o;
    FILE *misy=NULL;

	isa_andalana = manisa_andalana("./user.conf");
    misy = fopen("./user.conf", "r");
    if(misy != NULL){
        o = (Olona*)malloc(isa_andalana*sizeof(Olona));
        maka_olona_misy(misy, o, isa_andalana);

        for(int i=0;i<isa_andalana;i++){
            if(!strcmp(o[i].anarana, olona.anarana)){
                misy_anarana=i+1;
            }
        }
        if(misy_anarana){
            if(!strcmp(o[misy_anarana-1].teny_miafina, olona.teny_miafina)){
                marina=1;
            }
        }

        fclose(misy);
    }
    else{
        printf("<h1>Tsy nisokatra ilay mitahiry ny anaran'ireo olona misy.</h1>");
    }
    if(misy_anarana && marina)
        return 1;

    return 0;
}

int tafiditra(Olona olona){
    FILE *misy=NULL;
    char *ip = getenv("REMOTE_ADDR");

    misy = fopen("./login.conf", "a");
    if(misy!=NULL){
        fprintf(misy, "%s;%s;%s\n", olona.anarana, "connected", ip);
        fclose(misy);
    }
    else{
        printf("<h1>Erreur de l'ouverture du fichier login.</h1>");
    }
    return 1;
}
