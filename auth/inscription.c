#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "inscription.h"

int main(){
    User *users;
    User *u;
    char tadiavina[256]="";
    long isa=0;
    Olona user={"", "", ""};

    miala();
    manomboka_cgi("html", "styles.css");
    if(ao_ve()){
        bar_abony_ao();
        users = maka(&isa);
        u = (User*)malloc((isa)*sizeof(User));
        printf("<div class=\"Contenu_auth\">");
        fitadiavana();
        if(mitady_ve(users, u, &isa, tadiavina)){
            mampiseho(u, isa, (laharany_pejy()*10), (laharany_pejy()*10)+10, tadiavina);
        }
        else{
            mampiseho(users, isa, (laharany_pejy()*10), (laharany_pejy()*10)+10, tadiavina);
        }
        printf("</div>");
    }
    else{
        bar_abony();
        maka_mombamomba(&user);
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
    printf( "<div class=\"formulaire2\">\n"
            "         <form action=\"http://www.auth.mg/cgi/inscription.cgi\" method=\"get\">\n"
            "             <h1>Inscription</h1>\n"
            "             <input type=\"text\" name=\"login\" placeholder=\"Login\" class=\"text\"/><br>\n"
            "             <input type=\"password\" name=\"passwd1\" placeholder=\"Mot de passe\" class=\"text\" /><br>\n"
            "             <input type=\"password\" name=\"passwd2\" placeholder=\"Retaper le mot de passe\" class=\"text\"/><br>\n"
            "             <input type=\"submit\" value=\"S'inscrire\" class=\"valider\">\n"
            "          </form>\n"
            "    </div>\n"
    );
}

int maka_mombamomba(Olona *o){
    char *text=NULL;
    text = getenv("QUERY_STRING");
    
    if(text != NULL){
        sscanf(text, "login=%[^&]&passwd1=%[^&]&passwd2=%s", o->login, o->passwd, o->passwd0);
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
        if(!tsy_mitovy(user)){
            if(mandray_olona(user))
                voaray();
        }
        else{
            tsy_voaray("Les deux mots de passe ne sont pas identique.");
        }
    }

    return 1;
}

int tsy_mitovy(Olona user){
    if(!strcmp(user.passwd, user.passwd0))
        return 0;
    return 1;
}

void voaray(){
    printf( "<div class=\"valiny\">\n"
            "   <h1>Inscription terminé!!!</h1>\n"
            "   <a href=\"http://www.auth.mg/cgi/acceil.cgi\">Continue</a>"
            "</div>\n"
    );
}

int mandray_olona(Olona user){
    int n=0, efa_misy=0;
    FILE *fichier=NULL;
    Olona *u;

    fichier = fopen("./user", "a+");
    if(fichier!=NULL){
        n = manisa_andalana(fichier),
        u = (Olona*)malloc(n*sizeof(Olona));
        
        if(n>0){
            maka_olona_misy(fichier,u,n);
            for(int i=0;i<n;i++){
                if(!strcmp(u[i].login, user.login)){
                    efa_misy=1;
                }
            }
        }
        if(efa_misy){
            tsy_voaray("Il existe déjà une login identique.");
            return 0;
        }
        else{
            manoratra(fichier,user);
        }

        fclose(fichier);
    }   
    else{
        printf("<h1>Erreur de l'ouverture du fichier user.</h1>\n");
    }

    return 1;
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

int manoratra(FILE *fichier, Olona user){
    fprintf(fichier, "%s;%s\n", user.login, user.passwd);
    return 1;
}

void tsy_voaray(char *diso){
    printf( "<div class=\"valiny\">\n"
            "   <h1>Inscription échoué!!!</h1>\n"
            "   <p>%s</p>\n"
            "   <a href=\"http://www.auth.mg/cgi/inscription.cgi\">Retour</a>\n"
            "</div>\n"
    , diso);
}


//////////////////////////////////////////////////////
//          Efa tafiditra ilay olona                //
//////////////////////////////////////////////////////

void fitadiavana(){
    printf( "<form action=\"http://www.auth.mg/cgi/inscription.cgi\" method=\"get\">\n"
            "<input type=\"text\" class=\"cherche\" name=\"tadiavo\" placeholder=\"Nom d'un utilisateur\">\n"
            "<input type=\"Submit\" class=\"boutton\" value=\"Rechercher\">\n"
            "</form>"
    );
}

int mitady_ve(User *u, User *v, long *n, char *tadiavina){
    char *teny;
    char *tohiny;
    long j=0;

    teny = getenv("QUERY_STRING");
    if(teny != NULL){
        if((tohiny=strstr(teny, "tadiavo="))){
            sscanf(tohiny, "tadiavo=%[^&\n ]", tadiavina);
            for(int i=0;i<strlen(tadiavina);i++){
                tadiavina[i]=tolower(tadiavina[i]);
            }
            if(!strcmp(tadiavina, "")){
                printf("<h1>Aucun nom à rechercher n'est entrer.</h1>\n");
            }
            else{
                for(long i=0;i<(*n);i++){
                    if(strstr(u[i].user, tadiavina)){
                        strcpy(v[j].user, u[i].user);
                        strcpy(v[j].session, u[i].session);
                        strcpy(v[j].time, u[i].time);
                        strcpy(v[j].date, u[i].date);
                        j++;
                    }
                }
            }
            if(j==0 && strcmp(tadiavina, "")){
                printf("<h1>Aucun nom n'est toruver !!!.</h1>\n");
            }

            (*n) = j;

            return 1;
        }
    }
    return 0;
}

void mampiseho(User *user, long n, long a, long b, char *tadiavina){
    int fiatombohana=0, fihafarana=0;

    if(n>0){
        printf( "<table border=\"3\">"
                "<tr class=\"tete\"><td>Olona</td><td>Nanokatra/Nanidy</td><td>Ora</td><td>Daty</td></tr>\n"
        );
        for(long i=a;i<n && i <= b;i++){
            printf(
                    "<tr class=\"%s\"><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>\n"
            , (!strcmp(user[i].session, "opened"))?"mivoha":"mihidy", user[i].user, (!strcmp(user[i].session, "opened"))?"Nanokatra":"Nanidy", user[i].time, daty(user[i].date));
        }
        printf("</table>");

        printf("<div class=\"pejy\">");
        printf("<a class=\"page\" href=\"http://www.auth.mg/cgi/inscription.cgi?page=0\">Début</a>");

        if(((n%10==0)?n/10:(n/10)+1) < 10){
            if(!strcmp(tadiavina, "")){
                for(int i=0;i<((n%10==0)?n/10:(n/10)+1);i++){
                    printf("<a class=\"%s\" href=\"http://www.auth.mg/cgi/inscription.cgi?page=%d\">%d</a>", (laharany_pejy()==i)?"page1":"page", i, i+1);
                }
            }
            else{
                for(int i=0;i<((n%10==0)?n/10:(n/10)+1);i++){
                    printf("<a class=\"%s\" href=\"http://www.auth.mg/cgi/inscription.cgi?tadiavo=%s&page=%d\">%d</a>", (laharany_pejy()==i)?"page1":"page", tadiavina, i, i+1);
                }
            }
        }
        else{
            if(laharany_pejy()<=5){
                fiatombohana=0;
                fihafarana=10;
            }
            else{
                fiatombohana=laharany_pejy()-5;
            }

            if(laharany_pejy()>((n%10==0)?n/10:(n/10)+1)-5 && fihafarana == 0){
                fihafarana=((n%10==0)?n/10:(n/10)+1);
                fiatombohana=((((n%10==0)?n/10:(n/10)+1)-10));
            }
            else if(fihafarana==0){
                fihafarana=laharany_pejy()+5;
            }

            if(!strcmp(tadiavina, "")){
                for(int i=fiatombohana;i<fihafarana;i++){
                    /* printf("<div class=\"%s\">", (laharany_pejy()==i)?"page1":"page"); */
                    printf("<a class=\"%s\" href=\"http://www.auth.mg/cgi/inscription.cgi?page=%d\">%d</a>", (laharany_pejy()==i)?"page1":"page", i, i+1);
                }
            }
            else{
                for(int i=fiatombohana;i<fihafarana;i++){
                    printf("<a class=\"%s\" href=\"http://www.auth.mg/cgi/inscription.cgi?tadiavo=%s&page=%d\">%d</a>", (laharany_pejy()==i)?"page1":"page", tadiavina, i, i+1);
                }
            }
        }
        printf("<a class=\"page\" href=\"http://www.auth.mg/cgi/inscription.cgi?page=%ld\">Fin</a>", ((n%10==0)?n/10:(n/10)+1)-1);

        printf("</div>");
    }
}

int laharany_pejy(){
    char *teny, *tohiny;
    int pejy=0;

    teny = getenv("QUERY_STRING");
    if(teny != NULL){
        if((tohiny=strstr(teny, "page="))){
            sscanf(tohiny, "page=%d", &pejy);
        }
    }
    return pejy;
}

User *maka(long *n){
    long i=0;
    char teny[1000];
    char *tohiny_teny;
    FILE *fichier;
    User *u;

    system("cat /var/log/auth.log>./auth.log");
    fichier = fopen("./auth.log", "r");

    if(fichier != NULL){
        *n = manisa_andalana_hafa(fichier);
        u = (User*)malloc((*n)*sizeof(User));

        i=0;
        while(fgets(teny, 1000, fichier)){
            if((tohiny_teny=strstr(teny, ": session "))){
                sscanf(teny, "%[^T]T%[^.]", u[i].date, u[i].time);
                sscanf(tohiny_teny, ": session %s for user %[^(\n]", u[i].session, u[i].user);
                i++;
            }
        }
        
       /*  printf("Date           Time           session        user\n");
        for(long i=0;i<n;i++){
            printf("%-15s%-15s%-15s%-15s\n", u[i].date, u[i].time, u[i].session, u[i].user);
        } */

        fclose(fichier);
    }
    else{
        printf("<h1>Erreur de l'ouverture du fichier auth.log.</h1>\n");
        return 0;
    }

    return u;
}

int manisa_andalana_hafa(FILE *fichier){
    int isa=0;
    char teny[256];
    while(fgets(teny, 256, fichier)){
        if(strstr(teny, "for user")){
            isa++;
        }
    }
    rewind(fichier);
    return isa;
}

char *daty(char *date){
    char *teny;
    int andro, volana, taona;
    char a[7][50]={"Alahady", "Alatsinainy", "Talata", "Alarobia", "Alakamisy", "Zoma", "Sabotsy"};
    char v[12][50]={"Janoary", "Febroary", "Martsa", "Aprily", "May", "Jiona", "Jolay", "Aogositra", "Septembra", "Oktobra", "Novambra", "Desambra"};
    int code[12]={0,3,3,6,1,4,6,2,5,0,3,5};

    teny = (char*)malloc(256);

    sscanf(date, "%d-%d-%d", &taona, &volana, &andro);

    //Ny fikajiana ilay andro dia ao anatin'ny {0..6} dia miatomboka alahady=0 ka hatramin'ny sabotsy=6
    /*
        Fomba fakana azy:
        *alaina ny taona-1900 
        *alaina ny (taona-1900)/4
        *alaina ny andro
        *alaina ny codin'ny volana
        atambatra amin'ny farany dia zaraina 7 ka ny ambiny ilay andro.
    */ 
    sprintf(teny, "%s %d %s %d", a[((taona-1900)+((int)(taona-1900)/4)+andro+code[volana-1])%7], andro, v[volana-1], taona);

    return teny;
}