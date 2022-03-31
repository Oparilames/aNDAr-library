// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

#include <iostream>
#include <array>
using namespace std;






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













int main() {
    // dimension's boundaries
    const int N1{2}, N2{4}, N3{3};

    // indices out of corresponding boundaries
    const int beyondN1{N1+10}, beyondN2{N2+10}, beyondN3{N3+10};

    // used datatype for this example
    using T = int;

    // Arrays instantiations and initialisations
    T array_inC[N1][N2][N3];
    array< array< array<T,N1>, N2>, N3> array_STL;


    std::cout << "Content array_inC:\n";
    printArrayContent<T, N1, N2, N3>(array_inC);

    std::cout << "Content array_STL:\n";
    printArrayContent<T, N1, N2, N3>(array_STL);

    // Writing values
    array_inC[beyondN1][beyondN2][beyondN3] = 99;
    array_STL[beyondN1][beyondN2][beyondN3] = 99;
    cout << "Value at "<< beyondN1 << ", " << beyondN2 << ", " << beyondN3 << " for array_inC: " << array_inC[beyondN1][beyondN2][beyondN3] << std::endl;
    cout << "Value at "<< beyondN1 << ", " << beyondN2 << ", " << beyondN3 << " for array_STL: " << array_STL[beyondN1][beyondN2][beyondN3] << std::endl;
}
/*
  To compile:
	LANG=en g++ -Wfatal-errors -std=c++20 -g -O2 -I./src -I./include tutorial/compareArraytypes.cpp -o tutorial/bin_exe/Test_compareArraytypes && tutorial/bin_exe/Test_compareArraytypes
  To print out with line numbers:
	awk '{printf("% 4d %s\n", NR, $0)}' tutorial/compareArraytypes.cpp
*/
