/*
 * Autore: Domenico Luciani
 * Classe: 4B
 * Descrizione: Gestione music store
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musica
{
  char nome[20], cognome[20], cod_f[20], email[20], genere[20];
  int anno;
  struct musica *succ;
};

typedef struct musica negozio;

negozio *
carica_cli (negozio * lista, int *n)
{
  int num, i;

  printf ("Inserisci numero di clienti da caricare: ");
  scanf ("%d", &num);

  for (i = 0; i < num; i++)
    {
      lista = (negozio *) realloc (lista, ((*n) + 1) * sizeof (negozio));
      if (lista == NULL)
	printf ("Impossibile allocare nella carica_cli!\n");
      printf ("Nome: ");
      scanf ("%s", (lista + (*n))->nome);
      printf ("Cognome: ");
      scanf ("%s", (lista + (*n))->cognome);
      printf ("Codice fiscale: ");
      scanf ("%s", (lista + (*n))->cod_f);
      printf ("Email: ");
      scanf ("%s", (lista + (*n))->email);
      printf ("Genere: ");
      scanf ("%s", (lista + (*n))->genere);
      printf ("Anno: ");
      scanf ("%d", &(lista + (*n))->anno);
      putchar ('\n');
      (*n)++;

    }
  printf ("Inserimento dati completata!\n");
  return lista;
}

void
stampa_cli (negozio * lista, int n)
{
  int i;
  printf ("Numero clienti: %d\n", n);
  for (i = n - 1; i >= 0; i--)
    printf ("- %d -\n%s\n%s\n%s\n%s\n%s\n%d\n\n", i + 1,
	    (lista + i)->nome, (lista + i)->cognome, (lista + i)->cod_f,
	    (lista + i)->email, (lista + i)->genere, (lista + i)->anno);
}

negozio *
carica_g (negozio * archivio, negozio * lista, int n)
{
  negozio *tmp = NULL;
  int i;
  char genere[20];

  printf ("Inserisci genere da cercare: ");
  scanf ("%s", genere);

  for (i = 0; i < n; i++)
    {
      printf ("Cliente: %d = ", i);
      if ((strcmp ((archivio + i)->genere, genere)) == 0)
	{
	  printf ("Genere trovato!\n");
	  tmp = (negozio *) malloc (sizeof (negozio));
	  *tmp = *(archivio + i);
	  tmp->succ = lista;
	  lista = tmp;
	}
      else
	printf ("Non trovato!\n");
    }
  return lista;
}

void
stampa_g (negozio * lista)
{
  while (lista != NULL)
    {
      printf ("\n%s\n%s\n%s\n%s\n%s\n%d\n\n", lista->nome, lista->cognome,
	      lista->cod_f, lista->email, lista->genere, lista->anno);
      lista = lista->succ;
    }
}

main ()
{
  int scelta, cli = 0;
  negozio *archivio = NULL, *lista = NULL;

  do
    {
      printf ("1)Inserisci clienti\n"
	      "2)Stampa clienti\n"
	      "3)Inserisci generi\n"
	      "4)Stampa generi\n" "5)Esci\n" "Scelta: ");
      scanf ("%d", &scelta);
      switch (scelta)
	{
	case 1:
	  archivio = carica_cli (archivio, &cli);
	  break;
	case 2:
	  stampa_cli (archivio, cli);
	  break;
	case 3:
	  lista = carica_g (archivio, lista, cli);
	  break;
	case 4:
	  stampa_g (lista);
	  break;
	case 5:
	  printf ("BYE!\n");
	  break;
	};
    }
  while (scelta != 5);
}
