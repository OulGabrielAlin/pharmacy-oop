#include "console.h"
#include "stdio.h"
#include "../Domain/medicament.h"
#include "string.h"
#include "../Tests/run_tests.h"
#include <stdlib.h>
#include <ctype.h>

/* Creeaza un obiect de tip consola
*  return: consola cu service de medicamente
*/
Consola* creeaza_consola()
{
	Consola* consola = malloc(sizeof(Consola));
	if (consola == NULL)
	{
		perror("Couldn't allocate memory");
		return NULL;
	}

	ServiceMed* service = creeaza_serviciu();
	if (service == NULL)
	{
		perror("Couldn't allocate memory");
		return NULL;
	}

	consola->service = service;
	return consola;
}

void distruge_consola(Consola* consola)
{
	distruge_serviciu(consola->service);
	free(consola);
}

/* Afiseaza meniul aplicatiei
*/
void afiseaza_meniu()
{
	printf("*********************************************\n");
	printf("1. Adauga medicament\n");
	printf("2. Modifica medicament\n");
	printf("3. Sterge medicament\n");
	printf("4. Filtreaza dupa cantitate\n");
	printf("5. Filtreaza dupa nume\n");
	printf("6. Filtreaza dupa concentratie\n");
	printf("P. Afiseaza lista de medicamente ordonate\n");
	printf("U. Undo\n");
	printf("X. Iesire aplicatie\n");
	printf("*********************************************\n");
	printf("Alegeti optiunea dorita:\n");
	
}

/* Afiseaza un medicament
*  m: medicament
*/
void afiseaza_medicament(Medicament* m)
{
	printf("Cod: %d\nNume: %s\nConcentratie: %.2lf\nCantitate: %d\n", m->cod, m->nume, m->concentratie, m->cantitate);
}

/* Sorteaza lista pe baza datelor citite
*  consola: consola curenta
*/
void sorteaza_lista_ui(Consola* consola)
{
	char input = 0;
	printf("crescator/descrescator (c/d):");
	int cnt = scanf("\n%c", &input);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	switch (input) {
	case 'c':
		sorteaza_medicamente(consola->service, 1);
		break;
	case 'd':
		sorteaza_medicamente(consola->service, 0);
		break;
	default:
		return;
	}
}

/* Afiseaza lista de medicamente
*  consola: consola curenta
*/
void afiseaza_lista(Consola* consola)
{	
	sorteaza_lista_ui(consola);

	printf("---------------------------\n");
	for (int i = 0; i < consola->service->repo->lista_med->size; i++)
	{
		afiseaza_medicament(consola->service->repo->lista_med->elems[i]);
		printf("---------------------------\n");
	}
}

/* Citeste datele unui medicament
*  cod: codul citit
*  nume: numele citit
*  concentratie: concentratia citita
*  cantitate: cantitatea citita
*/
void citeste_date(int* cod, char nume[], float* concentratie, int* cantitate)
{
	int cnt;
	printf("Cod: ");
	cnt =  scanf("%d", cod);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	printf("Nume: ");
	cnt = scanf("%s", nume);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	printf("Concentratie: ");
	cnt = scanf("%f", concentratie);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	printf("Cantitate: ");
	cnt = scanf("%d", cantitate);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}
}

/* Adauga un medicament la lista pe baza datelor citite
*  consola: consola curenta
*  post: afiseaza erori daca apar
*/ 
void adauga_medicament_ui(Consola* consola)
{
	int cod, cantitate;
	float concentratie;
	char nume[20];

	citeste_date(&cod, nume, &concentratie, &cantitate);
	char errors[200] = "";
	adauga_medicament(consola->service, cod, nume, concentratie, cantitate, errors);

	if (strlen(errors) > 0)
	{
		printf("\n---------------------------\n");
		printf("%s", errors);
		printf("---------------------------\n");
	}
}

/* Modifica un medicament pe baza datelor citite
*  consola: consola curenta
*  post: afiseaza erori daca apar
*/

