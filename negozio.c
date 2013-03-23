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
//Funzione per listare le caratteristiche di un determinato articolo dando il codice esatto
void riassunto(articolo*,int);
//Funzione per aggiungere gli articoli al db
articolo* add_article(articolo*,int);

int main()
{
    articolo *db=NULL;
    int cod = 0,scelta;

    do
    {
        switch(scelta = menu_iniziale() )
        {
            case 1:
                db = add_article(db,cod);
                //Stampo un riassunto
                riassunto(db,cod);
                cod++;
                break;
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
        printf(" -- Menu' --\n"
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

void riassunto(articolo *db, int cod)
{
    printf("\n ====== RIASSUNTO ====== \n"
           " Codice prodotto: %.8d\n"
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

    puts(" ====== FINE RIASSUNTO ======\n");
}


articolo* add_article(articolo *db, int cod)
{
    //Alloco un nuovo spazio
    if((db = (articolo*)realloc(db, (cod+1)*sizeof(articolo))) == NULL)
        exit(EXIT_FAILURE);
    
    //Decido se l'articolo è una maglietta o un libro
    do
    {
        printf(" -- Tipo di articolo --\n"
               "0)Libro\n"
               "1)Maglietta\n"
               "Scelta: ");
        scanf("%d",&(db+cod)->tipo);  //Forma equivalente: scanf("%d",&db[cod]->tipo);
    }while((db+cod)->tipo < LIBRO || (db+cod)->tipo > MAGLIA);

    //Dettagli comuni
    printf("Inserisci il prezzo di ogni articolo: ");
    scanf("%f",&(db+cod)->prezzo);

    printf("Inserisci quantita': ");
    scanf("%d",&(db+cod)->quantita);

    //Assegno il codice
    (db+cod)->codice = cod;

    //Metto le informazioni di ogni articolo dentro le proprie strutture
    if((db+cod)->tipo == LIBRO)
    {
        printf(" -- Inserimento Libri --");
        printf("\nInserisci Autore: ");
        getchar();
        fgets((db+cod)->prodotto.libro.autore,sizeof((db+cod)->prodotto.libro.autore),stdin);
        printf("Inserisci Titolo: ");
        fgets((db+cod)->prodotto.libro.titolo,sizeof((db+cod)->prodotto.libro.titolo),stdin);
        printf("Inserisci numero Pagine: ");
        scanf("%d",&(db+cod)->prodotto.libro.pagine);
    }
    else
    {
        printf(" -- Inserimento Magliette --");
        printf("\nInserisci motivo: ");
        getchar();
        fgets((db+cod)->prodotto.maglietta.motivo,sizeof((db+cod)->prodotto.maglietta.motivo),stdin);
        printf("Inserisci Modello: ");
        fgets((db+cod)->prodotto.maglietta.modello,sizeof((db+cod)->prodotto.maglietta.modello),stdin);
        printf("Inserisci taglia: ");
        scanf("%d",&(db+cod)->prodotto.maglietta.taglia);
    }

    //Ritorno il db aggiornato alla funzione main
    return db;
}
