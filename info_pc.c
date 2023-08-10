#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pc{
	char marque[256];
	char nom[256];
	int numero;
	char mac[256];
} Pc ;

typedef struct Personne{
	char nom[256];
	char prenom[256];
	int numero;
	char tel[256];
	char email[256];
	char adresse[256];
	char naissance[256];
	char lieu[256];
	int bacc;
	char genre[256];
	char cin[256];
	char url[256];
} Personne ;

void tri(char texte[256][256], int l){
    char *tmp = (char*)malloc(256);
    int k=0;
    for(int i=0; i<l ;i++){
        for(int j=i+1; j<l ; j++){
            k=0;
        miverina:
            if(texte[i][k] > texte[j][k]){
                strcpy(tmp, texte[i]);
                strcpy(texte[i], texte[j]);
                strcpy(texte[j], tmp);
            }
            if(texte[i][k] == texte[j][k]){
                k++;
                goto miverina;
            }
        }
    }
}

void copier(Personne *copie, Personne Acopie){
	strcpy(copie->nom, Acopie.nom);
	strcpy(copie->prenom, Acopie.prenom);
	copie->numero = Acopie.numero;
	strcpy(copie->tel, Acopie.tel);
	strcpy(copie->email, Acopie.email);
	strcpy(copie->adresse, Acopie.adresse);
	strcpy(copie->naissance, Acopie.naissance);
	strcpy(copie->lieu, Acopie.lieu);
	copie->bacc = Acopie.bacc;
	strcpy(copie->genre, Acopie.genre);
	strcpy(copie->cin, Acopie.cin);
	strcpy(copie->url, Acopie.url);
}

void trier_nom(Personne *olona, int n){
	Personne tmp;
    int k=0;
    for(int i=0; i<n ;i++){
        for(int j=i+1; j<n ; j++){
            k=0;
        miverina:
            if(olona[i].nom[k] > olona[j].nom[k]){
				copier(&tmp, olona[i]);
				copier(&olona[i], olona[j]);
				copier(&olona[j], tmp);
            }
            if(olona[i].nom[k] == olona[j].nom[k]){
                k++;
                goto miverina;
            }
        }
    }
}

void trier_prenom(Personne *olona, int n){
	Personne tmp;
    int k=0;
    for(int i=0; i<n ;i++){
        for(int j=i+1; j<n ; j++){
            k=0;
        miverina:
            if(olona[i].prenom[k] > olona[j].prenom[k]){
				copier(&tmp, olona[i]);
				copier(&olona[i], olona[j]);
				copier(&olona[j], tmp);
            }
            if(olona[i].prenom[k] == olona[j].prenom[k]){
                k++;
                goto miverina;
            }
        }
    }
}

void copier_pc(Pc *copie, Pc Acopie){
	strcpy(copie->mac, Acopie.mac);
	strcpy(copie->nom, Acopie.nom);
	copie->numero=Acopie.numero;
	strcpy(copie->marque, Acopie.marque);
}

Pc *tri_num_mac(Pc *pc, int n){
	Pc *tmp;
	tmp = (Pc*)malloc(sizeof(Pc)*n);

	for(int i=0;i<46;i++){
		strcpy(tmp[i].mac, "");
		strcpy(tmp[i].marque, "");
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<46;j++){
			if(pc[i].numero == j){
				copier_pc(&tmp[j], pc[i]);
			}
		}
	}
	return tmp;
}

int principal(){
	char teny[256][256];
	Personne olona[46];
	Pc pc[46];
	Pc *ordi;
	FILE *info;
	int n=0, isa=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Ity dia fakana fotsiny ilay ao anatin'ilay 'fichier' misy ny mombamomba ny olona tsirairay
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	isa=0;
	info = fopen("data_info.csv", "r");
	if( info == NULL ){
		printf("Il y a une erreur pendant l'ouverture du fichier!!!");
	}
	else{
		fgets(teny[0], 256, info);
		while (fgets(teny[isa], 500, info) != NULL){
			sscanf(teny[isa], "%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]", olona[isa].nom, olona[isa].prenom, &olona[isa].numero, olona[isa].tel, olona[isa].email, olona[isa].adresse, olona[isa].naissance, olona[isa].lieu, &olona[isa].bacc, olona[isa].genre, olona[isa].cin, olona[isa].url);
			isa++;
		}
		for(int i=0; i<n ; i++){
			fprintf(info, "%s\n", teny[i]);
		}
		fclose(info);
	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Ity dia fakana fotsiny ilay ao anatin'ilay 'fichier' mombamomba an'ny mac
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	n=0;
	info = fopen("data_mac.csv", "r");
	if( info == NULL ){
		printf("Il y a une erreur pendant l'ouverture du fichier!!!");
	}
	else{
		while (fgets(teny[n], 256, info) != NULL){
			sscanf(teny[n], "%[^|]|%[^-]-%d|%[^\n]", pc[n].mac, pc[n].nom, &pc[n].numero, pc[n].marque);
			n++;
		}
		fclose(info);
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Ity dia fandaharana ilay ao anatin'ilay 'fichier'
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	trier_nom(olona, isa);  //Mandahatra ny anaran'ireo olona fotsiny 
	ordi = tri_num_mac(pc, n);

	info = fopen("information.csv", "w");
	if( info == NULL ){
		printf("Il y a une erreur pendant l'ouverture du fichier!!!");
	}
	else{
		fprintf(info, "Nom,Prénom,Numero,Téléphone,E-mail,Andresse,Date de naissance,Lieu de naissance,Date de bacc,Genre,CIN,url\n");
		for(int i=0; i<41 ; i++){
			fprintf(info, "%s,%s,%d,%s,%s,%s,%s,%s,%d,%s,%s,%s\n", olona[i].nom, olona[i].prenom, i+1, olona[i].tel, olona[i].email, olona[i].adresse, olona[i].naissance, olona[i].lieu, olona[i].bacc, olona[i].genre, olona[i].cin, olona[i].url);
		}
		fclose(info);
	}

	return 0;
}
