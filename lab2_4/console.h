#ifndef CONSOLE_H
#define CONSOLE_H
#include "service.h"

typedef struct {
	ServiceMed* service;
} Consola;

Consola* creeaza_consola();
void afiseaza_meniu();
void run(Consola* consola);
void citeste_date(int* cod, char nume[], float* concentratie, int* cantitate);
void afiseaza_lista(Consola* consola);
void afiseaza_medicament(Medicament* m);
void adauga_medicament_ui(Consola* consola);
void modifica_medicament_ui(Consola* consola);
void sterge_medicament_ui(Consola* consola);
void sorteaza_lista_ui(Consola* consola);
void filtreaza_dupa_cantitate_ui(Consola* consola);
void filtreaza_dupa_nume_ui(Consola* consola);
void distruge_consola(Consola* consola);

#endif