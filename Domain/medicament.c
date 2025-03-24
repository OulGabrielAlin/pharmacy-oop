#include "medicament.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Creeaza un obiect de tip medicament
*  cod: codul medicamentului (numar intreg)
*  nume: numele medicamentului
*  concentratie: concentratia medicamentului (numar rational)
*  cantitate: cantitatea medicamentului (numar intreg)
*/
Medicament* creeaza_medicament(int cod, char nume[], float concentratie, int cantitate)
{
	Medicament* m = malloc(sizeof(Medicament));
	if (m == NULL)
	{
		perror("Couldn't find memory");
		return NULL;
	}

	m->nume = malloc(sizeof(char) * (strlen(nume) + 1));

	if (m->nume == NULL)
	{
		perror("Couldn't find memory");
		return NULL;
	}

	m->cod = cod;
	strcpy(m->nume, nume);
	m->concentratie = concentratie;
	m->cantitate = cantitate;

	return m;
}

/* Returneaza o copie independenta a medicamentului dat
*  m: medicamentul dat
*  return: o copie
*/
Medicament* copiaza_medicament(Medicament* m)
{
	Medicament* med = malloc(sizeof(Medicament));
	if (med == NULL)
	{
		perror("Couldn't allocate memory");
		return NULL;
	}
	
	med->cod = m->cod;
	med->concentratie = m->concentratie;
	med->cantitate = m->cantitate;

	med->nume = malloc(sizeof(char) * (strlen(m->nume) + 1));
	if (med->nume == NULL)
	{
		perror("Couldn't allocate memory");
		return NULL;
	}

	strcpy(med->nume, m->nume);

	return med;
}

/* Elibereaza memoria ocupata de un medicament
*  post: medicamentul este distrus
*/
void distruge_medicament(Medicament* m)
{
	free(m->nume);
	free(m);
}