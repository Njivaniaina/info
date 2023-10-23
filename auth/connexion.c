#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connexion.h"

int main(){
    Olona user={"", "", ""};

    miala();
    manomboka_cgi("html", "style.css");
    if(ao_ve()){
        bar_abony_ao();
        printf("En ligne");
    }
    else{
        bar_abony();
        maka_nalefa(&user);
        mandray(user);
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

void fenoina(){
    printf( ""
            "<div class=\"formulaire1\">\n"
            "    <form action=\"\" method=\"get\">\n"
            "         <h1>Connexion</h1>\n"
            "         <input type=\"text\" name=\"login\" placeholder=\"Login\" class=\"text\"/><br>\n"
            "         <input type=\"password\" name=\"passwd\" placeholder=\"Mot de passe\" class=\"text\"/><br>\n"
            "         <input type=\"submit\" value=\"Se connecter\" class=\"valider\">\n"
            "     </form>\n"
            "</div>\n"
    );
}

int manisa_andalana(FILE *fichier){
    int isa=0;
    char teny[256];
    while(fgets(teny, 256, fichier))
        isa++;
    rewind(fichier);
    return isa;
}

int maka_olona_misy(FILE *fichier, Olona *u, int n){
    char teny[500];
    if(n>0){
        for(int i=0;i<n;i++){
            fgets(teny, 500, fichier);
            sscanf(teny, "%[^;];%s", u[i].login, u[i].passwd);
        }
    }
    else{
        return 0;
    }
    return 1;
}

int maka_nalefa(Olona *o){
    char *text=NULL;
    text = getenv("QUERY_STRING");
    
    if(text != NULL){
        sscanf(text, "login=%[^&]&passwd=%s", o->login, o->passwd);
    }
    else{
        return 0;
    }
    return 1;
}

int mandray(Olona user){
    if(!strcmp(user.login, "")){
        fenoina();
    }
    else{
        if(manamarina(user)){
            voaray();
            connecter(user);
        }
        else{
            diso();
        }
    }
    return 1;
}

void diso(){
    printf( "<div class=\"valiny\">\n"
            "   <h1>Mot de passe incorrecte!!!</h1>\n"
            "   <a href=\"http://www.auth.mg/cgi/connexion.cgi\">Retour</a>"
            "</div>\n"
    );
}

void tsy_misy(){
    printf( "<div class=\"valiny\">\n"
            "   <h1>Login introuvable!!!</h1>\n"
            "   <a href=\"http://www.auth.mg/cgi/connexion.cgi\">Retour</a>"
            "</div>\n"
    );
}


void voaray(){
    printf( "<div class=\"valiny\">\n"
            "   <h1>Bienvenue!!!</h1>\n"
            "   <a href=\"http://www.auth.mg/cgi/acceil.cgi\">Continuer</a>"
            "</div>\n"
    );
}

int manamarina(Olona user){
    int n=0, misy_anarana=0, marina=0;
    Olona *u;
    FILE *fichier=NULL;

    fichier = fopen("./user", "r");
    if(fichier != NULL){
        n = manisa_andalana(fichier);
        u = (Olona*)malloc(n*sizeof(Olona));
        maka_olona_misy(fichier,u,n);

        for(int i=0;i<n;i++){
            if(!strcmp(u[i].login, user.login)){
                misy_anarana=i+1;
            }
        }
        if(misy_anarana){
            if(!strcmp(u[misy_anarana-1].passwd, user.passwd)){
                marina=1;
            }
        }

        fclose(fichier);
    }
    else{
        printf("<h1>Erreur lors de l'ouverture du fichier user.</h1>");
    }
    if(misy_anarana && marina)
        return 1;

    return 0;
}

int connecter(Olona user){
    FILE *fic=NULL;
    char *ip = getenv("REMOTE_ADDR");

    fic = fopen("./login", "a");
    if(fic!=NULL){
        fprintf(fic, "%s;%s;%s\n", user.login, "connected", ip);
        fclose(fic);
    }
    else{
        printf("<h1>Erreur de l'ouverture du fichier login.</h1>");
    }
    return 1;
}