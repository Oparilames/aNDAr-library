#define __DEBUG_ON
#include <aNDAr/array.inl>
using namespace aNDAr::detail;
int main()
{
array<int,4> array(3);
    auto printFunc=[&array]{
    std::cout << "Four elements in array: ";
    for(auto i=array.begin(), iMax=array.beforeEnd(1); i!=iMax; ++i) std::cout << *i << ' ';
    std::cout << "and " << *array.beforeEnd(1) << "\n";};

    printFunc();
    const int arAccess[4]={0,0,0,1};
    array[3]=0;
    printFunc();
    /// 2022 now for nDarrays, no longer 1D ones.
    /// array[arAccess]=1;
    /// printFunc();
    return EXIT_SUCCESS;
}

/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include tests/array.cpp -o ./bin/Test_array && ./bin/Test_array
*/
