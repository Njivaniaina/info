#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-50

void mampiditra(long double *a, long double *b);
long double f(long double a);

int main(){
    long double a=0, b=0;
    int i=1;

    printf("Cette programme cherche la solution de f(x)=ln(x)-1 sur un intervalle [a;b] que l'on donne.\n");
    mampiditra(&a,&b);

    if(f(a)*f(b) < 0){
        while(fabs(b-a) > eps){
            if(f(a)*f((a+b)/2) < 0){
                b = (a+b)/2;
                printf("Solution %d = %0.50Lf\n", i, (a+b)/2);
            }
            else{
                a = (a+b)/2;
                printf("Solution %d = %0.50Lf\n", i, (a+b)/2);
            }
            i++;
        }
    }

    printf("La solution est : %0.50Lf\n", (a+b)/2);

    return 0;
}

void mampiditra(long double *a, long double *b){
    printf("Entrer le nombre a de l'intervalle: ");
    scanf("%Lf", a);
    printf("Entrer le nombre b de l'intervalle: ");
    scanf("%Lf", b);
}

long double f(long double a){
    return (log(a)-1);
}