#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acceil.h"

int main(){

    miala();
    manomboka_cgi("html", "styles.css");
    if(ao_ve()){
        bar_abony_ao();
        lesona();
    }
    else{
        bar_abony();
        lesona();
    }
    mamarana_cgi();

    return 0;
}

int miala(){
    int n=0;
    char *teny=NULL;
    Login *log;
    FILE *fichier=NULL;
    char *ip = getenv("REMOTE_ADDR");

    teny = getenv("QUERY_STRING");
    if(!strcmp(teny, "logout=1")){
        fichier = fopen("./login", "w+");
        if(fichier != NULL){
            n = manisa_andalana(fichier);
            log = (Login*)malloc(n*sizeof(Login));

            for(int i=0;i<n;i++){
                fgets(teny, 500, fichier);
                sscanf(teny, "%[^;];%[^;];%s", log[i].login, log[i].status, log[i].ip);
            }
            for(int i=0;i<n;i++){
                if(strcmp(ip, log[i].ip)){
                    fprintf(fichier, "%s;%s;%s", log[i].login, log[i].status, log[i].ip);
                }
            }

            fclose(fichier);
        }
        else{
            printf("<h1>Erreur de l'ouverture du fichier login.</h1>");
        }
    }
    return 0;
}

int ao_ve(){
    int n=0, ao=0;
    Login *log;
    FILE *fichier=NULL;
    char teny[500];
    char *ip = getenv("REMOTE_ADDR");

    fichier = fopen("./login", "r");
    if(fichier!=NULL){
        n = manisa_andalana(fichier);
        log = (Login*)malloc(n*sizeof(Login));

        for(int i=0;i<n;i++){
            fgets(teny, 500, fichier);
            sscanf(teny, "%[^;];%[^;];%s", log[i].login, log[i].status, log[i].ip);
        }
        for(int i=0;i<n;i++){
            if(!strcmp(ip, log[i].ip)){
                ao=1;
            }
        }

        fclose(fichier);
    }
    else{
        printf("<h1>Erreur de l'ouverture du fichier login.</h1>");
    }
    return ao;
}

int manisa_andalana(FILE *fichier){
    int isa=0;
    char teny[256];
    while(fgets(teny, 256, fichier))
        isa++;
    rewind(fichier);
    return isa;
}

void manomboka_cgi(char *karazany, char *css){
    printf("Context-Type:text/%s\n\n", karazany);

    printf( "<!DOCTYPE html>\n"
            "<html lang=\"en\">\n"
            "<head>\n"
            "   <meta charset=\"UTF-8\">\n"
            "   <title>AUTH.LOG</title>\n"
            "   <link rel=\"stylesheet\" href=\"http://www.auth.mg/%s\">\n"
            "</head>\n"
            "<body>\n"
    , css);
}

void mamarana_cgi(){
    printf( "</body>\n"
            "</html>\n"
    );
}

void bar_abony(){
    printf( "<header>\n"
            "    <a href=\"#\" class=\"titre\">Auth.log</a>\n"
            "    <div class=\"navigation\">\n"
            "        <div class=\"menu\">\n"
            "            <a href=\"http://www.auth.mg/cgi/acceil.cgi\">Acceil</a>\n"
            "            <a href=\"http://www.auth.mg/cgi/inscription.cgi\">S'inscrire</a>\n"
            "            <a href=\"http://www.auth.mg/cgi/connexion.cgi\">Se connecter</a>\n"
            "        </div>\n"
            "    </div>\n"
            "</header>\n"
    );
}

void bar_abony_ao(){
    printf( "<header>\n"
            "    <a href=\"#\" class=\"titre\">Auth.log</a>\n"
            "    <div class=\"navigation\">\n"
            "        <div class=\"menu\">\n"
            "            <a href=\"http://www.auth.mg/cgi/acceil.cgi\">Apprendre</a>\n"
            "            <a href=\"http://www.auth.mg/cgi/inscription.cgi\">Contenue</a>\n"
            "            <a href=\"http://www.auth.mg/cgi/connexion.cgi?logout=1\">Se deconnecter</a>\n"
            "        </div>\n"
            "    </div>\n"
            "</header>\n"
    );
}

void lesona(){
    printf( "<section class=\"home\">\n"
            "    <div class=\"text\">\n"
            "         <h1>Le fichier auth.log</h1><br>\n"
            "         <p>Le fichier auth.log est dans le repértoire /var/log. Il contient les journaux des utilisateurs dans l'ordinateur (Personne ou non).</p><br>\n"
            "        <a href=\"#\"class=\"voir\" >Apprendre...</a>\n"
            "    </div>\n"
            "</section>\n"
    );
}
