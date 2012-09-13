/*
 * Autore: Domenico Luciani
 *
 * Classe: 4B informatica Abacus
 *
 * Consegna: Realizzare un programma in linguaggio C per gestire una catena di alberghi e le prenotazioni delle stanze.
 * La tabella ALBERGHI contiene per ogni albergo le seguenti informazioni: codice albergo, nome, localita', numero stelle.
 * Ogni albergo puo' avere un numero di stanze non definibili a priori.
 * Le caratteristiche delle STANZE sono: numero di stanza, numero di posti letto, se e' libera o occupata, codice albergo (per indicare in quale albergo si trova la stanza)
 * Occorre sviluppare le seguenti funzionalita':
 * *Caricamento degli alberghi;
 * *Stampa delle caratteristiche di un albergo di cui e' fornito il codice;
 * *Dato il codice di un albergo, stampa dall'elenco delle stanze occupate con il relativo numero di posti ed il numero totale di posti occupati;
 * *Dato un numero di persone, stampa dell'elenco degli alberghi che possono ospitarle;
 * 
 * Informazioni: La struttura STANZE e' annidata dentro la struttura ALBERGHI;
 * la funzione carica i valori degli alberghi, dopo tramite l'apposita funzione carica i valori delle stanze, 
 * dopo alloca un nuovo spazio in caso si volesse inserire un nuovo albergo successivamente.
 *  
 *  **************************************************************
 * -- DO WHAT YOU WANT CAUSE A PIRATE IS FREE, YOU ARE A PIRATE! --
 *  **************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

//Strutture.
typedef struct
{
    int n_stanza;
    int np_letto;
    int stato;
}STANZE;

typedef struct
{
    int codice_h;
    char nome[20];
    char luogo[20];
    int n_stelle;
    int n_stanze;
    STANZE *stanza;
}ALBERGHI;

//Prototipi:
//Permette l'inserimento delle stanze.
void ins_s(ALBERGHI*);
//Carica alberghi.
ALBERGHI *carica(ALBERGHI*, int*);
//Stampa info su un'albergo dato.
void h_info(ALBERGHI*,int);
//Stampa info sulle stanze.
void s_info(ALBERGHI*,int);
//Controlla se ci sono posti liberi.
void free_places(ALBERGHI*,int);

//Main.
int main()
{
    ALBERGHI *catena=NULL;
    int scelta,numero=0;

    do
    {
        printf("\n- MENU -\n"
                "1)Aggiungi Hotel\n"
                "2)Info Hotel\n"
                "3)Info Stanze\n"
                "4)Controlla disponibilita' posti\n"
                "5)Esci\n"
                "Risposta: ");
        scanf("%d",&scelta);
        putchar('\n');
        switch(scelta)
        {
            case 1:
                catena = carica(catena,&numero);
                break;
            case 2:
                h_info(catena,numero);
                break;
            case 3:
                s_info(catena,numero);
                break;
            case 4:
                free_places(catena,numero);
                break;
            default:
                break;
        }
    }while(scelta != 5);

    free(catena);
    return 0;
}

void free_places(ALBERGHI *catena,int num)
{
    int numero,i,j;

    printf("Inserisci numero di persone: ");
    scanf("%d",&numero);

    for(i=0; i < num; i++)
        for(j=0; j < (catena+i)->n_stanze; j++)
            if( (((catena+i)->stanza)+j)->stato == 0 && (((catena+i)->stanza)+j)->np_letto >= numero)
                printf("Posti disponibili nell'albergo: %s\n"
                       "Codice albergo: %d\n"
                       "Presente stanza numero %d con %d posti letto disponibili\n\n",
                       (catena+i)->nome,
                       (catena+i)->codice_h,
                       (((catena+i)->stanza)+j)->n_stanza,
                       (((catena+i)->stanza)+j)->np_letto
                      );
            else
                printf("Nessun posto disponibile.\n");

    return;
}
    
void s_info(ALBERGHI *catena,int numero)
{
    int codice,trovato=0,occ=0,occ1=0,i,j;

    printf("- INFO STANZE -\nInserisci codice albergo: ");
    scanf("%d",&codice);

    for(i=0; i < numero; i++)
    {
        //Se il codice e' uguale significa che ha trovato l'hotel
        if(codice == (catena+i)->codice_h)
        {
            trovato=1;
            //Gira tutte le stanze.
            for(j=0; j < (catena+i)->n_stanze; j++)
            {
                //Controlla se la stanza e' occupata.
                if( (((catena+i)->stanza)+j)->stato == 1)
                {
                    printf("Stanza %d occupata.\n"
                           "Posti Letto: %d\n",
                           (((catena+i)->stanza)+j)->n_stanza,
                           (((catena+i)->stanza)+j)->np_letto
                          );
                    occ++;
                    occ1 += (((catena+i)->stanza)+j)->np_letto;
                }
            }
            printf("Totale stanze occupate %d dell'albergo %s su %d\n"
                   "Totale posti letto occupati: %d\n",
                    occ,
                    (catena+i)->nome,
                    (catena+i)->n_stanze,
                    occ1
                   );
        }
    }
    if(trovato == 0) printf("Nessun'albergo trovato!\n");
    return;
}

void ins_s(ALBERGHI *catena)
{
    int i;
    //Alloca lo spazio necessario per le stanze.
    if((catena->stanza = (STANZE*)malloc((catena->n_stanze)*sizeof(STANZE))) == NULL)
    {
        printf("Impossibile inserire stanze.\n");
        exit(1);
    }

    printf("\n- INSERIMENTO STANZA -");
    for(i=0; i < catena->n_stanze; i++)
    {
        printf("\nInserisci numero stanza %d: ",i+1);
        scanf("%d",&((catena->stanza)+i)->n_stanza);
        printf("Inserisci numero posti letto: ");
        scanf("%d",&((catena->stanza)+i)->np_letto);
        printf("Inserisci se la stanza e' libera (0=libera, 1=occupata): ");
        scanf("%d",&((catena->stanza)+i)->stato);
    }
    printf("Stanze inserite correttamente!\n\n");
    return;
}

ALBERGHI *carica(ALBERGHI *catena,int *numero)
{
    if((catena = (ALBERGHI*)realloc(catena,((*numero)+1)*sizeof(ALBERGHI))) == NULL)
        exit(1);

    
    printf("\n- INSERIMENTO ALBERGO -\nInserisci codice albergo: ");
    scanf("%d",&(catena+(*numero))->codice_h);
    printf("Inserisci nome: ");
    scanf("%s",(catena+(*numero))->nome);
    printf("Inserisci Localita': ");
    scanf("%s",(catena+(*numero))->luogo);
    printf("Inserisci numero stelle: ");
    scanf("%d",&(catena+(*numero))->n_stelle);
    printf("Inserisci numero di stanze: ");
    scanf("%d",&(catena+(*numero))->n_stanze);
    //Funzione per inserire le stanze.
    ins_s(catena+(*numero));
    (*numero)++;
    return catena;
}

void h_info(ALBERGHI *catena,int numero)
{
    int codice,i,j,trovato=0;

    printf("\n- STAMPA INFO -\nInserisci il codice dell'albergo: ");
        if (catena == NULL)
        {
            printf("Impossibile effettuare operazioni.\n");
            exit(1);
        }
    scanf("%d",&codice);

    for(i=0; i < numero; i++)
    {
        if( (catena+i)->codice_h == codice)
        {
            trovato = 1;
            printf("\n- INFO ALBERGO -\n\n"
                   "Codice albergo: %d\n"
                   "Nome: %s\n"
                   "Localita': %s\n"
                   "Stelle: %d\n"
                   "Numero stanze: %d\n\n"
                   "- INFO STANZE -\n\n",
                   (catena+i)->codice_h,
                   (catena+i)->nome,
                   (catena+i)->luogo,
                   (catena+i)->n_stelle,
                   (catena+i)->n_stanze
                  );

            for(j=0; j < (catena+i)->n_stanze; j++)
                printf("Stanza numero: %d\n"
                       "Posti letto: %d\n"
                       "Libera (0=si,1=no): %d\n\n",
                       (((catena+i)->stanza)+j)->n_stanza,
                       (((catena+i)->stanza)+j)->np_letto,
                       (((catena+i)->stanza)+j)->stato
                      );
        }
    }
    if (trovato == 0) printf("Nessun'albergo trovato!\n");
    return;
}

