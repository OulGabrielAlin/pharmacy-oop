#ifndef MYSORT_H
#define MYSORT_H
#include "../Utils/list.h"
#include "../Domain/medicament.h"


typedef int(*FunctieComparare)(Medicament* m1, Medicament* m2);
void sort(List* list, FunctieComparare func, int crescator);

#endif