#ifndef LIST_H
#define LIST_H

typedef void* TElem;
typedef void (*Destructor)(TElem);
typedef TElem (*Copiator)(TElem);

typedef struct {
	TElem* elems;
	int size;
	int cap;
	Destructor destructor;
	Copiator copiator;
} List;

List* creeaza_lista(Destructor destructor, Copiator copiator);
void add(List* list, TElem m);
void delete(List* list, int poz);
void destroy_list(List* list);
List* copy_list(List* list);


#endif