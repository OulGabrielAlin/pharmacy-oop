#include "service.h"
#include "../Validator/validator.h"
#include "../Repository/repository.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include "mysort.h"

/* Creeaza un obiect de tip serviciu pentru medicamente
*  return: un serviciu pentru medicamente
*/ 
ServiceMed* creeaza_serviciu()
{
	ServiceMed* service = malloc(sizeof(ServiceMed));
	if (service == NULL)
	{
		perror("Couldn't allocate memory");
		return NULL;
	}

	Repo* repo = creeaza_repo();
	if (repo == NULL)
	{
		perror("Couldn't allocate memory");
		return NULL;
	}

	service->repo = repo;
	return service;
}

/* Elibereaza memoria ocupata de serviciu
*  post: serviciul este distrus
*/
void distruge_serviciu(ServiceMed* service)
{
	distruge_repo(service->repo);
	free(service);
}

/* Adauga un medicament la lista de medicamente pe baza datelor citite
*  service: serviciul de medicamente curent
*  cod: codul medicamentului
*  nume: numele medicamentului
*  concentratie: concentratia medicamentului
*  cantitate: cantitatea medicamentului
*  errors: va contine la iesirea din functie lista de erori cauzate de date invalide
*/
void adauga_medicament(ServiceMed* service, int cod, char nume[], float concentratie, int cantitate, char* errors)
{
	valideaza(cod, nume, concentratie, cantitate, errors);

	Medicament* m = creeaza_medicament(cod, nume, concentratie, cantitate);

	if (strlen(errors) == 0)
	{
		store(service->repo, m);
		return;
	}

	if (m != NULL)
		distruge_medicament(m);
}

/* Modifica numele si concentratia unui medicament care are un cod dat
*  service: serviciul de medicamente curent
*  cod: codul medicamentului
*  nume: noul nume
*  concentratie: noua concentratie
*  errors: va contine la iesirea din functie lista de erori cauzate de date invalide
*/
void modifica_medicament(ServiceMed* service, int cod, char nume[], float concentratie, char* errors)
{
	int cantitate = 10;
	valideaza(cod, nume, concentratie, cantitate, errors);

	int status = 1;
	if (strlen(errors) != 0)
		return;
		
	status = update(service->repo, cod, nume, concentratie);

	if (!status)
		strcat(errors, "Medicamentul cu codul dat nu exista\n");
}

/* Sterge un medicament care are un cod dat
*  service: serviciul de medicamente curent
*  cod: codul medicamentului
*  return: 1 daca stergerea a avut loc, 0 in caz contrar
*/
int sterge_medicament(ServiceMed* service, int cod)
{
	return erase(service->repo, cod);
}

int cmpByType(Medicament* m1, Medicament* m2)
{
	if (strcmp(m1->nume, m2->nume) < 0 || (strcmp(m1->nume, m2->nume) == 0 && m1->cantitate < m2->cantitate))
		return 1;
	return 0;
}
/* Sorteaza crescator sau descrescator lista de medicamente din serviciu
*  service: serviciul curent de medicamente
*  crescator: daca este 0 indica sortare descrescatoare, altfel crescatoare
*/
void sorteaza_medicamente(ServiceMed* service, int crescator)
{
	sort(service->repo->lista_med, cmpByType, crescator);
}

/* Selecteaza din lista de medicamente acelea care au cantitatea mai mica ca o valoare data
*  service: serviciul de medicamente curent
*  list: lista in care vor fi adaugate medicamentele filtrate
*  cantitate: valoarea data
*/
void filtreaza_dupa_cantitate(ServiceMed* service, List* list, int cantitate)
{
	for (int i = 0; i < service->repo->lista_med->size; i++)
		if (((Medicament*)service->repo->lista_med->elems[i])->cantitate < cantitate)
		{
			Medicament* copy = copiaza_medicament(service->repo->lista_med->elems[i]);
			add(list, copy);
		}
}

/* Selecteaza din lista de medicamente acelea care au prima litera din nume aceeasi cu o litera data
*  service: serviciul de medicamente curent
*  list: lista in care vor fi adaugate medicamentele filtrate
*  c: litera data
*/
void filtreaza_dupa_nume(ServiceMed* service, List* list, char c)
{
	for (int i = 0; i < service->repo->lista_med->size; i++)
		if (((Medicament*)service->repo->lista_med->elems[i])->nume[0] == c)
		{
			Medicament* copy = copiaza_medicament(service->repo->lista_med->elems[i]);
			add(list, copy);
		}
}

/* Adauga medicamente default la lista de medicamente
*  service: serviciul de medicamente dat
*/
void adauga_default(ServiceMed* service)
{
	char errors[] = "";
	adauga_medicament(service, 10, "Paracetamol", 12.11, 6, errors);
	adauga_medicament(service, 11, "Ibuprofen", 19.1, 9, errors);
	adauga_medicament(service, 12, "Aspirina", 20.2, 4, errors);
	adauga_medicament(service, 13, "Omeprazol", 30.5, 10, errors);
	adauga_medicament(service, 14, "Amoxicilina", 9.51, 20, errors);
	adauga_medicament(service, 15, "Metformin", 20.2, 19, errors);
	adauga_medicament(service, 16, "Diazepam", 15.1, 7, errors);
	adauga_medicament(service, 17, "Atorvastatina", 10.78, 2, errors);
	adauga_medicament(service, 18, "Furosemid", 23.11, 5, errors);
	adauga_medicament(service, 19, "Cetirizina", 29.2, 21, errors);
	adauga_medicament(service, 20, "Levotiroxina", 4.2, 16, errors);
}