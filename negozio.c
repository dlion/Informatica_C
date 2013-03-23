/*
 * Autore: Domenico Luciani aka DLion
 * http://dlion.it
 * Primo anno della facoltà di Scienze Informatiche, Palermo.
 * Data: 23/02/2013 - 16:48
 * Esercizio 03_21 sulle unioni e sulle strutture
 * Testo dell'esercizio:
 * Aiutare il titolare del negozio a creare un archivio per la gestione della sua merce, attraverso un programma che:
 * - Aggiunga un nuovo articolo di tipo libro o maglietta, con tutte le informazioni necessarie e la quantità dei pezzi inseriti (copie del libro quantità
 *   di magliette uguali). Il programma deve assegnare un codice univoco (non negativo) di 8 cifre, via via crescente ad ogni articolo inserito.
 * - Dato il codice dell'articolo, stampi i dati relativi all'articolo. Il programma deve stampare un messaggio d'errore se l'elemento non è presente.
 *   Si usi la ricerca binaria.
 * - Dato il codice dell'articolo, stampi la quantità disponibile.
 * - Visualizzi tutti gli articoli presenti in magazzino.
 * - Simuli la vendita di un articolo su richiesta dell'utente, specificando il numero dei pezzi venduti.
 * - Calcoli il guadagno risultante dalle vendite effettuate.
 * - Termini l'esecuzione del programma.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struttura dati
typedef struct
{
    //Definisco alcune variabili
    unsigned int codice;
    float prezzo;
    //Per capire se è una maglietta o un libro
    enum {LIBRO,MAGLIA} tipo;
    int quantita;

    union
    {
        //Struttua per il libro
        
        struct
        {
            char titolo[100];
            char autore[15];
            int pagine;
        }libro;

        //Struttura per la maglietta

        struct
        {
            char motivo[30];
            char modello[30];
            unsigned short taglia;
        }maglietta;
    
    }prodotto;
    
}articolo;

//Funzione per stampare il menù iniziale, ritorna la scelta data
int menu_iniziale();
//Funzione per aggiungere gli articoli al db
articolo* add_article(articolo*,int);
//Funzione per cercare un determinato prodotto all'interno del database
int cerca(articolo*,int,int);
//Riassunto articolo
void riassunto(articolo*,int);
//Funzione per stampare i dati di un articolo
void stampa_cod(articolo*,int);
//Stampa la quantita' di un determinato articolo
void stampa_quantita(articolo*,int);
//Stampa tutti i dati del database
void stampa_tutto(articolo*,int);
//Simula la vendita di un articolo
articolo* vendi(articolo*,int,float*);

int main()
{
    articolo *db=NULL;
    int num = 0,scelta,codice,i;
    float guadagno = 0;

    do
    {
        switch(scelta = menu_iniziale() )
        {
            case 1:
                db = add_article(db,num);
                num++;
                break;
            case 2:
                riassunto(db,num);
                break;
            case 3:
                stampa_quantita(db,num);
                break;
            case 4:
                stampa_tutto(db,num);
                break;
            case 5:
                db = vendi(db,num,&guadagno);
                break;
            case 6:
                printf("\n ====== GUADAGNO ======\n"
                       "Guadagno: %f\n",guadagno
                      );
                break;
            case 7:
                break;
            default:
                puts("\n Opzione non valida \n");
        };
    }while(scelta != 7);

    free(db);
    return 0;
}


int menu_iniziale()
{
    int scelta;

    do
    {
        printf("\n -- Menu' --\n"
               "1) Aggiungi Articolo\n"
               "2) Cerca Articolo\n"
               "3) Fornisci Quantita'\n"
               "4) Visualizza tutti gli articoli\n"
               "5) Vendi articoli\n"
               "6) Calcola il guadagno\n"
               "7) Esci dal programma\n"
               "Scelta: ");
        
        scanf("%d",&scelta);

    }while(scelta < 1 || scelta > 7);

    return scelta;
}

articolo* add_article(articolo *db, int cod)
{
    //Alloco un nuovo spazio
    if((db = (articolo*)realloc(db, (cod+1)*sizeof(articolo))) == NULL)
        exit(EXIT_FAILURE);
    
    //Decido se l'articolo è una maglietta o un libro
    do
    {
        printf("\n -- Tipo di articolo --\n"
               "0)Libro\n"
               "1)Maglietta\n"
               "Scelta: ");
        scanf("%d",&(db+cod)->tipo);  //Forma equivalente: scanf("%d",&db[cod]->tipo);
    }while((db+cod)->tipo < LIBRO || (db+cod)->tipo > MAGLIA);

    //Dettagli comuni
    printf("\nInserisci il prezzo di ogni articolo: ");
    scanf("%f",&(db+cod)->prezzo);

    printf("\nInserisci quantita': ");
    scanf("%d",&(db+cod)->quantita);

    //Assegno il codice
    (db+cod)->codice = cod;

    //Metto le informazioni di ogni articolo dentro le proprie strutture
    if((db+cod)->tipo == LIBRO)
    {
        printf("\n -- Inserimento Libri --");
        printf("\nInserisci Autore: ");
        getchar();
        fgets((db+cod)->prodotto.libro.autore,sizeof((db+cod)->prodotto.libro.autore),stdin);
        printf("\nInserisci Titolo: ");
        fgets((db+cod)->prodotto.libro.titolo,sizeof((db+cod)->prodotto.libro.titolo),stdin);
        printf("\nInserisci numero Pagine: ");
        scanf("%d",&(db+cod)->prodotto.libro.pagine);
    }
    else
    {
        printf("\n -- Inserimento Magliette --");
        printf("\nInserisci motivo: ");
        getchar();
        fgets((db+cod)->prodotto.maglietta.motivo,sizeof((db+cod)->prodotto.maglietta.motivo),stdin);
        printf("\nInserisci Modello: ");
        fgets((db+cod)->prodotto.maglietta.modello,sizeof((db+cod)->prodotto.maglietta.modello),stdin);
        printf("\nInserisci taglia: ");
        scanf("%d",&(db+cod)->prodotto.maglietta.taglia);
    }

    //Ritorno il db aggiornato alla funzione main
    return db;
}

int cerca(articolo *db, int fine,int cod)
{
    int inizio = 0, centro = 0;
    fine = fine-1;

    //Ricerca Dicotomica
    while(inizio <= fine)
    {
        centro = (inizio + fine) / 2;
        
        if(cod < (db+centro)->codice)
            fine = centro-1;
        else if(cod > (db+centro)->codice)
            inizio = centro+1;
        else
            return 1;
    }

    return 0;
}

void stampa_cod(articolo *db, int cod)
{
    printf(" Codice prodotto: %.8d\n"
           " Prezzo: %.2f\n"
           " Quantita': %d\n",
           (db+cod)->codice,
           (db+cod)->prezzo,
           (db+cod)->quantita
          );

    if((db+cod)->tipo == LIBRO)
        printf(" Tipo: Libro\n"
               " Titolo: %s\n"
               " Autore: %s\n"
               " Pagine: %d\n",
               (db+cod)->prodotto.libro.titolo,
               (db+cod)->prodotto.libro.autore,
               (db+cod)->prodotto.libro.pagine
              );
    else
        printf(" Tipo: Maglietta\n"
               " Motivo: %s\n"
               " Modello: %s\n"
               " Taglia: %d\n",
               (db+cod)->prodotto.maglietta.motivo,
               (db+cod)->prodotto.maglietta.modello,
               (db+cod)->prodotto.maglietta.taglia
              );
}


void riassunto(articolo *db,int fine)
{
    int codice;

    do
    {
        printf("\n ====== RIASSUNTO PRODOTTO ======\n"
               "Inserisci il codice del prodotto da cercare: ");
        scanf("%d",&codice);
    }while(codice < 0 || codice > 99999999);

    if(!cerca(db,fine,codice))
        puts("\n ====== NESSUN ARTICOLO TROVATO ======\n");
    else
        stampa_cod(db,codice);
    puts("\n ====== FINE RIASSUNTO ======\n");
}

void stampa_quantita(articolo *db, int fine)
{
    int cod;

    do
    {
        printf("\n ====== QUANTITA' PRODOTTO ======\n"
               "Inserisci il codice del prodotto da cercare: ");
        scanf("%d",&cod);
    }while(cod < 0 || cod > 99999999);

    if(!cerca(db,fine,cod))
        puts("\n ====== NESSUN ARTICOLO TROVATO ======\n");
    else
    {
        printf("\n ====== ARTICOLO TROVATO ======\n"
               " Quantita' prodotto: %d\n",
               (db+cod)->quantita
              );
    }
}

void stampa_tutto(articolo *db, int fine)
{
    int i;

    puts("\n ====== STAMPA TUTTI GLI ARTICOLI ======");
    for(i=0; i < fine; i++)
    {
        stampa_cod(db,i);
        putchar('\n');
    }
    puts("\n ====== FINE STAMPA ARTICOLI ======\n");
}

articolo* vendi(articolo *db,int fine,float *guadagno)
{
    int cod,quanto,conto;

    do
    {
        printf("\n ====== VENDITA PRODOTTO ======\n"
               "Inserisci il codice del prodotto da cercare: ");
        scanf("%d",&cod);
    }while(cod < 0 || cod > 99999999);

    if(!cerca(db,fine,cod))
        puts("\n ====== NESSUN ARTICOLO TROVATO ======\n");
    else
    {
        puts("\n ====== ARTICOLO TROVATO ======");
        quanto = (db+cod)->quantita;
        if(quanto > 0)
        {
            printf("Inserisci quanto ne vuoi comprare: ");
            scanf("%d",&conto);
            if(conto <= quanto)
            {
                (db+cod)->quantita = quanto - conto;
                *guadagno += conto * (db+cod)->prezzo;
                puts("\n Grazie per l'acquisto!\n");
            }
            else
                puts("\nNon ne abbiamo a sufficienza!\n");
        }
        else
            puts("\nProdotto terminato!\n");
    }

    return db;
}
    
