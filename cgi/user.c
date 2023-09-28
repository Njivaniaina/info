#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nom[256];
    char rep_perso[256];
    int gid;
    int pid;
} User ;

int main(){
    FILE *fichier = NULL;
    int n=0;
    char buffer[256], text[256];
    User *u;

    printf("Context-Type:text/html\n\n");
    printf("<html><head><style>body{display: flex;justify-content: center;align-items: center;height: 100vh;width: 100vw;}table{border-collapse:collapse;padding:5px;}table,table tr td{border: 5px double black;padding:3px;}</style></head><body>");

    fichier = fopen("/etc/passwd", "r");
    if(fichier == NULL){
        printf("<h1>Erreur lors de l'ouverture du fichier!!!</h1>\n");
    }
    else{
        while(fgets(buffer, 256, fichier)){
            n++;
        }
        rewind(fichier);
        u = (User *)malloc(sizeof(User)*n);
        for(int i=0;i<n;i++){
            fgets(buffer, 256, fichier);
            sscanf(buffer, "%[^:]:%[^:]:%d:%d:%[^:]:%[^:]:%[^:]\n", u[i].nom, text, &u[i].pid, &u[i].gid, text, u[i].rep_perso, text);
        }

        printf("<table>");
        printf("<tr><td>Nom</td><td>Dossier personnel</td></tr>\n");
        for(int i=0;i<n;i++){
            if(u[i].pid >= 1000 && u[i].pid <= 60000)
                printf("<tr><td>%s</td><td>%s</td></tr>\n", u[i].nom, u[i].rep_perso);
        }
        printf("</table>");
        fclose(fichier);
    }

    printf("</body></html>");
    return 0;
}