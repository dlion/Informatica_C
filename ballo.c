/*
 * Autore: Domenico Luciani
 * Classe: 4B Informatica
 * Descrizione: Si vuole gestire una scuola di ballo in coppia.
 * 1. inserire gli allievi e le allieve in attesa della lezione.
 * 2. formare la coppia da avviare alla lezione.
 * 3. visualizzare gli allievi e le allieve in attesa della lezione.
 */

#include <stdio.h>
#include <stdlib.h>

struct alunno {
	char nome[20], cognome[20];
	int eta, cod_t;
};

struct lista {
	struct alunno a;
	struct lista *succ;
};

typedef struct lista elenco;

elenco *carica(elenco*);
elenco *estrai(elenco*);
void visualizza(elenco*,elenco*);

main()
{
	int scelta,sesso;
	elenco *allievi=NULL,*allieve=NULL;

	do {
		printf("1)Inserimento allievo/allieve\n"
		       "2)Formazione coppie\n"
		       "3)Visualizza allievi in attesa\n"
               "4)Esci\n" 
               "Scelta: ");
		scanf("%d", &scelta);
		switch (scelta) 
        {
		    case 1:
                printf("Inserisci sesso dell'alunno\n"
                       "1. Maschio\n"
                       "2. Femmina\n"
                       "Scelta: ");
                scanf("%d",&sesso);
                if(sesso == 1)
                    allievi = carica(allievi);
                else
                    allieve = carica(allieve);
                break;
            case 2:
                allievi = estrai(allievi);
                allieve = estrai(allieve);
                break;
            case 3:
                visualizza(allievi,allieve);
                break;
		    case 5:
			    printf("BYE!\n");
			    break;
		};
	}while (scelta != 4);
}

elenco *carica(elenco *f)
{
    elenco *tmp;

    tmp = (elenco*)malloc(sizeof(elenco));
    
    printf("Nome: ");
    scanf("%s",(tmp->a).nome);
    printf("Cognome: ");
    scanf("%s",(tmp->a).cognome);
    printf("Eta': ");
    scanf("%d",&(tmp->a).eta);
    printf("Codice tessera: ");
    scanf("%d",&(tmp->a).cod_t);
    if(f == NULL)
    {
        tmp->succ = NULL;
        f = tmp;
    }
    else
    {
        f->succ = tmp;
        tmp->succ = NULL;
    }
    return f;
}

elenco *estrai(elenco *alunno)
{
    if(alunno == NULL)
    {
        printf("Lista vuota!\n");
        return;
    }
    else
    {
        printf("%s ",(alunno->a).nome);
        alunno = alunno->succ;
    }
    putchar('\n');
    return alunno;
}

void visualizza(elenco *alunno, elenco *alunna)
{
    printf("Maschio  Femmina\n");
    while(alunno || alunna)
    {
        printf("%s  %s\n",(alunno->a).nome,(alunna->a).nome);
        alunno=alunno->succ;
        alunna=alunna->succ;
    };
}


            
    


