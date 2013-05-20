/*
Scrivere un programma che, attraverso l'esclusivo uso di funzioni ricorsive, gestisca una lista concatenata in cui ogni elemento ha due campi informativi
uno di tipo int di nome num e uno di tipo char di nome lettera. il programma deve:
    1)Creare una lista L in cui il campo num di ogni elemento, immesso da tastiera, sia un intero positivo non nullo;
     il campo lettera deve essere automaticamente calcolato e deve contenere il carattere minuscono nel range 'a'-'z' corrispondente all'intero 
     contenuto nel campo num. 
      Nota che se per esempio il campo num è 30, il campo letterà sarà 'd'. 
    2) Calcolare la lunghezza della lista, ovvero il numero dei suoi elementi;
    3) Stampare i caratteri della lista L nell'ordine inverso;
    4) Restituire il massimo degli interi di L;
    5) 
    */
    

#include <stdio.h>
#include <stdlib.h>

struct lista
{
    int num;
    char lettera;
    struct lista *next;
};

struct lista* crea_lista(struct lista *p)
{
    int x;
    
    printf("Inserisci num, 0 per terminare: ");
    scanf("%d",&x);
    
    if(!x)
        p=NULL;
    else
    {
        p=malloc(sizeof(struct lista));
        p->num = x;
        p->lettera = (x % 26) + ('a' - 1);
        p->next = crea_lista(p->next);
    }
    return p;
}

int calcola_elementi(struct lista *p)
{
    if(p == NULL)
        return 0;
    else
        return 1 + calcola_elementi(p->next);
        
}

void stamp_inverso(struct lista *p)
{
    if(p==NULL)
        return;
    else
    {
        stamp_inverso(p->next);
        printf("%c\n",p->lettera);
    }
}

int rit_max(struct lista *p)
{
    if(p == NULL)
        return 0;
    else
    {
        if(p->num > rit_max(p->next))
            return p->num;
        else
            return rit_max(p->next);
    }
}

int parity_check(struct lista *p)
{
   if(p==NULL)
    return 1;
   else
        return (!(p->num % 2) && parity_check(p->next));
}

int main(void)
{
    struct lista *testa=NULL;
    int n,max;
    
    testa = crea_lista(testa);
    n = calcola_elementi(testa);
    printf("Numero elementi: %d\n",n);
    stamp_inverso(testa);
    printf("Max: %d\n",rit_max(testa));
    printf("Elementi pari: %d\n",parity_check(testa));
    system("pause");
}