void modifica_medicament_ui(Consola* consola)
{
	int cod, cnt;
	char nume[20];
	float concentratie;

	printf("Cod: ");
	cnt = scanf("%d",&cod);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	printf("Nume: ");
	cnt = scanf("%s", nume);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	printf("Concentratie: ");
	cnt = scanf("%f", &concentratie);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	char errors[200] = "";
	modifica_medicament(consola->service, cod, nume, concentratie, errors);

	if (strlen(errors) > 0)
	{
		printf("\n---------------------------\n");
		printf("%s", errors);
		printf("---------------------------\n");
	}
}

/* Sterge un medicament din lista pe baza datelor citite
*  consola: consola curenta
*  post: afiseaza erori daca apar
*/
void sterge_medicament_ui(Consola* consola)
{
	int cod = -1, cnt;
	printf("Cod: ");
	cnt = scanf("%d", &cod);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	int status = sterge_medicament(consola->service, cod);
	if (status == 0)
	{
		printf("\n---------------------------\n");
		printf("Medicamentul cu codul dat nu exista\n");
		printf("---------------------------\n");
	}
}

/* Afiseaza medicamentele care au cantitatea mai mica decat o valoare citita
*  consola: consola curenta
*/
void filtreaza_dupa_cantitate_ui(Consola* consola)
{
	int cantitate;
	int cnt;

	printf("Cantitate: ");
	cnt = scanf("%d", &cantitate);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	List* list = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	filtreaza_dupa_cantitate(consola->service, list, cantitate);

	printf("---------------------------\n");
	for (int i = 0; i < list->size; i++)
	{
		afiseaza_medicament(list->elems[i]);
		printf("---------------------------\n");
	}
	destroy_list(list);
}

/* Afiseaza medicamentele a caror prima litera din nume este aceeasi cu o litera citita
*  consola: consola curenta
*/
void filtreaza_dupa_nume_ui(Consola* consola)
{
	char c[5];
	int cnt;

	printf("Litera: ");
	cnt = scanf("%s", c);
	if (cnt != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	List* list = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	filtreaza_dupa_nume(consola->service, list, c[0]);

	printf("---------------------------\n");
	for (int i = 0; i < list->size; i++)
	{
		afiseaza_medicament(list->elems[i]);
		printf("---------------------------\n");
	}

	destroy_list(list);
}

/* Afiseaza medicamentele a caror concentratie se afla intre doua valori date
*  consola: consola curenta
*/
void filtreaza_dupa_concentratie_ui(Consola* consola)
{
	double c1, c2;
	int cnt1, cnt2;

	printf("Limita inferioara de concentratie: ");
	cnt1 = scanf("%lf", &c1);

	printf("Limita superioara de concentratie: ");
	cnt2 = scanf("%lf", &c2);


	if (cnt1 != 1 || cnt2 != 1)
	{
		printf("Nu s-au putut citi datele!");
		return;
	}

	List* list = creeaza_lista((void*)distruge_medicament, (void*)copiaza_medicament);
	filtreaza_dupa_concentratie(consola->service, list, c1, c2);

	printf("---------------------------\n");
	for (int i = 0; i < list->size; i++)
	{
		afiseaza_medicament(list->elems[i]);
		printf("---------------------------\n");
	}

	destroy_list(list);
}

void run(Consola* consola)
{
	int is_running = 1;
	run_tests();
	printf("Testele au trecut cu succes!\n\n");
	adauga_default(consola->service);

	while (is_running)
	{
		afiseaza_meniu();
		char optiune[2];
		int cnt;
		cnt = scanf("%s", optiune);
		if (cnt != 1)
		{
			printf("Nu s-au putut citi datele!");
			return;
		}
		printf("\n");
		
		optiune[0] = toupper(optiune[0]);
		switch (optiune[0]) {
			case '1':
				adauga_medicament_ui(consola);
				break;

			case '2':
				modifica_medicament_ui(consola);
				break;

			case '3':
				sterge_medicament_ui(consola);
				break;

			case '4':
				filtreaza_dupa_cantitate_ui(consola);
				break;

			case '5':
				filtreaza_dupa_nume_ui(consola);
				break;

			case '6':
				filtreaza_dupa_concentratie_ui(consola);
				break;

			case 'P':
				afiseaza_lista(consola);
				break;

			case 'U':
				Undo(consola->service);
				break;

			case 'X':
				is_running = 0;
				break;

		}
	}
}