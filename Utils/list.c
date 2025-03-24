#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Domain/medicament.h"


/* Creaza un obiect de tip lista
*  return: o lista fara elemente
*/ 
List* creeaza_lista()
{
	List* list = malloc(sizeof(List));
	if (list == NULL)
	{
		perror("Couldn't find memory");
		return NULL;
	}

	list->size = 0;
	list->cap = 2;
	list->elems = malloc(sizeof(TElem) * list->cap);
	if (list->elems == NULL)
	{
		perror("Couldn't find memory");
		return NULL;
	}
	return list;
}

/* Adauga un medicament la lista
*  list: lista curenta
*  m: medicamentul adaugat
*/
void add(List* list, TElem m)
{
	if (list->size == list->cap)
	{
		list->cap *= 2;
		TElem* new_list = malloc(sizeof(TElem) * list->cap);
		if (new_list == NULL)
		{
			perror("Couldn't allocate more memory");
			return;
		}

		for (int i = 0; i < list->size; i++)
			new_list[i] = list->elems[i];

		free(list->elems);
		list->elems = new_list;
	}

	list->elems[list->size] = m;
	++(list->size);
}

/* Sterge un medicament din lista dupa pozitie
*  list: lista curenta
*  poz: pozitia data
*/
void delete(List* list, int poz)
{
	if (poz >= list->size)
		return;

	distruge_medicament(list->elems[poz]);

	for (int i = poz; i < list->size - 1; i++)
		list->elems[i] = list->elems[i + 1];
	

	--(list->size);
}

/* Elibereaza memoria ocupata de lista
*  post: lista este distrusa
*/
void destroy_list(List* list)
{
	for (int i = 0; i < list->size; i++)
		distruge_medicament(list->elems[i]);
	free(list->elems);
	free(list);
}
