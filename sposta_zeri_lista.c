/*
 * 3. Si realizzi l’obiettivo dell’esercizio precedente, supponendo che questa volta i dati siano organizzati in una
 * lista concatenata. Ossia scrivere una procedura in cui, data in input una lista concatenata, la modifichi in modo tale
 * che tutte le celle che contengono uno 0  vengano spostate alla fine della lista, e che gli altri elementi restino nello
 * stesso ordine.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct lista 
{
    int num;
    struct lista *next;
}lista;

void stampa(lista *p)
{
    if(p != NULL)
    {
        printf("%d-> ",p->num);
        stampa(p->next);
    }
}

lista* ins_coda(lista *p,int ele)
{
    if(p == NULL)
    {
        p = (lista*)malloc(sizeof(lista));
        p->num = ele;
        p->next = NULL;
    }
    else
        p->next = ins_coda(p->next,ele);

    return p;
}

lista* sposta(lista *p)
{
    lista *temp=NULL;
    int conto = 0;
    
    while(p != NULL)
    {
        if(p->num != 0)
            temp = ins_coda(temp,p->num);
        else
            conto++;

        p = p->next;
    }

    for(conto; conto > 0; conto--)
        temp = ins_coda(temp,0);

    return temp;           
}
        

int main()
{
    lista *primo = NULL;
    int A[] = {2,7,0,3,0,5,0,0,3,4,0,1,3,6,7,0,0,2,0,0};
    int i;

    for(i=0; i < 20; i++)
        primo = ins_coda(primo,A[i]);

    stampa(primo);
    puts("NULL\n");

    primo = sposta(primo);

    stampa(primo);
    puts("NULL");

    return 0;
}
