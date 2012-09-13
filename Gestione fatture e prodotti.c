/*
Programma gestione di prodotti e di fatture di vendita dei prodotti
Le caratteristiche di un prodotto sono:
*codice del prodotto (Identificativo numerico intero)
*denominazione del prodotto.
*prezzo

Le caratteristiche di una fattura sono:
*numero (identificativo numerico progressivo della fattura)
*data
*elenco dei prodotti venduti con la fattura (tramite loro codice)

Realizzare il programma in modo tale che sia possibile:
*caricare ogni singolo prodotto (fornendo in input tutti i suoi dati)
*stampare i dati di un prodotto (fornendo in input il codice del prodotto)
*caricare una fattura (fornendo in input tutti i suoi dati con un numero di prodotti variabile in base alle indicazioni dell'utente)
*stampare una fattura, con tutti i suoi dati e l'importo totale della fattura (fornendo in input il numero della fattura)
*stampare tutte le fatture in cui e'  presente un prodotto (fornito in input)
*/
 
#include <stdio.h>
#include <stdlib.h>

//Strutture
typedef struct
{
   int codice_p;
   char nome[20];
   float prezzo;
}prodotto;

typedef struct 
{
  short int unsigned giorno,mese,anno;
}date;

typedef struct
{
   int num_f;
   date data;
   int *prodotti;
}fattura;

prodotto* carica_prodotto(prodotto*,int*);
int cerca(int,prodotto*,int);
void stampa_prodotto(prodotto*,int);
fattura* carica_fattura(fattura*,int*,prodotto*,int,int*);
void stampa_fattura(fattura*,int,prodotto*,int, int*);
void stampa_fattura_prodotto(fattura*,int,prodotto*,int,int*);

int main()
{
    int scelta;
   //Variabili prodotti
    prodotto *archivio_p=NULL; 
    int num_p=0;
    //Variabili fatture
    fattura *archivio_f=NULL;
    int num_f=0,*n_p=NULL;
    do
    {
        printf("--Menu--\n"
               "1)Carica un singolo prodotto\n"
               "2)Stampa i dati di un prodotto\n"
               "3)Carica una fattura\n"
               "4)Stampa i dati di una fattura\n"
               "5)Stampa le fatture in cui e' presente un prodotto\n"
               "6)Esci\n"
               "Scelta: ");
        scanf("%d",&scelta);
        getchar();
        switch(scelta)
        {
            case 1:
                  archivio_p = carica_prodotto(archivio_p,&num_p);
                  break;
            case 2:
                  stampa_prodotto(archivio_p,num_p);
                  break;
            case 3:
                  archivio_f = carica_fattura(archivio_f,&num_f,archivio_p,num_p,n_p);
                  break;
            case 4:
                  stampa_fattura(archivio_f,num_f,archivio_p,num_p,n_p);
                  break;
            case 5:
                   stampa_fattura_prodotto(archivio_f,num_f,archivio_p,num_p,n_p);
                   break;
            default:
                  break;
        }
    }while(scelta != 6);
    
    free(archivio_p);
    system("PAUSE");
    return 0;
}    

void stampa_fattura_prodotto(fattura *archivio_f,int numb_f,prodotto *archivio_p,int num_p,int *n_p)
{
   int codice,pos,i,j;
   printf("Inserisci codice prodotto da cercare: ");
   scanf("%d",&codice);
   pos = cerca(codice,archivio_p,num_p);
   if(pos == -2)
   {
      printf("Prodotto non trovato!\n");
      return;
   }
   printf("Prodotto Trovato!\n"
          "Nome: %s\n"
          "Prezzo: %f\n"
          "Codice: %d\n"
          "Trovato nelle fatture numero: "
          ,(archivio_p+pos)->nome
          ,(archivio_p+pos)->prezzo
          ,(archivio_p+pos)->codice_p
          );
   for(i=0; i <= numb_f; i++)
      for(j=0; j <= (*(n_p+i)); j++)
         if(codice == (*(((archivio_f+i)->prodotti)+j)))
            printf("%d ",i);
   putchar('\n');
   return;
}
   


