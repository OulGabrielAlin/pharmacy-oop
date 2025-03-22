#include "teste_list.h"
#include "list.h"
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

void test_add()
{
	List* list = creeaza_lista();
	assert(list->size == 0);
	Medicament* m1 = creeaza_medicament(10, "Paracetamol", 5.15, 20);
	Medicament* m2 = creeaza_medicament(11, "Ibuprofen", 17.2, 25);
	Medicament* m3 = creeaza_medicament(12, "Paduden", 19.2, 10);
	add(list, m1);
	add(list, m2);
	add(list, m3);

	assert(list->size == 3);
	assert(((Medicament*)list->elems[0])->cod == 10);
	assert(((Medicament*)list->elems[0])->cantitate == 20);
	assert(strcmp(((Medicament*)list->elems[0])->nume, "Paracetamol") == 0);
	assert(fabs(((Medicament*)list->elems[0])->concentratie - 5.15) < 0.0001);

	assert(list->cap == 4);

	destroy_list(list);
}

void test_delete()
{
	List* list = creeaza_lista();
	assert(list->size == 0);

	Medicament* m1 = creeaza_medicament(10, "Paracetamol", 5.15, 19);
	Medicament* m2 = creeaza_medicament(11, "Paduden", 6.15, 22);
	Medicament* m3 = creeaza_medicament(12, "Ibuprofen", 7.15, 2);
	Medicament* m4 = creeaza_medicament(13, "Vitamina C", 8.15, 15);
	Medicament* m5 = creeaza_medicament(14, "Sirop", 4.15, 10);
	add(list, m1);
	add(list, m2);
	add(list, m3);
	add(list, m4);
	add(list, m5);

	delete(list, 2);
	assert(list->size == 4);
	assert(((Medicament*)list->elems[2])->cod == 13);
	for (int i = 0; i < list->size; i++)
		if (((Medicament*)list->elems[i])->cod == 12)
			assert(!1);

	delete(list, 100);
	assert(list->size == 4);

	destroy_list(list);
}