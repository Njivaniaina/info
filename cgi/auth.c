#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char date[256];
    char time[266];
    char session[256];
    char name[256];
} User ;

int main(){
    FILE *fichier = NULL;
    int n=30;
    int c=0;
    char buffer[256], *coupe;
    /* char text[256]; */
    User *u;

    printf("Context-Type:text/html\n\n");
    printf("<html><head><style>table{border-collapse:collapse;padding:5px;}table,table tr td{border: 5px double black;padding:3px;}</style></head><body>");

    system("cat /var/log/auth.log|tail -10 > ./tmp.txt");
    system("cat /var/log/auth.log");

    fichier = fopen("./tmp.txt", "r");
    if(fichier == NULL){
        printf("<h1>Erreur lors de l'ouverture du fichier!!!</h1>\n");
    }
    else{
        u = (User *)malloc(sizeof(User)*n);
        for(int i=0;i<n;i++){
            fgets(buffer, 256, fichier);
            if((coupe=strstr(buffer, ": session"))){
                sscanf(buffer, "%[^T]T%[^.]\n", u[c].date, u[c].time);
                sscanf(coupe, ": session %s for user %[^\n(]", u[c].session, u[c].name);
                c++;
            }
        }
        printf("<table>");
        printf("<tr><td>User</td><td>Session</td><td>Time</td><td>Date</td></tr>\n");
        for(int i=0;i<c;i++){
            printf("<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>\n", u[i].name, u[i].session, u[i].time, u[i].date);
        }
        printf("</table>");
        fclose(fichier);
        remove("./tmp.txt");
    }

    printf("</body></html>");
    return 0;
}