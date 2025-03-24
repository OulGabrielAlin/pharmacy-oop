#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "../Domain/medicament.h"
#include "../Utils/list.h"

typedef struct {
	List* lista_med;
} Repo;

Repo* creeaza_repo();
void store(Repo* repo, Medicament* m);
int find(Repo* repo, int cod);
int update(Repo* repo, int cod, char nume[], float concentratie);
int erase(Repo* repo, int cod);
void distruge_repo(Repo* repo);

#endif
