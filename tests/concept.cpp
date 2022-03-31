#define __DEBUG_ON
#include <aNDAr/concepts.hpp>
#include <vector>
struct x{};
struct y{
	x operator++(){
		return x{};
	};
}; 
// if you swap x for y in line 33 the code won't compile. Return type doesn't matter.

void test(anyOfType<float, x, int> auto a) {}

int main()
{
    int varI;
    x varX;
    y varY;
    test(varI);
    test(varX);
    // Won't compile because y is not listed in the template parameter-list of anyOfType inside the function parameter type list.
    // test(varY);
    
    // Won't compile if 1!=1 || 2!=2.
	static_assert(allTruthIn<1==1, 2==2>(), "Not all template parameter-list parameters are equal.");
	
	// Won't compile if all bool expressions insine <> are false
	static_assert(anyTruthIn<1==0, 2==3, 1==0, 7==7>(), "No template parameter-list parameter is equal.");
	
	// Won't compile if int had no -- operator
	static_assert(hasDecrementOperator_v<int>, "int has no -- operator.");
	
	// Won't compile if x had ++ operator
	static_assert(!hasIncrementOperator_v<x>, "x has ++ operator.");
	
	// Won't compile if datatype couldn't be multiplied with itself
	static_assert(hasMultiplyOperator_self_v<int>, "type can't be *= ed with itself.");
	
	// Won't compile if one datatype couldn't be multiplied with the other
	static_assert(isMultiplyAssignableTo<int,float>::value, "This two types can't be *= ed.");
	
	// Won't compile if datatype couldn't be muiltiplied with standard C++ integral datatypes
	static_assert(hasMultiplyOperator_basicIntegral_v<int>, "The chosen data type can't be *= with any standard integral datatype.");
	
	// Won't compile if datatype couldn't be muiltiplied with standard C++ integral datatypes nor with wchar_t, char8_t and other special compiler dependet types.
	static_assert(hasMultiplyOperator_integral_v<int>, "The chosen data type can't be *= with any standard integral datatype nor with special cases.");
	
	// Won't compile if datatype hadn't a multiply assign operator
	static_assert(hasMultiplyOperator_v<int>, "Datatype simple can't be multiplied.");
	
	// Won't compile if datatype had no << operator with std::ostream
	static_assert(canPrintedByConsole_v<int>, "Datatype can't be printed out to std::cout.");
	
	// Won't compile if datatype had no [] operator
 	static_assert(hasRandoomAccessIterator_v<std::vector<int>>, "Datatype has not [] operator.");
	
    return EXIT_SUCCESS;
}

/*
LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include tests/concept.cpp -o ./bin/Test_concept && ./bin/Test_concept
*/
