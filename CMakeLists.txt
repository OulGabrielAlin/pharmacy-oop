cmake_minimum_required(VERSION 3.28.3)
project(Lab5 C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS "--coverage -g ${CMAKE_CXX_FLAGS}")

add_executable(Lab5 main.c
                Controller/mysort.c
                Controller/mysort.h
                Controller/service.c
                Controller/service.h
                Domain/medicament.c
                Domain/medicament.h
                Repository/repository.c
                Repository/repository.h
                Tests/run_tests.c
                Tests/run_tests.h
                Tests/teste_domain.c
                Tests/teste_domain.h
                Tests/teste_list.c
                Tests/teste_list.h
                Tests/teste_repo.c
                Tests/teste_repo.h
                Tests/teste_service.c
                Tests/teste_service.h
                UI/console.c
                UI/console.h
                Utils/list.c
                Utils/list.h
                Validator/validator.c
                Validator/validator.h
                )
