#ifndef SERVICE_H
#define SERVICE_H
#include "../Repository/repository.h"

typedef struct {
	Repo* repo;
	List* listaUndo;
} ServiceMed;

ServiceMed* creeaza_serviciu();
void distruge_serviciu(ServiceMed* service);
void adauga_medicament(ServiceMed* service, int cod, char nume[], float concentratie, int cantitate, char* errors);
void modifica_medicament(ServiceMed* service, int cod, char nume[], float concentratie, char* errors);
int sterge_medicament(ServiceMed* service, int cod);
void sorteaza_medicamente(ServiceMed* service, int crescator);
int cmpByType(Medicament* m1, Medicament* m2);
int cmp_cresc(Medicament* m1, Medicament* m2);
int cmp_desc(Medicament* m1, Medicament* m2);
void filtreaza_dupa_cantitate(ServiceMed* service, List* list, int cantitate);
void filtreaza_dupa_nume(ServiceMed* service, List* list, char c);
void filtreaza_dupa_concentratie(ServiceMed* service, List* list, double c1, double c2);
void adauga_default(ServiceMed* service);
void Undo(ServiceMed* service);

#endif