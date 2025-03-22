#ifndef LIST_H
#define LIST_H

#include "medicament.h"
typedef void* TElem;
typedef void (*Destructor)(TElem);

typedef struct {
	TElem* elems;
	int size;
	int cap;
} List;

List* creeaza_lista();
void add(List* list, TElem m);
void delete(List* list, int poz);
void destroy_list(List* list);


#endif