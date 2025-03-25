#include "teste_domain.h"
#include "teste_list.h"
#include "teste_repo.h"
#include "teste_service.h"

// functie care ruleaza toate functiile de test (din domain, validator, repository, list, service)
void run_tests()
{
	test_medicament();
	test_validare();
	test_add();
	test_delete();
	test_store();
	test_update();
	test_find();
	test_erase();
	test_adauga_medicament();
	test_modifica_medicament();
    test_sterge_medicament();
	test_sorteaza_medicamente();
	test_filtreaza_dupa_cantitate();
	test_filtreaza_dupa_nume();
}