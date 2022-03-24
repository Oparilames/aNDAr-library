// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

#include <iostream>
#include <array>
using std::array;

#define __SHORTNAMES_ON
#include <aNDAr/multiDimensionalArray.hpp>
using namespace aNDAr::shortName;


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
     auto current = array.begin(); auto lastElem = array.beforeEnd(2);
    for(; current != lastElem; ++counter)
        std::cout << *current++ << ' ';
    counter+=2;
    std::cout << *current++ << " and " << *current++ << "\n      Counter: " << counter << "\n" << std::endl;
}


int main() {
    // dimension's boundaries
    const int N1{2}, N2{4}, N3{3};

    // indices out of corresponding boundaries
    const int beyondN1{N1+10}, beyondN2{N2+10}, beyondN3{N3+10};
    const int errorCode_valueNotSet{54};

    // used datatype for this example
    using T = int;

    // Arrays instantiations
    T array_C[N1][N2][N3]{0};           array_C;
    array< array< array<T,N1>, N2>, N3> array_STL{0};
    arrayND<int,N1,N2,N3>               array_aNDAr;

    // Checking default initialisations
    std::cout << "Content     array_C:\n";
    printArrayContent<T, N1, N2, N3>(array_C);

    std::cout << "Content   array_STL:\n";
    printArrayContent<T, N1, N2, N3>(array_STL);

    std::cout << "Content array_aNDAr:\n";
    printArrayContent<T, N1, N2, N3>(array_aNDAr);

    std::cout << "\n-----------------------------------------------------------------\n\n";

    // Writing values
    array_C[beyondN1][beyondN2][beyondN3] = 99;
    array_STL[beyondN1][beyondN2][beyondN3] = 99;
 // array_aNDAr.set<beyondN1,beyondN2,beyondN3>(99); // won't compile
    /// auto aNDAr_writeResult=array_aNDAr.writeDataAtIndex(99,beyondN1,beyondN2,beyondN3); /// Auskommentierung aufheben sobald code von alter Version übernommen wurde
    //array_aNDAr.set<beyondN1,beyondN2,beyondN3>(99); // won't compile

    // Printing individual values:
    std::cout << "written value,     array_C: " << array_C[beyondN1][beyondN2][beyondN3] << std::endl;
    std::cout << "written value,   array_STL: " << array_STL[beyondN1][beyondN2][beyondN3] << std::endl;
    // std::cout << array_aNDAr.get<beyondN1,beyondN2,beyondN3>() << std::endl; // won't compile because not within array boundaries.
    /// std::cout << "written value, array_aNDAr: ";
    
    /// 2022: was commented out. Is it still needed?
    /// if(aNDAr_writeResult.value_or(errorCode_valueNotSet)==errorCode_valueNotSet) /// Auskommentierung aufheben sobald code von alter Version übernommen wurde
    ///     std::cout << "unknown (error)" << std::endl;
    /// else std::cout << aNDAr_writeResult.value() << std::endl;
    std::cout << "\n-----------------------------------------------------------------\n\n";

    // Checking values
    std::cout << "Content     array_C:\n";
    printArrayContent<T, N1, N2, N3>(array_C);

    std::cout << "Content   array_STL:\n";
    printArrayContent<T, N1, N2, N3>(array_STL);

    //std::cout << "Content array_aNDAr:\n";
    //printArrayContent<T, N1, N2, N3>(array_aNDAr);
}
/*
  To compile:
	LANG=en g++ -Wfatal-errors -std=c++20 -g -O2 -I./src -I./include tutorial/compareArraytypesNew.cpp -o tutorial/bin_exe/Test_compareArraytypesNew && tutorial/bin_exe/Test_compareArraytypesNew
  To print out with line numbers:
	awk '{printf("% 4d %s\n", NR, $0)}' tutorial/compareArraytypesNew.cpp
*/
