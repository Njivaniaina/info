#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "auth.h"

int main(){
    User *user;
    User *u;
    char tadiavina[256]="";
    long isa=0;
    
    manomboka_cgi("html", "auth.css");
    user = maka(&isa);
    u = (User*)malloc((isa)*sizeof(User));
    fitadiavana();
    if(mitady_ve(user, u, &isa, tadiavina)){
        mampiseho(u, isa, (laharany_pejy()*10), (laharany_pejy()*10)+10, tadiavina);
    }
    else{
        mampiseho(user, isa, (laharany_pejy()*10), (laharany_pejy()*10)+10, tadiavina);
    }

    mamarana_cgi();
    return 0;
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

void fitadiavana(){
    printf( "<form action=\"http://www.auth.mg/cgi/auth.cgi\" method=\"get\">\n"
            "<input type=\"text\" name=\"tadiavo\" placeholder=\"Nom d'un utilisateur\">\n"
            "<input type=\"Submit\" value=\"Rechercher\">\n"
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
                "<tr><td>Olona</td><td>Nanokatra/Nanidy</td><td>Ora</td><td>Daty</td></tr>\n"
        );
        for(long i=a;i<n && i <= b;i++){
            printf(
                    "<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>\n"
            , user[i].user, (!strcmp(user[i].session, "opened"))?"Nanokatra":"Nanidy", user[i].time, daty(user[i].date));
        }
        printf("</table>");

        if(((n%10==0)?n/10:(n/10)+1) < 10){
            if(!strcmp(tadiavina, "")){
                for(int i=0;i<((n%10==0)?n/10:(n/10)+1);i++){
                    printf("<a href=\"http://www.auth.mg/cgi/auth.cgi?page=%d\">%d</a>", i, i+1);
                }
            }
            else{
                for(int i=0;i<((n%10==0)?n/10:(n/10)+1);i++){
                    printf("<a href=\"http://www.auth.mg/cgi/auth.cgi?tadiavo=%s&page=%d\">%d</a>", tadiavina, i, i+1);
                }
            }
        }
        else{
            if(laharany_pejy()<=5){
                fiatombohana=0;
                fihafarana=laharany_pejy()+5+(5-laharany_pejy());
            }
            else{
                fiatombohana=laharany_pejy()-5;
            }

            if(laharany_pejy()>((n%10==0)?n/10:(n/10)+1)-5 && fihafarana == 0){
                fihafarana=((n%10==0)?n/10:(n/10)+1);
                fiatombohana=laharany_pejy()-(5+(((n%10==0)?n/10:(n/10)+1)-5)-laharany_pejy());
            }
            else{
                fihafarana=laharany_pejy()+5;
            }

            if(!strcmp(tadiavina, "")){
                for(int i=fiatombohana;i<fihafarana;i++){
                    printf("<a href=\"http://www.auth.mg/cgi/auth.cgi?page=%d\">%d</a>-", i, i+1);
                }
            }
            else{
                for(int i=fiatombohana;i<fihafarana;i++){
                    printf("<a href=\"http://www.auth.mg/cgi/auth.cgi?tadiavo=%s&page=%d\">%d</a><p> - </p>", tadiavina, i, i+1);
                }
            }
        }
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
        *n = manisa_andalana(fichier);
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

int manisa_andalana(FILE *fichier){
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