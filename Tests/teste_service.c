#include "teste_service.h"
#include "../Repository/repository.h"
#include "../Controller/service.h"
#include "string.h"
#include "assert.h"
#include "math.h"
#include <stdio.h>
#include "../Controller/mysort.h"

// functie de test pentru adauga_medicament (service)
void test_adauga_medicament()
{
	ServiceMed* service = creeaza_serviciu();
	assert(service->repo->lista_med->size== 0);

	char errors[250] = "";
	adauga_medicament(service, 101, "Paracetamol", 12.3, 10, errors);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cod == 101);
	assert(strcmp(((Medicament*)service->repo->lista_med->elems[0])->nume, "Paracetamol") == 0);
	assert(fabs(((Medicament*)service->repo->lista_med->elems[0])->concentratie - 12.3) < 0.0001);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cantitate == 10);
	assert(strcmp(errors, "") == 0);

	strcpy(errors, "");
	adauga_medicament(service, 101, "Paracetamol", 12.3, 12, errors);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cod == 101);
	assert(strcmp(((Medicament*)service->repo->lista_med->elems[0])->nume, "Paracetamol") == 0);
	assert(fabs(((Medicament*)service->repo->lista_med->elems[0])->concentratie - 12.3) < 0.0001);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cantitate == 22);
	assert(strcmp(errors, "") == 0);

	strcpy(errors, "");
	adauga_medicament(service, -1, "Paracetamol", 12.3, 12, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\n") == 0);

	strcpy(errors, "");
	adauga_medicament(service, 101, "Paracetamol", 100, 12, errors);
	assert(strcmp(errors, "Concentratia trebuie sa aiba o valoare in intervalul (0, 100)\n") == 0);

	strcpy(errors, "");
	adauga_medicament(service, 101, "Paracetamol", 12.3, -1, errors);
	assert(strcmp(errors, "Cantitatea trebuie sa fie un numar intreg pozitiv\n") == 0);

	strcpy(errors, "");
	adauga_medicament(service, -1, "Paracetamol", 100, -1, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\nConcentratia trebuie sa aiba o valoare in intervalul (0, 100)\nCantitatea trebuie sa fie un numar intreg pozitiv\n") == 0);

	strcpy(errors, "");
	adauga_medicament(service, -2, "", 100, -1, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\nConcentratia trebuie sa aiba o valoare in intervalul (0, 100)\nCantitatea trebuie sa fie un numar intreg pozitiv\nTrebuie sa introduceti un nume pentru medicament\n") == 0);

	distruge_serviciu(service);
}

// functie de test pentru modifica_medicament (service)
void test_modifica_medicament()
{
	ServiceMed* service = creeaza_serviciu();
	assert(service->repo->lista_med->size == 0);

	char errors[200] = "";
	adauga_medicament(service, 101, "Paracetamol", 12.2, 10, errors);
	assert(service->repo->lista_med->size == 1);
	assert(strcmp(errors, "") == 0);

	strcpy(errors, "");
	modifica_medicament(service, 101, "Paduden", 10.99, errors);
	assert(strcmp(((Medicament*)service->repo->lista_med->elems[0])->nume, "Paduden") == 0);
	assert(fabs(((Medicament*)service->repo->lista_med->elems[0])->concentratie - 10.99) < 0.0001);

	strcpy(errors, "");
	modifica_medicament(service, -1, "Ibuprofen", 15.1, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\n") == 0);

	strcpy(errors, "");
	modifica_medicament(service, 102, "Ibuprofen", 15.1, errors);
	assert(strcmp(errors, "Medicamentul cu codul dat nu exista\n") == 0);

	strcpy(errors, "");
	modifica_medicament(service, 101, "Ibuprofen", -1, errors);
	assert(strcmp(errors, "Concentratia trebuie sa aiba o valoare in intervalul (0, 100)\n") == 0);

	strcpy(errors, "");
	modifica_medicament(service, -1, "Ibuprofen", -1, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\nConcentratia trebuie sa aiba o valoare in intervalul (0, 100)\n") == 0);

	distruge_serviciu(service);
}

// functie de test pentru sterge_medicament (service)
void test_sterge_medicament()
{
	ServiceMed* service = creeaza_serviciu();
	assert(service->repo->lista_med->size == 0);

	char errors[200] = "";
	adauga_medicament(service, 10, "Paracetamol", 12.1, 10, errors);
	adauga_medicament(service, 11, "Ibuprofen", 10.1, 12, errors);
	assert(strlen(errors) == 0);
	assert(service->repo->lista_med->size == 2);

	int status;
	status = sterge_medicament(service, 10);
	assert(status == 1);
	assert(service->repo->lista_med->size == 1);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cod == 11);

	status = sterge_medicament(service, 11);
	assert(status == 1);
	assert(service->repo->lista_med->size == 0);

	status = sterge_medicament(service, 10);
	assert(status == 0);
	assert(service->repo->lista_med->size == 0);

	distruge_serviciu(service);
}

// functie de test pentru sorteaza_medicamente (service)
void test_sorteaza_medicamente()
{
	ServiceMed* service = creeaza_serviciu();

	char errors[] = "";
	adauga_medicament(service, 11, "b", 12.1, 5, errors);
	adauga_medicament(service, 12, "c", 12.1, 2, errors);
	adauga_medicament(service, 13, "a", 12.1, 6, errors);
	adauga_medicament(service, 14, "e", 12.1, 1, errors);
	adauga_medicament(service, 15, "b", 12.1, 9, errors);
	adauga_medicament(service, 16, "c", 12.1, 10, errors);
	adauga_medicament(service, 17, "a", 12.1, 2, errors);
	assert(strlen(errors) == 0);

	sorteaza_medicamente(service, 1);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cod == 17);
	assert(((Medicament*)service->repo->lista_med->elems[1])->cod == 13);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cod == 11);
	assert(((Medicament*)service->repo->lista_med->elems[3])->cod == 15);
	assert(((Medicament*)service->repo->lista_med->elems[4])->cod == 12);
	assert(((Medicament*)service->repo->lista_med->elems[5])->cod == 16);
	assert(((Medicament*)service->repo->lista_med->elems[6])->cod == 14);

	sterge_medicament(service, 11);
	sterge_medicament(service, 12);
	sterge_medicament(service, 13);
	sterge_medicament(service, 14);
	sterge_medicament(service, 15);
	sterge_medicament(service, 16);
	sterge_medicament(service, 17);
	assert(service->repo->lista_med->size == 0);

	adauga_medicament(service, 11, "b", 12.1, 5, errors);
	adauga_medicament(service, 12, "c", 12.1, 2, errors);
	adauga_medicament(service, 13, "a", 12.1, 6, errors);
	adauga_medicament(service, 14, "e", 12.1, 1, errors);
	adauga_medicament(service, 15, "b", 12.1, 9, errors);
	adauga_medicament(service, 16, "c", 12.1, 10, errors);
	adauga_medicament(service, 17, "a", 12.1, 2, errors);
	assert(strlen(errors) == 0);

	sorteaza_medicamente(service, 0);
	assert(((Medicament*)service->repo->lista_med->elems[0])->cod == 14);
	assert(((Medicament*)service->repo->lista_med->elems[1])->cod == 16);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cod == 12);
	assert(((Medicament*)service->repo->lista_med->elems[3])->cod == 15);
	assert(((Medicament*)service->repo->lista_med->elems[4])->cod == 11);
	assert(((Medicament*)service->repo->lista_med->elems[5])->cod == 13);
	assert(((Medicament*)service->repo->lista_med->elems[6])->cod == 17);

	distruge_serviciu(service);
}

