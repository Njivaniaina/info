#include <stdio.h>
#include <math.h>

float f(float a);

int main(){
    FILE *fichier=NULL;
    FILE *plot=NULL;

    fichier = fopen("points.txt", "w");
    if(fichier != NULL){
        for(int i=1;i<100;i++){
            fprintf(fichier, "%d   %f\n", i, f(i));
        }
        fclose(fichier);
    }
    else{
        printf("Erreur de l'ouverture du fichier/\n");
    }

    plot=popen("gnuplot -persistent", "w");
    if(plot != NULL){
        fprintf(plot, "plot \"points.txt\" using 1:2 with lines\n");
        fprintf(plot, "exit\n");
        pclose(plot);
    }
    else{
        printf("Erreur du commande gnuplot/\n");
    }

    return 0;
}

float f(float a){
    return (log(a)-1);
}