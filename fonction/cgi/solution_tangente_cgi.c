#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define eps 1e-20

#include "solution_tangente_cgi.h"

int main(){
    long double a=1;

    manomboka_cgi("Solution d'une la fonction f(x)=ln(x)-1.\n");
    maka_a_cgi();
    if(misy_a(&a)){
        mamoaka_valiny(a);
    }

    mamarana_cgi();

    return 0;
}

void manokatra_tabilao(){
    printf(
        "<table border=\"2\">\n"
        "<tr class=\"tete\"><td>Nombre compteur</td><td>Le nombre a</td><td>f(a)</td><td>f'(a)</td></tr>\n"
    );
}

void manidy_tabilao(){
    printf(
        "</table>\n"
    );
}

void mamoaka_valiny(long double a){
    int i=0;

    manokatra_tabilao();

    while(fabs(f(a)) > eps){
        printf("<tr><td>%d</td><td>%Lf</td><td>%Lf</td><td>%Lf</td><tr>\n", i, a, f(a), f1(a));
        a = (-(f(a)/f1(a))) + a;
        i++;
    }

    printf("<tr class=\"final\"><td>%d</td><td>%Lf</td><td>%Lf</td><td>%Lf</td><tr>\n", i, a, f(a), f1(a));

    manidy_tabilao();
}

long double f(long double a){
    return (log(a)-1);
}

long double f1(long double a){
    return (1/a);
}

int misy_a(long double *a){
    char *teny=NULL;
    char manamarina[256]="";

    teny = getenv("QUERY_STRING");
    if(teny != NULL){
        sscanf(teny, "a=%Lf", a);
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

void maka_a_cgi(){
    printf(
        "<h1>Calcule de la solution f(x)=ln(x)+1 </h1>\n"
        "<p>On calcule la solution à l'aide d'une point a.</p>\n"
        "<form action=\"\" method=\"get\">\n"
        "   <label>Enter le nombre a :</label><input type=\"number\" name=\"a\" value=\"0\"/>\n"
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
