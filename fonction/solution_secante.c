#include <stdio.h>
#include <math.h>

#include "solution_secante.h"

#define eps 1e-10

int main(){
    long double a=0, b=0;

    maka_a_b(&a,&b);
    mikajy(a, b);

    return 0;
}

void maka_a_b(long double *a, long double *b){
    printf("Entrer la nombre a : ");
    scanf("%Lf", a);
    printf("Entrer la nombre b : ");
    scanf("%Lf", b);
}

long double f(long double a){
    return (log(a)-1);
}

void mikajy(long double a, long double b){
    long double x=0, y=0, tmp=0;

    if(f(a)*f(b) <= 0){
        while(fabs(f(tmp)) > eps){
            x = (f(a)-f(b))/(a-b);
            y = ((b*f(a))-(a*f(b)))/(b-a);
            tmp = (-y)/x;

            printf("x=%Lf\ty=%Lf\ttmp=%Lf\n", x, y, tmp);
            if(f(a)*f(tmp) <= 0){
                b = tmp;
            }
            else{
                a = tmp;
            }
        }

        printf("La solution est  : %Lf\n", tmp);
    }
    else{
        printf("La solution n'est pas dans cette interval.\n");
    }
}
