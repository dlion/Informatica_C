/*
 * Autore: Domenico Luciani
 * Classe: 4B Informatica
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5

int controllo(int, int*, int);

int main()
{
   int V[MAX],n,i,j=0,k=0;
   printf("Attenzione il programma potrebbe essere molto lento\n");
   printf("Numero: ");
   scanf("%d",&n);

   for(k;k<MAX;k++)
   {
      do
      {
        srand(time(NULL));
        V[k]=(rand()%90)+1;
        
        if(k != 0)
           j=controllo(V[k],V,k);
        
      }while(j != 0);
   }
   for(i=0;i<MAX;i++)
   {
      printf("%d ",V[i]);
     j = (V[i] == n) ? 1 : 0;
   }
   putchar('\n');
   (j==1) ? printf("Complimenti il numero da te scelto e' uscito\n") : printf("Mi dispiace il tuo numero non e' uscito\n") ;
   
   return 0;
}

int controllo(int j, int V[],int k)
{
   int i;
   for(i=0;i<k;i++)
      if(V[i]==j)
         return 1;
   
   return 0;
}

