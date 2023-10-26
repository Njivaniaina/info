#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define eps 1e-3

#include "integral_cgi.h"

int main(){
    long double a=1, b=100;

    manomboka_cgi("Calcule d'integral.\n");
    maka_a_b_cgi();
    if(misy_a_b(&a,&b)){
        mamoaka_valiny(a,b);
    }
    mamarana_cgi();

    return 0;
}

void manokatra_tabilao(){
    printf(
        "<table border=\"2\">\n"
        "<tr class=\"tete\"><td>Nombre de calcule</td><td>Resultats pour chaque changement d'interval</td><td>Sur l'interval</td></tr>\n"
    );
}

void manidy_tabilao(){
    printf(
        "</table>\n"
    );
}

void mamoaka_valiny(long double a, long double b){
    int i=0;
    long double sum=0, tmp=0;

    if(f(a)*f(b) < 0){
        manokatra_tabilao();
        tmp = a;
        while(a <= b){
            sum += (f(a)*eps) + (eps*(f(a+eps)-f(a)));
            a = a+eps;
            printf("<tr><td>%i</td><td>%Lf</td><td>[ %Lf ; %Lf ]</td></tr>\n", i, sum, tmp, a);
            i++;

        }
        if(a>b){
            a=a-eps;
            sum += (f(a)*(b-a));
            printf("<tr class=\"final\"><td>Final %i</td><td>%Lf</td><td>[ %Lf ; %Lf ]</td></tr>\n", i, sum, tmp, a);
        }


        manidy_tabilao();
    }
}

long double f(long double a){
    return (log(a)-1);
}

int misy_a_b(long double *a, long double *b){
    char *teny=NULL;
    char manamarina[256]="";

    teny = getenv("QUERY_STRING");
    if(teny != NULL){
        sscanf(teny, "a=%Lf&b=%Lf", a, b);
        sscanf(teny, "a=%[^&]", manamarina);
        if(!strcmp(manamarina, "")){
            return 0;
        }
    }
    return 1;
}

void manomboka_cgi(char *titre){   
    printf("Context-type:text/html\n\n");
    printf(
        "<!DOCTYPE html>\n"
        "<html>\n"
        "   <head>\n"
        "   <meta charset=\"UTF-8\">\n"
        "   <title>%s</title>\n"
        "   <link rel=\"stylesheet\" href=\"http://localhost/fonction_cgi.css\" >\n"
        "   </head>\n"
        "<body>\n"
    , titre);
}

void maka_a_b_cgi(){
    printf(
        "<h1>Calcule de la solution f(x)=ln(x)+1 </h1>\n"
        "<p>On calclule l'integral de la fonction sur un intervale [a;b]. On varie la valeur de a d'une valeur eps pour qu'il atteinnent la valeur de b et calcule l'integrale pour chaque changement.\n</p>\n"
        "<form action=\"http://localhost/cgi/integral_cgi.cgi\" method=\"get\">\n"
        "   <label>Enter le nombre a :</label><input type=\"number\" name=\"a\" value=\"0\"/>\n"
        "   <label>Enter le nombre b :</label><input type=\"number\" name=\"b\" value=\"0\"/>\n"
        "   <input type=\"submit\" value=\"Calculer\"/>\n"
        "</form>"
    );
}

void mamarana_cgi(){
    printf(
        "</body>\n"
        "</html>\n"
    );
}   
