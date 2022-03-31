
#include <aNDAr/multiDimensionalArray.hpp>
using namespace aNDAr;
void test_VA() {
    VA_pack<2,3>   va;
    VA_pack<1,1>   va_within;
    VA_pack<4,5>   va_higher;
    VA_pack<0,1,1> va_more;
    using vaType = VA_pack<2,3>;
    std::cout << "2×3 = 6 elements\n";
    std::cout << vaType::data::productOfElements << "\t productOfElements\n";
    std::cout << vaType::data::size << "\t size\n";
    std::cout << vaType::data::size << "\t size\n\n";

    std::cout << vaType::areAllIndicesSmallerThan(va_within) << "\t <2,3>::areAllIndicesSmallerThan <1,1>\n";
    std::cout << vaType::areAllIndicesSmallerThan(va_higher) << "\t <2,3>::areAllIndicesSmallerThan <4,5>\n";
    //std::cout << vaType::areAllIndicesSmallerThan(va_more) << "\t areAllIndicesSmallerThan <0,1,1>\n";

    std::cout << vaType::canHold(va_within) << "\t <2,3>::canHold <1,1>\n";
    std::cout << vaType::canHold(va_higher) << "\t <2,3>::canHold <4,5>\n";



        // Deemonstration, wie/dass VA_pack funktioniert:
        std::cout << "\n\n\n\n";
        VA_pack<4, 6,77,14,-15,73> vaTest;
        using testData = decltype(vaTest)::data;
        const int maxI{testData::size};
        std::cout << maxI << "\n";
        for(int i=0; i<maxI; ++i) std::cout <<  "[" << i << "] = " << testData::index[i] << '\n';
        std::cout << std::endl;
}
int main() {
    //test_VA();return 1;
    /*
    for(int i=0; i<55; ++i)
        if(i%10==0) std::cout << i << "\n";
    return
    0;0
    10
    20
    30
    40
    50 */


    multiDimensionalArray<int, 3,3,3> testArray(1);
    using ARTYPE =decltype(testArray);
    //testArray.debug->printDetailedInfo();
    //testArray.debug->printSummary();
    testArray.debug->printContent();
    #define TESTCASE_16 1,2,1 // 16
    #define TESTCASE_2 0,0,1 // 2
    #define STR_TESTCASE_16 "1,2,1 "// 16
    #define STR_TESTCASE_2 "0,0,1" // 2
    std::array<int,3> idx_16_stl{TESTCASE_16};
    std::array<int,3> idx_2_stl{TESTCASE_2};
    int idx_2_c[3]{TESTCASE_2};
    int idx_16_c[3]{TESTCASE_16};

    VA_pack<TESTCASE_2> idx_2_tpl;
    VA_pack<TESTCASE_16> idx_16_tpl;

    std::cout << "1D\n";
    testArray[5]=9; // access B; Zeile 20 in cpp läuft nicht.
    #define accessOutcome_0  {0,0,0}
    #define accessOutcome_2  {0,0,2}
    #define accessOutcome_4  {0,1,1}
    #define accessOutcome_12 {1,1,0}
    #define accessOutcome_25 {2,2,1}

    std::cout << "\n\n\n\n\n\n";

    std::cout << "Diverse\n";
    testArray[accessOutcome_2] += -10;
    testArray[accessOutcome_12] += 0;
    testArray[accessOutcome_25] += 0;
    testArray.debug->printDetailedInfo();

    std::cout << STR_TESTCASE_16 << "(16)\n";
    testArray[{TESTCASE_16}] = -10;
    testArray.debug->printContent();

    testArray[idx_16_tpl.getAsTuple()]=9;
    testArray.debug->printContent();

    testArray[idx_16_c]=77;
    testArray.debug->printContent();

    testArray[idx_16_stl]=3;
    testArray.debug->printContent();
    std::cout << "\n\nEND\n\n\n" << std::endl;
    //std::cout << "D" << std::endl;
    //testArray[*idx_c]=7; // access B

    testArray();
    testArray.operator()<1,1,1>();
    // std::cout << testArray<0,1,1>() << std::endl;

    return EXIT_SUCCESS;
}
// LANG=en g++ -Wfatal-errors -std=c++20 -O2 -I./src -I./include -D __DEBUG_ON tests/ndarray.cpp -o ./bin/Test_ndarray && ./bin/Test_ndarray
