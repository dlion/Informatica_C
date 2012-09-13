/*
 * Nome: Domenico Luciani
 * Classe: 3B
 * Data: 21-04-10
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

void sort(int,float*,int*);

int main()
{
    int concorrenti=0,i,ritirati=0;
    float somma=0;
    printf("Quanti sono i concorrenti ?\nRisp: ");
    scanf("%d",&concorrenti);
    float classifica[concorrenti];
    for(i=0;i<concorrenti;i++) classifica[i]=0;
    int partecipante[concorrenti];
    
    for(i=0;i<concorrenti;i++)
    {
       printf("Tempo di arrivo del numero %d (metti 0 per dire che non e' arrivato): ",i+1);
       scanf("%f",&classifica[i]);
       fflush(stdin);
       somma+=classifica[i];
       partecipante[i]=i;
       if(classifica[i]==0)ritirati++;
           
    }
    sort(concorrenti,classifica,partecipante);
    for(i=0;i<concorrenti;i++)
    {
       if(classifica[i]==0)printf("Numero %d ritirato\n",partecipante[i]+1);
       else
       {
               printf("Tempo %f il numero %d\n",classifica[i],partecipante[i]+1);
       }
    }
    printf("Si sono ritirati %d ciclisti\n",ritirati);
    printf("Il tempo medio e': %f\n",somma/(concorrenti-ritirati));
    system("pause");
    return 0;
}

void sort(int concorrenti,float *classifica,int *partecipante)
{
     int i,j,temp1;
     float temp2;
     
     for(i=0;i<concorrenti-1;i++)
     {
        for(j=i+1;j<concorrenti;j++)
        {
           if(classifica[i]>classifica[j])
           {
              temp2=classifica[j];
              classifica[j]=classifica[i];
              classifica[i]=temp2;
              
              temp1=partecipante[j];
              partecipante[j]=partecipante[i];
              partecipante[i]=temp1;
           }
        }
     }
}
              
              
