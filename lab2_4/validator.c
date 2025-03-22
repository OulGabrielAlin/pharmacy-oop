#include "validator.h"
#include <string.h>

/* Valideaza datele unui medicament
*  cod: codul medicamentului
*  nume: numele medicamentului
*  concentratie: concentratia medicamentului
*  cantitate: cantitatea medicamentului
*  post: in errors vor fi adaugat erorile care apar in urma datelor invalide
*/
void valideaza(int cod, char nume[], float concentratie, int cantitate, char* errors)
{
	if (cod < 1)
		strcat(errors, "Codul trebuie sa aiba o valoare mai mare ca 0\n");
	if (concentratie <= 0 || concentratie >= 100)
		strcat(errors, "Concentratia trebuie sa aiba o valoare in intervalul (0, 100)\n");
	if (cantitate < 0)
		strcat(errors, "Cantitatea trebuie sa fie un numar intreg pozitiv\n");
}