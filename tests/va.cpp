// #include "variadicParameterPacks.cpp"
#include <aNDAr/variadicParameterPacks.cpp>
using namespace aNDAr;
int main()
{
    VA_pack<3,3,3> DreiDreiDrei;
    VA_pack<1,1,1> EinsEinsEins;
    std::cout << std::boolalpha << "<1,1,1> can hold <3,3,3>: " << EinsEinsEins.canHold(DreiDreiDrei) << "\n" ;
    std::cout << std::boolalpha << "<1,1,1> out of boundary for <3,3,3>: " << EinsEinsEins.indexOutOfBoundariesOf<3,3,3>() << "\n" ;
    std::cout << std::boolalpha << "<1,1,1> indices smaller than <3,3,3>: " << EinsEinsEins.areAllIndicesSmallerThan<3,3,3>() << "\n\n";

    std::cout << std::boolalpha << "<3,3,3> can hold <1,1,1>: " << DreiDreiDrei.canHold(EinsEinsEins) << "\n" ;
    std::cout << std::boolalpha << "<3,3,3> out of boundary for <1,1,1>: " << DreiDreiDrei.indexOutOfBoundariesOf<1,1,1>() << "\n" ;
    std::cout << std::boolalpha << "<3,3,3> indices smaller than <1,1,1>: " << DreiDreiDrei.areAllIndicesSmallerThan<1,1,1>() << "\n\n";

    return EXIT_SUCCESS;
}
/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include test/va.cpp -o ./bin/Test_va && ./bin/Test_va
*/
