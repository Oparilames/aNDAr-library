
#include <aNDAr/multiDimensionalArray.hpp>
using namespace aNDAr;
int main(){
    using T = multiDimensionalArray<int,3,3,3>;
    using C = multiDimensionalArray<char,3,3,3>;
    {T ar{};}
    {T ar(5);}
    /// {T ar(initialisationMethod::incrementFrom,1);} // 2022
    {T ar{initialisationMethod::decrementFrom,1};}
    {T ar(initialisationMethod::incrementFrom,10,2);}
    {T ar(initialiseByIncrementFrom,10,2);}
    {T ar(aNDAr::incrementFrom,10,2);}
    {C ar("ThisIsATestThisIsATest!!!!!");}
    {C ar(aNDAr::incrementFrom,'a');}
    return EXIT_SUCCESS;
}
/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include tests/multiArray.cpp -o ./bin/Test_multiArray && ./bin/Test_multiArray
*/
