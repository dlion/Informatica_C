/*
 * Scrivere una procedura che inverta una lista concatenata data in input:
 * Esempio:
 * h->S->U->P->E->R->L->A->T->I->V->A->M->E->N->T->E->NULL
 * h->E->T->N->E->M->A->V->I->T->A->L->R->E->P->U->S->NULL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista
{
    char car;
    struct lista *next;
};

//Stampa ricorsiva di una lista
void stampa(struct lista *p)
{
    if(p != NULL)
    {
        printf("%c->",p->car);
        stampa(p->next);
    }
}

//Inserimento in coda
struct lista* ins_coda(struct lista *p,char ele)
{
    if(p == NULL)
    {
        p = (struct lista*)malloc(sizeof(struct lista));
        p->car = ele;
        p->next = NULL;
    }
    else
        p->next = ins_coda(p->next,ele);

    return p;
}

//Inserimento in testa
struct lista* ins_testa(struct lista *p,char ele)
{
    struct lista *primo = NULL;

    if(p == NULL)
    {
        p = (struct lista*)malloc(sizeof(struct lista));
        p->car = ele;
        p->next = NULL;
    }
    else
    {
        primo = (struct lista*)malloc(sizeof(struct lista));
        primo->car = ele;
        primo->next = p;
        p = primo;
    }

    return p;
}

struct lista* inverti(struct lista *p)
{
    struct lista *nuova=NULL;

    for(p; p != NULL; p = p->next)
        nuova = ins_testa(nuova,p->car);
    
    return nuova;
}
        
int main()
{
    char stringa[20];
    int i;
    struct lista *inizio=NULL;

    printf("Inserisci la stringa: ");
    scanf("%s",stringa);
    
    for(i=0; i < strlen(stringa); i++)
        inizio = ins_coda(inizio,stringa[i]);

    printf("h->");
    stampa(inizio);
    printf("NULL\n");

    inizio = inverti(inizio);
    
    printf("h->");
    stampa(inizio);
    puts("NULL");
    
    return 0;
}
