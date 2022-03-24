// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

#include <iostream>
#include <array>
using std::array;

#define __SHORTNAMES_ON
#include <aNDAr/multiDimensionalArray.hpp>
using aNDAr::multiDimensionalArray;

template <typename UNDERLYINGTYPE, int N1, int N2, int N3, typename CONTAINER>
void printArrayContent(CONTAINER& array) {
    std::cout << "      ";
    int counter{0};
    const int amountElements{sizeof(array)/sizeof(UNDERLYINGTYPE)};
    auto* current{&array[0][0][0]};--current;
        for(; counter < amountElements-2; ++counter)
            std::cout << *++current << ' ';
        counter+=2;
        std::cout << *++current << " and " << *++current << "\n      Counter: " << counter << "\n" << std::endl;
}

template <typename UNDERLYINGTYPE, int N1, int N2, int N3,typename T>
void printArrayContent(T& array) requires(std::is_same_v<T, aNDAr::multiDimensionalArray<UNDERLYINGTYPE, N1,N2,N3>>) {
    std::cout << "      ";
    int counter{0};
    auto current = array.begin();
    for(auto current = array.begin(),last=array.beforeEnd(2); current!=last; ++current,++counter)
    //for(; current < array.beforeEnd(2); ++counter)
        std::cout << *current++ << ' ';
    counter+=2;
    std::cout << *current++ << " and " << *current++ << "\n      Counter: " << counter << "\n" << std::endl;
}


int main() {
	using namespace aNDAr::shortName;
	
    // dimension's boundaries
    const int N1{2}, N2{4}, N3{3};

    // indices out of corresponding boundaries
    const int beyondN1{N1+10}, beyondN2{N2+10}, beyondN3{N3+10};

    // used datatype for this example
    using T = int;

    // Array's instantiations
    multiDimensionalArray<int,N1,N2,N3> lengthyND;
    arrayND<int,N1,N2,N3>               shorterND;
    arND<int,N1,N2,N3>                  abbrev_ND;
    array3D<int,N1,N2,N3>               shorter3D;
    ar3D<int,N1,N2,N3>                  abbrev_3D;
    int array_inC[N1][N2][N3]={0};
    array<array<array<int,N3>,N2>,N1>   array_STL{0};

    std::cout << "   Content C array after initialisation: \n";
    printArrayContent<T, N1, N2, N3>(array_inC);

    std::cout << "  Content STL array after initialisation: \n";
    printArrayContent<T, N1, N2, N3>(array_inC);

    std::cout << "Content aNDAr array after initialisation: \n";
    printArrayContent<T, N1, N2, N3>(lengthyND);

    // Writing values
    array_inC[0][0][0] = 1;
    array_inC[N1-1][N2-1][N3-1] = N1*N2*N3;
    array_inC[beyondN1][beyondN2][beyondN3] = 99;

    array_STL[0][0][0] = 1;
    array_STL[N1-1][N2-1][N3-1] = N1*N2*N3;
    array_STL[beyondN1][beyondN2][beyondN3] = 99;

    lengthyND.set<0,0,0>(1);
    lengthyND.set<N1-1,N2-1,N3-1>(N1*N2*N3);
    //lengthyND.set<beyondN1,beyondN2,beyondN3>(99);
{
    aNDAr::multiDimensionalArray<int,N1,N2,N3> lengthyND; // variable name: 9, dimensions:  9, type name:  4, class name: 21, semicolon and spaces: 1, until here: 44,  default initialisation: 0, total: 44 + 7 without `using namespace aNDAr`, real total = 50
    arrayND<int,N1,N2,N3>               shorterND; // variable name: 9, dimensions:  9, type name:  4, class name:  7, semicolon and spaces: 1, until here: 30, default initialisation: 0, total: 30 + 7 without `using namespace aNDAr`, real total = 37
    arND<int,N1,N2,N3>                  abbrev_ND; // variable name: 9, dimensions:  9, type name:  4, class name:  4, semicolon and spaces: 1, until here: 27, default initialisation: 0, total: 27 + 7 without `using namespace aNDAr`, real total = 27
    array3D<int,N1,N2,N3>               shorter3D; // variable name: 9, dimensions:  9, type name:  4, class name:  7, semicolon and spaces: 1, until here: 30, default initialisation: 0, total: 30 + 7 without `using namespace aNDAr`, real total = 37
    ar3D<int,N1,N2,N3>                  abbrev_3D; // variable name: 9, dimensions:  9, type name:  4, class name:  4, semicolon and spaces: 1, until here: 27, default initialisation: 0, total: 27 + 7 without `using namespace aNDAr`, real total = 28
    int array_inC[N1][N2][N3]={0};   // array_inC  // variable name: 9, dimensions: 12, type name:  3, class name:  0, semicolon and spaces: 2, until here: 26, default initialisation: 4, total:     // if each value has to be initialised on its own: 125 instead 4
    array<array<array<int,N3>,N2>,N1>     array_STL{0}; // variable name: 9, dimensions:  12, type name:  3, class name: 18, semicolon and spaces: 1, default initialisation: x, total: 40 + 5 without using namespace, real total = 45
}
    std::cout << "   Content after writing to C array: \n";
    printArrayContent<T, N1, N2, N3>(array_inC);

    std::cout << "  Content after writing toSTL array: \n";
    printArrayContent<T, N1, N2, N3>(array_inC);

    std::cout << "Content after writing to aNDAr array: \n";
    printArrayContent<T, N1, N2, N3>(lengthyND);

}

// LANG=en g++ -Wfatal-errors -std=c++20 -g -O2 -I./src -I./include tutorial/compareArraytypesNewShort.cpp -o tutorial/bin_exe/Test_compareArraytypesNewShort && tutorial/bin_exe/Test_compareArraytypesNewShort
// awk '{printf("% 4d %s\n", NR, $0)}' tutorial/compareArraytypesNewShort.cpp