// functie de test pentru filtreaza_dupa_cantitate (service)
void test_filtreaza_dupa_cantitate()
{
	ServiceMed* service = creeaza_serviciu();

	List* list = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	char errors[] = "";
	adauga_medicament(service, 11, "Algocalmin", 12.1, 10, errors);
	adauga_medicament(service, 12, "Paracetamol", 15.2, 4, errors);
	adauga_medicament(service, 13, "Omeprazol", 19.2, 20, errors);
	adauga_medicament(service, 14, "Amoxicilina", 20.1, 12, errors);
	adauga_medicament(service, 15, "Diazepam", 13.2, 5, errors);
	assert(strlen(errors) == 0);

	filtreaza_dupa_cantitate(service, list, 10);
	assert(list->size == 2);
	assert(((Medicament*)list->elems[0])->cod == 12);
	assert(((Medicament*)list->elems[1])->cod == 15);

	destroy_list(list);
	distruge_serviciu(service);
}

// functie de test pentru filtreaza_dupa_nume (service)
void test_filtreaza_dupa_nume()
{
	ServiceMed* service = creeaza_serviciu();

	List* list = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	char errors[] = "";
	adauga_medicament(service, 11, "Algocalmin", 12.1, 10, errors);
	adauga_medicament(service, 12, "Paracetamol", 15.2, 4, errors);
	adauga_medicament(service, 13, "Omeprazol", 19.2, 20, errors);
	adauga_medicament(service, 14, "Amoxicilina", 20.1, 12, errors);
	adauga_medicament(service, 15, "Prednison", 13.2, 5, errors);
	assert(strlen(errors) == 0);

	filtreaza_dupa_nume(service, list, 'P');
	assert(list->size == 2);
	assert(((Medicament*)list->elems[0])->cod == 12);
	assert(((Medicament*)list->elems[1])->cod == 15);

	destroy_list(list);
	distruge_serviciu(service);
}

