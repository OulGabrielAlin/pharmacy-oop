#include "teste_repo.h"
#include "../Repository/repository.h"
#include "../Domain/medicament.h"
#include "math.h"
#include <assert.h>
#include <string.h>

// functie de test pentru functia store (repo)
void test_store()
{
	Repo* repo = creeaza_repo();
	assert(repo->lista_med->size == 0);

	Medicament* m1 = creeaza_medicament(1, "Paracetamol", 12.10, 5);
	store(repo, m1);
	assert(((Medicament*)repo->lista_med->elems[0])->cod == 1);
	assert(strcmp(((Medicament*)repo->lista_med->elems[0])->nume, "Paracetamol") == 0);
	assert(fabs(((Medicament*)repo->lista_med->elems[0])->concentratie - 12.10) < 0.0001);
	assert(((Medicament*)repo->lista_med->elems[0])->cantitate == 5);
	assert(repo->lista_med->size == 1);

	Medicament* m2 = creeaza_medicament(1, "Paracetamol", 12.10, 10);
	store(repo, m2);
	assert(((Medicament*)repo->lista_med->elems[0])->cod == 1);
	assert(strcmp(((Medicament*)repo->lista_med->elems[0])->nume, "Paracetamol") == 0);
	assert(fabs(((Medicament*)repo->lista_med->elems[0])->concentratie - 12.10) < 0.0001);
	assert(((Medicament*)repo->lista_med->elems[0])->cantitate == 15);
	assert(repo->lista_med->size == 1);

	Medicament* m3 = creeaza_medicament(2, "Ibuprofen", 5.1, 2);
	store(repo, m3);
	assert(((Medicament*)repo->lista_med->elems[1])->cod == 2);
	assert(strcmp(((Medicament*)repo->lista_med->elems[1])->nume, "Ibuprofen") == 0);
	assert(fabs(((Medicament*)repo->lista_med->elems[1])->concentratie - 5.1) < 0.0001);
	assert(((Medicament*)repo->lista_med->elems[1])->cantitate == 2);
	assert(repo->lista_med->size == 2);

	distruge_repo(repo);
}

// functie de test pentru functia update (repo)
void test_update()
{
	Repo* repo = creeaza_repo();
	Medicament* m1 = creeaza_medicament(1, "Paracetamol", 12.1, 5);
	store(repo, m1);
	assert(repo->lista_med->size == 1);

	int status;
	status = update(repo, 2, "Ibuprofen", 10.9);
	assert(status == 0);

	status = update(repo, 1, "Ibuprofen", 11.2);
	assert(status == 1);
	assert(strcmp(((Medicament*)repo->lista_med->elems[0])->nume, "Ibuprofen") == 0);
	assert(fabs(((Medicament*)repo->lista_med->elems[0])->concentratie - 11.2) < 0.0001);

	distruge_repo(repo);
}

// functie de test pentru functia find (repo)
void test_find()
{
	Repo* repo = creeaza_repo();
	Medicament* m1 = creeaza_medicament(101, "Paduden", 21.1, 10);
	store(repo, m1);
	assert(repo->lista_med->size == 1);

	int poz;
	poz = find(repo, 200);
	assert(poz == -1);

	poz = find(repo, 101);
	assert(poz == 0);
	assert(((Medicament*)repo->lista_med->elems[poz])->cod == 101);
	assert(strcmp(((Medicament*)repo->lista_med->elems[poz])->nume, "Paduden") == 0);
	assert(fabs(((Medicament*)repo->lista_med->elems[poz])->concentratie - 21.1) < 0.0001);
	assert(((Medicament*)repo->lista_med->elems[poz])->cantitate == 10);

	distruge_repo(repo);
}

// functie de test pentru functia erase (repo)
void test_erase()
{
	Repo* repo = creeaza_repo();
	assert(repo->lista_med->size == 0);

	Medicament* m1 = creeaza_medicament(10, "Paracetamol", 10.15, 10);
	Medicament* m2 = creeaza_medicament(11, "Ibuprofen", 22.05, 15);
	store(repo, m1);
	store(repo, m2);
	assert(repo->lista_med->size == 2);

	int status;
	status = erase(repo, 10);
	assert(status == 1);
	assert(repo->lista_med->size == 1);
	assert(((Medicament*)repo->lista_med->elems[0])->cod == 11);

	status = erase(repo, 11);
	assert(status == 1);
	assert(repo->lista_med->size == 0);

	status = erase(repo, 10);
	assert(status == 0);
	assert(repo->lista_med->size == 0);

	distruge_repo(repo);
}