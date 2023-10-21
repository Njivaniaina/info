#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-3

void mampiditra(long double *a, long double *b);
long double f(long double a);

int main(){
    long double a=0, b=0, sum=0;

    printf("Cette programme calcule l'integrale de f(x)=ln(x)-1 sur un intervalle [a;b] que l'on donne.\n");
    mampiditra(&a,&b);

    while(a <= b){
        printf("b = %LF\t t = %LF\tsum = %LF\n", b, a, sum);
        sum += (f(a)*eps)+((f(a+eps)-f(a))*eps)/2;
        a = a+eps;
    }
    if(a>b){
        a=a-eps;
        sum += (f(a)*(b-a)+((f(b)-f(a))*(b-a))/2);
    }

    printf("La surface est : %0.9Lf\n", sum);

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