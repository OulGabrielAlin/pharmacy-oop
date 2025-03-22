#include "medicament.h"
#include "mysort.h"

/* Sorteaza o lista data crescator sau descrescator dupa un criteriu dat
*/
void sort(List* list, FunctieComparare func, int crescator)
{
	for (int i = 0; i < list->size - 1; i++)
		for (int j = i + 1; j < list->size; j++)
			if (crescator)
			{
				if (func(list->elems[j], list->elems[i]) != 0)
				{
					Medicament* aux = list->elems[j];
					list->elems[j] = list->elems[i];
					list->elems[i] = aux;
				}
			}
			else
			{
				if (func(list->elems[i], list->elems[j]) != 0)
				{
					Medicament* aux = list->elems[j];
					list->elems[j] = list->elems[i];
					list->elems[i] = aux;
				}
			}
				
}