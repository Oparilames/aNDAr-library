#define __DEBUG_ON
#include <aNDAr/counter.inl>
#include <iostream>
using namespace aNDAr::detail;
int main()
{
    counter<int> cntr1, cntr2;
    std::cout << cntr1 << ", " << cntr2 << " / " << cntr1.getMax() << std::endl;
    return EXIT_SUCCESS;
}

/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include tests/counter.cpp -o ./bin/Test_counter && ./bin/Test_counter
*/
