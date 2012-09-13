/*
 * ALbero binario
 */

#include <stdio.h>
#include <stdlib.h>

struct dati
{
    int num;
};

struct nodo
{
    struct dati d;
    struct nodo *l,*r;
};

struct nodo* aggiungi_nodo(struct nodo *p, struct dati a)
{
    if(p == NULL)
    {
        p = (struct nodo*)malloc(sizeof(struct nodo));
        p->d = a;
        p->l = p->r = NULL;
    }
    else
    {
        if(a.num > (p->d).num)
            p->r = aggiungi_nodo(p->r,a);
        else
            p->l = aggiungi_nodo(p->l,a);
    }
    return p;
}

void stampa(struct nodo *p)
{
    if(p == NULL)
        return;
    else
    {
        stampa(p->l);
        printf("%d\n",(p->d).num);
        stampa(p->r);
    }
}

main()
{
    struct dati info;
    struct nodo *radice=NULL;
    int array[8]={8,27,5,14,9,10,18,1},i;
    
    for(i=0; i < 8; i++)
    {
        info.num=array[i];
        radice = aggiungi_nodo(radice,info);
    }

    stampa(radice);

}
