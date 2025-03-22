#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "console.h"

int main()
{
	Consola* consola = creeaza_consola();
	run(consola);

	distruge_consola(consola);

	_CrtDumpMemoryLeaks();
	return 0;
}