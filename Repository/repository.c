#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Creeaza un obiect de tip repository pentru medicamente
  return: un repository care nu contine elemente
*/
Repo* creeaza_repo()
{
	Repo* repo = malloc(sizeof(Repo));
	if (repo == NULL)
	{
		perror("Couldn't find memory");
		return NULL;
	}

	repo->lista_med = creeaza_lista();
	if (repo->lista_med == NULL)
		return NULL;

	return repo;
}

/*Adauga un medicament la lista de medicamente
* repo: repository-ul curent
* m: medicamentul adaugat
*/
void store(Repo* repo, Medicament* m)
{
	int poz = find(repo, m->cod);
	if (poz != -1)
	{
		if (strcmp(m->nume, ((Medicament*)(repo->lista_med->elems[poz]))->nume) == 0 &&
			((Medicament*)(repo->lista_med->elems[poz]))->concentratie == m->concentratie) {
			((Medicament*)(repo->lista_med->elems[poz]))->cantitate += m->cantitate;
		}
		distruge_medicament(m);
		return;
	}

	add(repo->lista_med, m);
}

/*Returneaza pozitia in lista a medicamentului care are un cod dat sau -1 daca el nu se afla in lista
  repo: repository-ul curent
  cod: codul medicamentului cautat
  return: pozitia medicamentului sau -1
*/
int find(Repo* repo, int cod)
{
	for (int i = 0; i < repo->lista_med->size; i++)
		if (((Medicament*)repo->lista_med->elems[i])->cod == cod)
			return i;

	return -1;
}

/* Modifica numele si concentratie medicamentului care are un cod dat
*  repo: repository-ul curent
*  cod: codul medicamentului
*  nume: noul nume
*  concentratie: noua concentratie
*  return: 1 daca modificarea a avut loc, 0 in caz contrar
*/ 
int update(Repo* repo, int cod, char nume[], float concentratie)
{
	int poz = find(repo, cod);

	if (poz == -1)
		return 0;

	free(((Medicament*)repo->lista_med->elems[poz])->nume);
	((Medicament*)repo->lista_med->elems[poz])->nume = malloc(sizeof(char) * (strlen(nume) + 1));

	if (((Medicament*)repo->lista_med->elems[poz])->nume == NULL)
		return 1;

	strcpy(((Medicament*)repo->lista_med->elems[poz])->nume, nume);
	((Medicament*)repo->lista_med->elems[poz])->concentratie = concentratie;
	
	return 1;
}

/* Sterge un medicament din lista dupa un cod dat
*  repo: repository-ul curent
*  cod: codul medicamentului
*  return: 1 daca stergerea a avut loc, 0 in caz contrar
*/
int erase(Repo* repo, int cod)
{
	int poz = find(repo, cod);
	if (poz == -1)
		return 0;
	
	delete(repo->lista_med, poz);
	return 1;
}

/* Elibereaza memoria ocupata de repository
*  post: repository-ul este distrus
*/
void distruge_repo(Repo* repo)
{
	destroy_list(repo->lista_med);
	free(repo);
}