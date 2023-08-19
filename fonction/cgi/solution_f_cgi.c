#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define eps 1e-20

#include "solution_f_cgi.h"

int main(){
    long double a=1, b=3;

    manomboka_cgi("Solution d'une foction.\n");
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
        "<tr class=\"tete\"><td>Nombre de calcule</td><td>Solution pour les calcules</td><td>Dans l'interval [a;b]</td></tr>\n"
    );
}

void manidy_tabilao(){
    printf(
        "</table>\n"
    );
}

void mamoaka_valiny(long double a, long double b){
    int i=0;

    if(f(a)*f(b) < 0){

        manokatra_tabilao();

        while( fabs(b-a) > eps ){
            if(f(a)*f((a+b)/2) < 0){
                printf("<tr><td> %d</td><td>%0.50Lf</td><td>[ %Lf ; %Lf ]</td><tr>\n", i, (a+b)/2.0L, a, b);
                b = ((a+b)/2);
            }
            else{
                printf("<tr><td>%d</td><td>%0.50Lf</td><td>[ %Lf ; %Lf ]</td><tr>\n", i, (a+b)/2.0L, a, b);
                a = ((a+b)/2);
            }
            i++;
        }

        printf("<tr class=\"final\"><td>Final %d</td><td>%0.50Lf</td><td>[ %Lf ; %Lf ]</td><tr>\n", i, (a+b)/2.0L, a, b);

        manidy_tabilao();
    }
    else{
        printf("<h1>La solution n'est pas include dans cette intervalle.\n</h1>\n");
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
        "<p>On calcule la solution à l'aide d'une intervale [a;b].</p>\n"
        "<form action=\"\" method=\"get\">\n"
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
