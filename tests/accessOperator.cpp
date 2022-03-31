
#include <aNDAr/multiDimensionalArray.hpp>
#include <iostream>
#include <vector>
#include <array>
using namespace aNDAr;
int main(){
    using T = multiDimensionalArray<int,3,3,3>;
    {
		const int amountDimensions = 3;
		{T ar(initialisationMethod::incrementFrom,10,3);}
		T ar(initialisationMethod::incrementFrom,10,3);
		std::cout << 3*3*3 << " elements\n\n";
		std::cout << "   Array.totalSize = " << ar.totalSize << "\n";
		
		VA_pack<2,2,2> accesVA_222;
		VA_pack<0,0,1> accesVA_001;
		
		const std::initializer_list<const int> accesIL_222({2,2,2});
		const std::initializer_list<const int> accesIL_001({0,0,1});
		
		int accessCAr_222[3]={2,2,2};
		int accessCAr_001[3]={0,0,1};
		
		const int (&accessConstCAr_001)[3]={0,0,1};
		const int (&accessConstCAr_222)[3]={2,2,2};
		
		int accessBy1DIndex{27}; // B
		const int (&accessByCIntArray)[amountDimensions]{0,0,2}; // C
		std::initializer_list<const int>&& accessByIList{0,0,2}; // D
		std::tuple<int,int,int> accessByTuple{0,0,2}; // E // müsste amountDimensions lang sein?
		std::array<int,amountDimensions> accessBySTLArray{0,0,2}; // F
		std::vector<int> accessBySTLVector{0,0,2}; // F
		// G int[amountDimensions] direkt im body
		const int (&accessByCIntArrayReference)[amountDimensions]{0,0,2}; // H


		// B
		ar[accessBy1DIndex];
		// C
		ar[accessByCIntArray];
		// D
		ar[accessByIList];
		// E
		ar[accesVA_222.getAsTuple()];//ar[accessByTuple];
		// F
		ar[accessBySTLArray];
		ar[accessBySTLVector];
		// G
		/// ar[int[amountDimensions]{0,0,2}];
		// H
		ar[accessByCIntArrayReference];
		
		return 0;
		std::cout << "   Array[26] = "; ar[26];
		std::cout << "   Array[{2, 2, 2}] = "; ar[{2,2,2}];
		std::cout << "   Array[accesIL_222] = "; ar[accesIL_222];
		std::cout << "   Array[accesCAr_222] = "; ar[accessCAr_222];
		std::cout << "   Array[accessConstCAr_222] = "; ar[accessConstCAr_222];
		
		//int y[ar.totalSize]=
		/*
		std::cout << ar[x] << "\n";
		std::cout << ar[y] << "\n";
		std::cout << ar.getMappedIndex2022(*y) << "\n";
		*/
	}
    
    return EXIT_SUCCESS;
}
/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include tests/accessOperator2022.cpp -o ./bin/Test_accessOperator2022 && ./bin/Test_accessOperator2022
*/
