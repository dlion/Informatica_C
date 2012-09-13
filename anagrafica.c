/*Autore: Domenico Luciani
 * Classe: 4°B
 * Data: 13-03-11
 * 
 * Descrizione: Si vuole gestire l'anagrafica degli abitanti di un piccolo paese per ciascuno di essi occorre specificare, oltre al cognome, al nome,alla data e al  luogo di nascita
 * ,il sesso, lo stato civile (libero, coniugato, vedovo), l'attuale indirizzo di residenza e la professione.
 * Dopo avere sviluppato un'attenta analisi scrivere il programma che consenta:
 * * la memorizzazione
 * * la stampa totale
 * * la ricerca per cognome e nome
 * * il calcolo della percentuale dei liberi, coniugati, vedovi sul totale
 * * il calcolo del numero totale di abitanti e delle percentuali di maschi e femmine
 */

//Librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Database
#define DB "database.txt"

//Struttura
typedef struct
{
    char nome[20],cognome[20],luogo[20],residenza[20],professione[20],sesso,stato;
    int giorno,mese,anno;
}info;

//Prototipi
info *aggiungi(info*,int*);
info *preleva(info*,int*);
void stampa(info*);
void ricerca(info*);
void perc_stato(info*);
void perc_sesso(info*);

//Main
int main()
{
    info *db=NULL;
    int scelta,numero=0;

    do
    {
        printf("-- MENU --\n\n"
               "1. Aggiungi abitante\n"
               "2. Stampa abitanti\n"
               "3. Cerca un abitante\n"
               "4. Percentuale liberi, vedovi, coniugati\n"
               "5. Stampa numero totale di abitanti e percentuali maschi e femmine\n"
               "6. Esci\n"
               "Scelta: ");
        scanf("%d",&scelta);
        
        switch(scelta)
        {
            case 1:
                db = aggiungi(db,&numero);
                break;
            case 2:
                stampa(db);
                break;
            case 3:
                ricerca(db);
                break;
            case 4:
                perc_stato(db);
                break;
            case 5:
                perc_sesso(db);
                break;
            case 6:
                printf("Programma terminato.\n");
                break;
        };
    }while(scelta != 6);
    
    free(db);
    return 0;
}

//Funzione per aggiungere gli abitanti
info* aggiungi(info *db,int *numero)
{
    FILE *f;
    printf("\n-- INSERIMENTO --\n\n");
    //Inserisce il tutto nella tabella
    if((db = (info*) realloc(db,((*numero)+1)*sizeof(info))) != NULL)
    {
        printf("Inserisci nome: ");
        scanf("%s",(db+(*numero))->nome);
        printf("Inserisci cognome: ");
        scanf("%s",(db+(*numero))->cognome);
        printf("Inserisci data di nascita: ");
        scanf("%d/%d/%d",&(db+(*numero))->giorno,&(db+(*numero))->mese,&(db+(*numero))->anno);
        printf("Luogo di nascita: ");
        scanf("%s",(db+(*numero))->luogo);
        getchar();
        printf("Sesso m/f : ");
        scanf("%c",&(db+(*numero))->sesso);
        getchar();
        printf("Stato civile l/c/v (libero/coniugato/vedovo) : ");
        scanf("%c",&(db+(*numero))->stato);
        printf("Residenza: ");
        scanf("%s",(db+(*numero))->residenza);
        printf("Professione: ");
        scanf("%s",(db+(*numero))->professione);
        if((f = fopen(DB,"ab")) != NULL)
        {
            //Scrive i dati sul database
            fwrite(db+(*numero),sizeof(info),1,f);
            printf("\n-- Dati salvati --\n");
            fclose(f);
        }            
        else
            printf("Impossibile aprire il file!\n");
        (*numero)++;
    }
    else
        printf("Impossibile allocare spazio!\n");
    putchar('\n');
    return db;
}

