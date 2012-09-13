/*
 * Sorgente fatto a minchia di cane tanto per far vedere come usare fwrite e fread, se avete problemi basta chiedere e STUDIARE!!
 * ~DO WHAT YOU WANT CAUSE A PIRATE IS FREE, YOU ARE A PIRATE!~
 */

#include <stdio.h>
#include <stdlib.h>


struct allievo
{
    int eta;
    char nome[20],cognome[20],classe[2];
};



struct allievo *carica(struct allievo *dati,int *n)
{
    dati = (struct allievo*)realloc(dati,((*n)+1)*sizeof(struct allievo));
    if(dati != NULL)
    {
        printf("Nome: ");
        scanf("%s",(dati+(*n))->nome);
        printf("Cognome: ");
        scanf("%s",(dati+(*n))->cognome);
        printf("Eta': ");
        scanf("%d",&(dati+(*n))->eta);
        printf("Classe: ");
        scanf("%s",(dati+(*n))->classe);
        (*n)++;
    }
    else
        printf("Impossibile allocare spazio\n");
    
    return dati;
}


void scrivi(struct allievo *dati,int n)
{
    FILE *fp;
    int i;

    if((fp = fopen("lol.dat","wb")) != NULL)
    {
        for(i=0; i < n; i++)
            fwrite((dati+i),sizeof(struct allievo),1,fp);
        printf("Dati scritti sul file.\n");
    }
    else
        printf("Impossibile aprire il file\n");
    
    fclose(fp);
    return;
}

struct allievo* leggi(struct allievo *dati,int n)
{
    FILE *fp;

    struct allievo *temp = (struct allievo*)malloc(n*sizeof(struct allievo));
    int i=0,g;

    if((fp = fopen("lol.dat","rb")) != NULL)
    {
        while(!feof(fp))
        {
            fread((temp+i),sizeof(struct allievo),1,fp);
            i++;
        };
        printf("Dati letti dal file: %d\n",i-1);
    
        for(g=0; g < i-1; g++)
            printf("\nNome:%s\nCognome:%s\nEta':%d\nClasse:%s\n",(temp+g)->nome,(temp+g)->cognome,(temp+g)->eta,(temp+g)->classe);
    }
    else
        printf("Impossibile aprire il file\n");
    
    fclose(fp);

    return temp;
}

int main()
{
    int risp,n=0;
    struct allievo *dati=NULL;


    do
    {
        printf("\nMenu\n"
               "1)Carica\n"
               "2)Scrivi\n"
               "3)Leggi\n"
               "4)Esci\n"
               "Risposta: ");
        scanf("%d",&risp);

        switch(risp)
        {
            case 1:
                dati = carica(dati,&n);
                break;
            case 2:
                scrivi(dati,n);
                break;
            case 3:
                dati = leggi(dati,n);
                break;
            case 4:
                printf("Goodbye\n");
                break;
        }
    }while(risp != 4);
    free(dati);
    return 0;
}