// functie de test pentru filtreaza_dupa_concentratie (service)
void test_filtreaza_dupa_concentratie()
{
	ServiceMed* service = creeaza_serviciu();

	List* list = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	char errors[] = "";
	adauga_medicament(service, 11, "Algocalmin", 12.1, 10, errors);
	adauga_medicament(service, 12, "Paracetamol", 15.2, 4, errors);
	adauga_medicament(service, 13, "Omeprazol", 19.2, 20, errors);
	adauga_medicament(service, 14, "Amoxicilina", 20.1, 12, errors);
	adauga_medicament(service, 15, "Prednison", 13.2, 5, errors);
	assert(strlen(errors) == 0);

	filtreaza_dupa_concentratie(service, list, 10, 15);
	assert(list->size == 2);
	assert(((Medicament*)list->elems[0])->cod == 11);
	assert(((Medicament*)list->elems[1])->cod == 15);
	destroy_list(list);

	List* list1 = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	filtreaza_dupa_concentratie(service, list1, 19, 20);
	assert(list1->size == 1);
	assert(((Medicament*)list1->elems[0])->cod == 13);

	destroy_list(list1);
	distruge_serviciu(service);
}

// functie de test pentru functia (Service) Undo
void test_undo() {
	ServiceMed* service = creeaza_serviciu();

	char errors[] = "";
	adauga_medicament(service, 11, "Algocalmin", 12.1, 10, errors);
	adauga_medicament(service, 12, "Paracetamol", 15.2, 4, errors);
	adauga_medicament(service, 13, "Omeprazol", 19.2, 20, errors);
	adauga_medicament(service, 14, "Amoxicilina", 20.1, 12, errors);
	adauga_medicament(service, 15, "Prednison", 13.2, 5, errors);
	assert(strlen(errors) == 0);
	assert(service->repo->lista_med->size == 5);

	Undo(service);
	assert(service->repo->lista_med->size == 4);
	assert(find(service->repo, 15) == -1);

	Undo(service);
	assert(service->repo->lista_med->size == 3);
	assert(find(service->repo, 14) == -1);

	modifica_medicament(service, 13, "Nospa", 14.3, errors);
	modifica_medicament(service, 13, "Aspacardin", 15.2, errors);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cod == 13);
	assert(strcmp(((Medicament*)service->repo->lista_med->elems[2])->nume, "Aspacardin") == 0);
	assert(fabs(((Medicament*)service->repo->lista_med->elems[2])->concentratie - 15.2) < 0.0001);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cantitate == 20);

	Undo(service);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cod == 13);
	assert(strcmp(((Medicament*)service->repo->lista_med->elems[2])->nume, "Nospa") == 0);
	assert(fabs(((Medicament*)service->repo->lista_med->elems[2])->concentratie - 14.3) < 0.0001);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cantitate == 20);

	Undo(service);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cod == 13);
	assert(strcmp(((Medicament*)service->repo->lista_med->elems[2])->nume, "Omeprazol") == 0);
	assert(fabs(((Medicament*)service->repo->lista_med->elems[2])->concentratie - 19.2) < 0.0001);
	assert(((Medicament*)service->repo->lista_med->elems[2])->cantitate == 20);

	Undo(service);
	assert(find(service->repo, 13) == -1);
	assert(service->repo->lista_med->size == 2);

	adauga_medicament(service, 13, "Omeprazol", 19.2, 20, errors);
	adauga_medicament(service, 14, "Amoxicilina", 20.1, 12, errors);

	assert(service->repo->lista_med->size == 4);
	sterge_medicament(service, 11);
	sterge_medicament(service, 13);

	assert(service->repo->lista_med->size == 2);
	assert(find(service->repo, 13) == -1);
	assert(find(service->repo, 11) == -1);

	Undo(service);
	assert(service->repo->lista_med->size == 3);
	assert(find(service->repo, 13) == 1);

	Undo(service);
	assert(service->repo->lista_med->size == 4);
	assert(find(service->repo, 13) == 2);
	assert(find(service->repo, 11) == 0);

	Undo(service);
	assert(service->repo->lista_med->size == 3);
	assert(find(service->repo, 14) == -1);

	Undo(service);
	assert(service->repo->lista_med->size == 2);
	assert(find(service->repo, 13) == -1);

	Undo(service);
	assert(service->repo->lista_med->size == 1);
	assert(find(service->repo, 12) == -1);

	Undo(service);
	assert(service->repo->lista_med->size == 0);
	assert(find(service->repo, 11) == -1);

	Undo(service);
	assert(service->repo->lista_med->size == 0);

	distruge_serviciu(service);
}