void stampa_fattura(fattura *archivio_f,int numb_f,prodotto *archivio_p,int num_p,int *n_p)
{
     int i,n_f,pos;
     float somma=0;
     do
     {
       printf("Sono presenti %d fatture\nInserisci il numero della fattura da cercare: ",numb_f);
       scanf("%d",&n_f);
       if(n_f > numb_f || n_f < 0)
              printf("Numero errato!\n");
     }while(n_f > numb_f || n_f < 0);
     printf("Fattura numero: %d\n"
            "Data: %d/%d/%d\n"
            "%d Prodotti Assegnati alla fattura:\n"
            "N\t|\tNOME\t|\tPREZZO\t|\tCODICE\t|\n"
            ,(archivio_f+n_f)->num_f
            ,(archivio_f+n_f)->data.giorno
            ,(archivio_f+n_f)->data.mese
            ,(archivio_f+n_f)->data.anno
            ,(*(n_p+n_f))+1
            );
            
     for(i=0; i < (*(n_p+n_f)); i++)
     {
              pos = cerca(*(((archivio_f+n_f )->prodotti)+i),archivio_p,num_p);
              printf("%d)\t|\t%s\t%f\t%d\n"
                     ,i+1
                     ,(archivio_p+pos)->nome
                     ,(archivio_p+pos)->prezzo
                     ,(archivio_p+pos)->codice_p
                     );
              somma += (archivio_p+pos)->prezzo;
     }
     printf("Importo totale fattura: %f\n",somma);
     printf("Fine elenco prodotti assegnati\n");
     return;
}




fattura *carica_fattura(fattura *archivio_f,int *num,prodotto *archivio_p,int num_p,int *n_p)
{
   int codice,posi,*archivio_temp=NULL,again,*p_temp=NULL;
   
   if((archivio_f = (fattura*)realloc(archivio_f,((*num)+1)*sizeof(fattura))) == NULL)
      exit(1);
   if((p_temp = (int*)realloc(p_temp,((*num)+1)*sizeof(int))) == NULL)
      exit(1);
      
   printf("Fattura numero %d\n",(*num));
   (archivio_f+(*num))->num_f=(*num);
   printf("Inserisci giorno: ");
   scanf("%d",&(archivio_f+(*num))->data.giorno);
   printf("Inserisci mese: ");
   scanf("%d",&(archivio_f+(*num))->data.mese);
   printf("Inserisci anno: ");
   scanf("%d",&(archivio_f+(*num))->data.anno);
   *(p_temp+(*num))=0;
   
   do
   {
      if((archivio_temp=(int*)realloc(archivio_temp,(*(p_temp+(*num))+1)*sizeof(int))) == NULL)
          exit(1);                                         
      do
      {
         printf("Inserisci il codice del prodotto da inserire nella fattura: ");
         scanf("%d",&codice);
         if((posi = cerca(codice,archivio_p,num_p)) == -2)
            printf("Codice corrispondente a nessun prodotto.\n");
         else
            printf("Codice corrispondente a %s\n",(archivio_p+posi)->nome);
      }while(posi == -2);
      *(archivio_temp+(*(p_temp+(*num))))=codice;
      printf("Prodotto inserito!\nVuoi inserire altri prodotti all'interno della fattura ?\n1)Si\n2)No\nRisposta: ");
      scanf("%d",&again);
      getchar();
      if(again == 1)
               (*(p_temp+(*num)))++;
   }while(again != 2); 
   if((((archivio_f+(*num))->prodotti) = (int*)malloc((*(p_temp+(*num)))*sizeof(int))) == NULL)
         exit(1);
   ((archivio_f+(*num))->prodotti) = archivio_temp;
   printf("Fattura %d completata!\nHai inserito %d prodotti!\n",*num,*(p_temp+(*num)));
   n_p =(int*)malloc((*(p_temp+(*num)))*sizeof(int));
   n_p = p_temp;
   (*num)++;
   return archivio_f;
}

void stampa_prodotto(prodotto *archivio_p,int num)
{
   int codice,pos;

   printf("Inserisci il codice prodotto da cercare: ");
   scanf("%d",&codice);
   pos = cerca(codice,archivio_p,num);
   if(pos > -2)
      printf("Prodotto trovato!\n"
             "Nome: %s\n"
             "Codice: %d\n"
             "Prezzo: %f\n"
             ,(archivio_p+pos)->nome
             ,(archivio_p+pos)->codice_p
             ,(archivio_p+pos)->prezzo);
   else
      printf("Prodotto non trovato\n");
   return;     
}

int cerca(int codice,prodotto *archivio_p,int num)
{
   int i=0,trovato=-2;
   
  for(i; i < num; i++)
  {
      if(((archivio_p+i)->codice_p) == codice)
         trovato = i;
   }
  return trovato;
}
      
   
           
prodotto *carica_prodotto(prodotto *archivio_p,int *num)
{
   if((archivio_p = (prodotto*)realloc(archivio_p,((*num)+1)*sizeof(prodotto))) == NULL)
                exit(1);
                
    printf("Inserisci il nome del prodotto: ");
    scanf("%s",(archivio_p+(*num))->nome);
    printf("Inserisci il codice del prodotto: ");
    scanf("%d",&(archivio_p+(*num))->codice_p);
    printf("Inserisci il prezzo del prodotto: ");
    scanf("%3f",&(archivio_p+(*num))->prezzo);
    (*num)++;
    printf("Prodotto caricato con successo!\n");
    getchar();
    return archivio_p;
}



          
          
  
