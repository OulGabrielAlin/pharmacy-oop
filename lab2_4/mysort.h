#ifndef MYSORT_H
#define MYSORT_H
#include "list.h"


typedef int(*FunctieComparare)(Medicament* m1, Medicament* m2);
void sort(List* list, FunctieComparare func, int crescator);

#endif