#include "teste_domain.h"
#include <assert.h>
#include "../Domain/medicament.h"
#include "../Validator/validator.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

void test_medicament()
{
	Medicament* m = creeaza_medicament(1, "Paracetamol", 11.10, 10);
	
	if (m == NULL)
		return;
	assert(m->cod == 1);
	assert(strcmp(m->nume, "Paracetamol")  == 0);
	assert(fabs(m->concentratie - 11.10) < 0.0001);
	assert(m->cantitate == 10);

	distruge_medicament(m);
}

void test_validare()
{
	char errors[200] = "";
	valideaza(1, "Ibuprofen", 12.3, 5, errors);
	assert(strlen(errors) == 0);

	strcpy(errors, "");
	valideaza(-1, "Ibuprofen", 12.3, 5, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\n") == 0);

	strcpy(errors, "");
	valideaza(1, "Ibuprofen", 0, 5, errors);
	assert(strcmp(errors, "Concentratia trebuie sa aiba o valoare in intervalul (0, 100)\n") == 0);

	strcpy(errors, "");
	valideaza(1, "Ibuprofen", 12.3, -1, errors);
	assert(strcmp(errors, "Cantitatea trebuie sa fie un numar intreg pozitiv\n") == 0);

	strcpy(errors, "");
	valideaza(-1, "Ibuprofen", 100, -1, errors);
	assert(strcmp(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\nConcentratia trebuie sa aiba o valoare in intervalul (0, 100)\nCantitatea trebuie sa fie un numar intreg pozitiv\n") == 0);
}