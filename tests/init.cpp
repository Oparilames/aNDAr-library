#include <aNDAr/initialisation.hpp>
#include <iostream>
using namespace aNDAr;

int main()
{
    //iM_constant<initialisationMethod::typeDefaultTo> shouldFail;
    std::cout << detail::initMethodTitle(initialiseByIncrementFrom) << std::endl;
    std::cout << detail::initMethodTitle(multiplyFromBy) << std::endl;
    std::cout << detail::initMethodTitle(multiplyFromBy,true) << std::endl;

    return EXIT_SUCCESS;
}
/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include tests/init.cpp -o ./bin/Test_init && ./bin/Test_init
*/
