/*
 * Autore: Domenico Luciani
 * Classe: 4 B Informatica
 * Descrizione: Realizzare un programma in linguaggio C che permetta di gestire le informazioni riguardanti i quadri. 
 * I dati da trattare sono: titolo, autore, prezzo, larghezza, altezza, anno.
 * Il programma deve permettere di:
 * 1) caricare da un file i dati dei quadri e visualizzarli ordinati per autore;
 * 2) salvare su un altro file i dati dei quadri di prezzo superiore ad un prezzo fornito in input ed ordinati per autore;
 * 3) visualizzare tutti i dati di un quadro fornito in input il suo titolo;
 * 4) visualizzare il numero totale di quadri di una determinata larghezza ed altezza fornite in input. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nomefile "db.txt"
#define altrofile "altrodb.txt"

typedef struct
{
    char titolo[20],autore[20];
    int anno;
    float prezzo,larg,alt;
}quadri;

quadri *ordina(quadri *db, int n)
{
    int i=0,j;
    quadri *tmp=(quadri*)malloc(sizeof(quadri));
    
    for(i; i<n; i++)
    {
        for(j=i+1; j<n-1; j++)
        {
            if((strcmp((db+i)->autore,(db+j)->autore)) > 0)
            {
                *tmp=*(db+i);
                *(db+i)=*(db+j);
                *(db+j)=*tmp;
            }
        }
    }
    return db;
}

void stampa(quadri *db, int n)
{
    int i;
    
    for(i=0; i<n-1; i++)
        printf("\nTitolo: %s\nAutore: %s\nAnno: %d\nPrezzo: %f\nLarghezza: %f\nAltezza: %f\n\n",(db+i)->titolo,(db+i)->autore,(db+i)->anno,(db+i)->prezzo,(db+i)->larg,(db+i)->alt);
}

quadri *carica_dati(quadri *db, int *n)
{
    FILE *f;
    
    if((f=fopen(nomefile,"rb")) != NULL)
    {
        while(!feof(f))
        {
           db=(quadri*)realloc(db,((*n)+1)*sizeof(quadri));
           fread((db+(*n)),sizeof(quadri),1,f);
           (*n)++;
        }}
    else
    {
        printf("File impossibile da aprire!\n");
        exit(1);
    }

    db=ordina(db,*n);
    stampa(db,*n);
    
    fclose(f);
    return db;
}

quadri *scrivi_dati(quadri *db, int n)
{
    FILE *f;
    float prezzo2;
    int i;

    printf("Inserisci il prezzo: ");
    scanf("%f",&prezzo2);

    if((f=fopen(altrofile,"ab")) != NULL)
    {
        for(i=0; i<n; i++)
            if((db+i)->prezzo > prezzo2)
                fwrite((db+i),sizeof(quadri),1,f);
    }
    else
    {
        printf("Impossibile aprire il file!\n");
        exit(1);
    }

    fclose(f);
    return db;
}

void totale(quadri *db, int n)
{
    float a,l;
    int h=0,i;

    printf("Larghezza e altezza: ");
    scanf("%f %f",&a,&l);
    
    for(i=0; i<n; i++)
        if((db+i)->larg > a && (db+i)->alt > l)
            h++;
    printf("TOTALE %d\n",h);
    
    return;
}

quadri *inserisci_dati(quadri *db, int *n)
{
    FILE *f;
  
    db=(quadri*)realloc(db,((*n)+1)*sizeof(quadri));

    if(db == NULL)
    {
        printf("Impossibile allocare!\n");
        exit(1);
    }
    else
    {
        printf("Inserisci Titolo: ");
        scanf("%s",(db+(*n))->titolo);
        printf("Inserisci Autore: ");
        scanf("%s",(db+(*n))->autore);
        printf("Inserisci Anno: ");
        scanf("%d",&(db+(*n))->anno);
        printf("Inserisci Larghezza: ");
        scanf("%f",&(db+(*n))->larg);
        printf("Inserisci Altezza: ");
        scanf("%f",&(db+(*n))->alt);
        printf("Inserisci Prezzo: ");
        scanf("%f",&(db+(*n))->prezzo);

        if((f=fopen(nomefile,"ab")) != NULL)
        {
            fwrite((db+(*n)),sizeof(quadri),1,f);
            (*n)++;
        }
        else
        {
            printf("File impossibile da aprire!\n");
            exit(1);
        }
        fclose(f);
    }

    return db;
}

int main()
{
    quadri *db=NULL;
    int n=0,risp;

    do
    {
        printf("-- MENU' --\n1. Inserisci dati\n2. Carica dati\n3. Scrivi dati ordinati\n4. Visualizza dati\n5. Numero totale quadri con altezza e larghezza maggiore\n6. Esci\nRisposta: ");
        scanf("%d",&risp);
        switch(risp)
        {
            case 1:
                db=inserisci_dati(db,&n);
                break;
            case 2:
                db=carica_dati(db,&n);
                break;
            case 3:
                db=scrivi_dati(db,n);
                break;
            case 4:
                stampa(db,n);
                break;
            case 5:
                totale(db,n);
                break;
            case 6:
                break;
            default:
                printf("Risposta errata!\n");
                break;
        };
    }while(risp != 6);

    free(db);
    return 0;
}

