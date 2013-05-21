/*
 * E' dato un array ordinato di caratteri. Scrivere una funzione che, presa in input una stringa, restituisce TRUE se tutti i 
 * caratteri della stringa sono contenuti nell'array.
 * Strutturare eventualmente il problema in sottoprocedure
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum RIS {FALSE,TRUE};

enum RIS binary_search(char carattere,char *vett)
{
    int dim = strlen(vett);
    int inizio=0,fine=dim-1,medio;

    while(inizio <= fine)
    {
        medio = (inizio+fine)/2;

        if(vett[medio] == carattere)
            return TRUE;

        if(vett[medio] < carattere)
            inizio = medio+1;
        else
            fine = medio-1;
    }

    return FALSE;
}


enum RIS cerca(char *str, char *vett)
{
    int i;

    for(i=0; i < strlen(str); i++)
        if(binary_search(str[i],vett) == FALSE)
            return FALSE;

    return TRUE;
}

int main()
{
    char stringa[30];
    char vettore[] = {'B','C','E','L','M','O','P','S','T','U','Z'};

    printf("\nInserisci la stringa: ");
    scanf("%s",stringa);

    if(cerca(stringa,vettore) == TRUE)
        puts("VERO");
    else
        puts("FALSO");

    return 0;
}
