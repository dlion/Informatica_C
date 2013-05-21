/*
 * Dato un vettore A, modificarlo senza usare un vettore ausiliario e spostare gli 0 alla fine lasciando inalterati tutti gli altri
 */
#include <stdio.h>
#include <stdlib.h>

#define DIM 20

void stampa(int *A)
{
    int i=0;

    for(i; i < DIM; i++)
        printf("%d ",A[i]);
    putchar('\n');
}

int main()
{
    int A[] = {5,3,0,5,4,0,6,8,0,2,6,0,1,4,0,1,9,0,2,5};
    int i,j,temp=0;

    for(i=0; i < DIM; i++)
    {
        if(A[i] == 0)
        {
            for(j=i; j< DIM-1; j++)
                A[j] = A[j+1];
            
            A[j] = 0;
        }

    }

    stampa(A);

    return 0;
}
