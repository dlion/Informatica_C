/*
Alunno: Domenico Luciani
Classe: 4B Informatica
Esercizio pag 419 n.18: E' dato un elenco di studenti con l'indicazione per ciascuno del cognome e nome, della data di 
nascita e della data in cui si e' diplomato, i dati relativi per ciascun nominativo devono essere raggruppati in un unica 
struttura. Facendo entrare da tastiera i dati studente per studente calcolare il numero di coloro che si sono diplomati 
dopo aver compiuto 20 anni.
- Numeri di studenti non noto.

- DO WHAT YOU WANT CAUSE A PIRATE IS FREE, YOU ARE A PIRATE! -
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 3000

typedef struct data1
{
    int giorno;
    int mese;
    int anno;
}data;

typedef struct elenco
{
    data data_N;
    data data_D;    
    char nome[30];
    char cognome[30];
}studenti;

//Prototipi
int inserimento(studenti*);
int controllo(studenti*,int);

int main()
{
    studenti tizi[MAX];
    int num;
    
    //Inserimento studenti
    num=inserimento(tizi);
    
    //Controllo eta'
    printf("Il numero di studenti diplomati dopo i 20 anni e': %d\n",controllo(tizi,num));
    return 0;
}

int inserimento(studenti *tizi)
{
    int num=-1,scelta;
    
    do
    {
    	num++;
        printf("Inserisci il nome dello studente: ");
        scanf("%s",tizi[num].nome);
        printf("Inserisci il cognome dello studente: ");
        scanf("%s",tizi[num].cognome);
        do
        {
            printf("\nInserisci giorno di nascita: ");
            scanf("%d",&tizi[num].data_N.giorno);
            printf("Inserisci mese di nascita: ");
            scanf("%d",&tizi[num].data_N.mese);
            printf("Inserisci anno di nascita: ");
            scanf("%d",&tizi[num].data_N.anno);
        }while(tizi[num].data_N.giorno <= 0 || tizi[num].data_N.giorno > 31 && 
        	   tizi[num].data_N.mese <= 0 || tizi[num].data_N.mese > 12);
        
        do
        {
        	printf("\nInserisci giorno del diploma: ");
        	scanf("%d",&tizi[num].data_D.giorno);
        	printf("Inserisci mese del diploma: ");
        	scanf("%d",&tizi[num].data_D.mese);
        	printf("Inserisci anno del diploma: ");
        	scanf("%d",&tizi[num].data_D.anno);
        }while(tizi[num].data_D.giorno <= 0 || tizi[num].data_D.giorno > 31 || 
               tizi[num].data_D.mese <= 0 || tizi[num].data_D.mese > 12 || 
               tizi[num].data_D.anno <= tizi[num].data_N.anno);
       do
       {
           printf("Vuoi inserire un'altro studente ?\n1)Si\n2)No\n: ");
           scanf("%d",&scelta);
       }while(scelta <= 0 || scelta > 2);
        
     }while(scelta == 1 && num < MAX);
     
     return num+1;
}

int controllo(studenti *tizi,int num)
{
    int ris=0,i=0;

    for(i;i<num;i++)
        if((tizi[i].data_D.anno - tizi[i].data_N.anno) >= 20)
            if(tizi[i].data_D.mese >= tizi[i].data_N.mese)
                if(tizi[i].data_D.giorno >= tizi[i].data_N.giorno)
                    ris++;
    return ris;
}
            
            

