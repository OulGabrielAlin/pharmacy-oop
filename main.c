#include <stdlib.h>
#include "UI/console.h"

int main()
{
    Consola* consola = creeaza_consola();
    run(consola);

    distruge_consola(consola);

    return 0;
}