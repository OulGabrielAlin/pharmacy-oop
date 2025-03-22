#ifndef MEDICAMENT_H
#define MEDICAMENT_H

typedef struct {
	int cod;
	char* nume;
	float concentratie;
	int cantitate;
} Medicament;

Medicament* creeaza_medicament(int cod, char nume[], float concentratie, int cantitate);
Medicament* copiaza_medicament(Medicament* m);
void distruge_medicament(Medicament* m);


#endif