//Funzione per prelevare i dati dal database
info* preleva(info *db,int *n)
{
    FILE *f;

    if((f = fopen(DB,"rb")) != NULL)
    {
        //Legge il file e mette i vari dati letti nella tabella fornendo anche il numero di dati letti
        while(!feof(f))
        {
           if((db = (info*)realloc(db,((*n)+1)*sizeof(info))) != NULL)
           {
               fread(db+(*n),sizeof(info),1,f);
               (*n)++;
           }
           else
               printf("Impossibile allocare memoria\n");
        }
    }
    else
        printf("Impossibile aprire il file!\n");
    fclose(f);
    return db;
}
    
//Stampa tutti gli abitanti presenti nel database
void stampa(info *db)
{
    int g=0,i;

    printf("\n-- STAMPA --\n\n");
    db = preleva(db,&g);
    for(i=0; i < g-1; i++)
        printf("\nNome: %s\n"
               "Cognome: %s\n"
               "Data di nascita: %d/%d/%d\n"
               "Luogo di nascita: %s\n"
               "Sesso: %c\n"
               "Stato civile: %c\n"
               "Residenza: %s\n"
               "Professione: %s\n",(db+i)->nome,(db+i)->cognome,(db+i)->giorno,(db+i)->mese,(db+i)->anno,(db+i)->luogo,(db+i)->sesso,(db+i)->stato,(db+i)->residenza,(db+i)->professione);    
    putchar('\n');
}

//Effettua una ricerca per nome e cognome nel database
void ricerca(info *db)
{
    int n=0,find=-1,i;
    char nome[20],cognome[20];
    
    printf("Inserisci il nome da cercare: ");
    scanf("%s",nome);
    printf("Inserisci il cognome da cercare: ");
    scanf("%s",cognome);
    
    db = preleva(db,&n);

    for(i=0; i < n-1; i++)
        if((strcmp((db+i)->nome,nome)) == 0 && (strcmp((db+i)->cognome,cognome)) == 0)
            find = i;
    
    if(find != -1)
        printf("\n-- ABITANTE TROVATO --\n"
       "\nNome: %s\n"
       "Cognome: %s\n"
       "Data di nascita: %d/%d/%d\n"
       "Luogo di nascita: %s\n"
       "Sesso: %c\n"
       "Stato civile: %c\n"
       "Residenza: %s\n"
       "Professione: %s\n",(db+find)->nome,(db+find)->cognome,(db+find)->giorno,(db+find)->mese,(db+find)->anno,(db+find)->luogo,(db+find)->sesso,(db+find)->stato,(db+find)->residenza
       ,(db+find)->professione);
    else
        printf("\n-- ABITANTE NON TROVATO --\n\n");
}

//Calcola la percentuale di liberi,coniuagati e vedovi presenti nel database
void perc_stato(info *db)
{
    int tot=0,i;
    float lib=0,vedo=0,coni=0;

    db = preleva(db,&tot);

    for(i=0; i < tot-1; i++)
    {
        switch((db+i)->stato)
        {
            case 'l':
                lib++;
                break;
            case 'v':
                vedo++;
                break;
            case 'c':
                coni++;
                break;
        };
    }
    printf("\n-- PERCENTUALE STATI SOCIALI --\n"
           "Liberi: %f%%\n"
           "Coniugati: %f%%\n"
           "Vedovi: %f%%\n\n",((lib/(tot-1))*100),((coni/(tot-1))*100),((vedo/(tot-1))*100));
}

//Calcola la percentuale di maschi e femmine e il numero di abitanti presenti nel database
void perc_sesso(info *db)
{
    int tot=0,i;
    float maschi=0,femmine=0;

    db = preleva(db,&tot);

    for(i=0; i < tot-1; i++)
    {
        if(((db+i)->sesso) == 'm')
            maschi++;
        else
            femmine++;
    }

    printf("\n-- NUMERO ABITANTI E PERCENTUALE SESSO --\n"
           "Numero totale: %d\n"
           "Maschi: %f%%\n"
           "Femmine: %f%%\n\n",tot-1,(maschi/(tot-1))*100,(femmine/(tot-1))*100);
}
