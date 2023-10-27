#include <stdio.h>
#include <math.h>

#define eps 1e-20

#include "solution_tangente.h"

int main(){
    long double a=0;

    a=maka_a();
    mamoaka_valiny(a);

    return 0;
}

long double maka_a(){
    long double a=0;
    printf("Enter un point  a :");
    scanf("%Lf", &a);
    return a;
}

long double f(long double a){
    return (log(a)-1);
}

long double f1(long double a){
    return (1/a);
}

long double mamoaka_valiny(long double a){
    while(fabs(f(a)) > eps){
        printf("f(a)=%Lf\nf1(a)=%Lf\na=%Lf\n", f(a), f1(a), a);
        a = (-(f(a)/f1(a))) + a;
        printf("a=%Lf\n", a);
    }

    printf("La reponse est  %LF.\n", a);
    return a;
}