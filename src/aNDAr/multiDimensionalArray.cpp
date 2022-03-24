#include <aNDAr/multiDimensionalArray.hpp>
#include <aNDAr/antimagicnumbers.inl>
#define initTheBughunt(x) initBughunt(__LINE__,x)


namespace aNDAr{
using namespace aNDAr::str;
using namespace aNDAr::detail;
#define PREFIX template<typename T, int... DIM>
#define MULTIDIMENSIONALARRAY multiDimensionalArray<T,DIM...>

PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray()
{
    initBughunt(__LINE__,"default initialisation");
}

PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(T&& defaultInitialisationValue)
: data(std::forward<decltype(defaultInitialisationValue)>(defaultInitialisationValue))
{
    //initBughunt(__LINE__,intialiseToDefault,defaultInitialisationValue, static_cast<T>(1));
    initBughunt(__LINE__,"default initialisation with user value");
}

PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(const setupByWider auto&&    initMethod, T&& toValue_start, T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    //const_cast<T&>(static_cast<const array<T,size>&>(*this)[idx]);
    initBughunt(__LINE__,initMethod, static_cast<int>(toValue_start), static_cast<int>(proceedByOrWith_optional));

    if (compareInitMethod(initMethod, initialisationMethod::incrementFrom))
        init_incrementFrom(initMethod, std::forward<T>(proceedByOrWith_optional));
    else if (compareInitMethod(initMethod, initialisationMethod::decrementFrom))
        init_decrementFrom(initMethod, std::forward<T>(proceedByOrWith_optional));
    else if (compareInitMethod(initMethod, initialisationMethod::multiplyFromBy))
        init_multiplyFromBy(initMethod, std::forward<T>(proceedByOrWith_optional));
    else if (compareInitMethod(initMethod, initialisationMethod::divideFromBy))
        init_divideFromBy(initMethod, std::forward<T>(proceedByOrWith_optional));
}
/*
PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(const initialisationMethod initMethod, T&& toValue_start, T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    initBughunt(__LINE__,initMethod, static_cast<int>(toValue_start), static_cast<int>(proceedByOrWith_optional));

    if constexpr (undo_SetupBy(initMethod) == initialisationMethod::incrementFrom)
        init_incrementFrom(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
    else if constexpr (undo_SetupBy(initMethod) == initialisationMethod::decrementFrom)
        init_decrementFrom(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
    else if constexpr (undo_SetupBy(initMethod) == initialisationMethod::multiplyFromBy)
        init_multiplyFromBy(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
    else if constexpr (undo_SetupBy(initMethod) == initialisationMethod::divideFromBy)
        init_divideFromBy(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));

}*/

    // non-artithmetic types
PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(const setupByWider auto&&    initMethod, T&& toValue_start, T&& proceedByOrWith_optional)
requires(!std::is_arithmetic_v<T>) {
    initBughunt(__LINE__,static_cast<initialisationMethod>(initMethod), static_cast<int>(toValue_start), static_cast<int>(proceedByOrWith_optional));

    if constexpr (undo_SetupBy(initMethod) == initialisationMethod::incrementFrom)
        init_incrementFrom(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
    else if constexpr (undo_SetupBy(initMethod) == initialisationMethod::decrementFrom)
        init_decrementFrom(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
    else if constexpr (undo_SetupBy(initMethod) == initialisationMethod::multiplyFromBy)
        init_multiplyFromBy(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
    else if constexpr (undo_SetupBy(initMethod) == initialisationMethod::divideFromBy)
        init_divideFromBy(std::forward<T>(toValue_start), std::forward<T>(proceedByOrWith_optional));
}

/*PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(const initialisationMethod initMethod, T&& toValue_start, T&& proceedByOrWith_optional)
requires(!std::is_arithmetic_v<T>) {

}*/
    // char by string-like data
PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(const std::initializer_list<const T> values)
requires(anyOfType<T, char, char16_t, char32_t, wchar_t>)
{
    initBughunt(__LINE__,std::string_view(values));
    int cntr=-1;
    if (values.size() <= totalSize) {
        for(T i: values) data[++cntr]=i;

        for(;cntr<totalSize;) data[++cntr]=T{};
    }
    else {
        for(;cntr<totalSize;) data[++cntr]=values[cntr];
    }

    // old function part
    if (values.size() != sizeof(data)/sizeof(T))
    {
        std::cout << "Amount of elements in initializer list (" << values.size() << ") doesn't match array size: " << sizeof(data)/sizeof(T) << std::endl;
        throw 0;
    }

    for(T i: values)
    {
        #ifdef __DEBUG_ON
            std::cout << cntr << " = " << i << std::endl;
        #endif // __DEBUG_ON
        data[++cntr]=i;
    }
}

PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(const std::initializer_list<const std::basic_string_view<T>> values)
requires(anyOfType<T, char, char8_t, char16_t, char32_t, wchar_t>) {
    initBughunt(__LINE__,std::string_view(values));

    int fullLengthOfValues=0;
    for(auto i : values)
    fullLengthOfValues+=i.length();

    int cntr=-1;
    if (fullLengthOfValues <= totalSize) {
        for(auto& i: values) for(auto& j: i) data[++cntr]=j;

        for(;cntr<totalSize;) data[++cntr]=T{};
    }
    else {
        int numCharsProcessed=0;
        for(auto& i: values) for(auto& j: i) {data[++cntr]=j;
        }
        // for(;cntr<totalSize;) data[++cntr]=values[cntr];
    }

}

PREFIX
constexpr MULTIDIMENSIONALARRAY::multiDimensionalArray(std::string_view&& values)
requires(anyOfType<T, char, char16_t, char32_t, wchar_t>) {
        initBughunt(__LINE__,std::string_view(values));
        int cntr=-1;
        if (values.size() <= totalSize) {
            for(T i: values) data[++cntr]=i;

            for(;cntr<totalSize;) data[++cntr]=T{};
        }
        else {
            for(;cntr<totalSize;) data[++cntr]=values[cntr];
        }
}


PREFIX
inline constexpr detail::array<T,MULTIDIMENSIONALARRAY::totalSize>& MULTIDIMENSIONALARRAY::readData() const {
    return data;
}


PREFIX
constexpr void MULTIDIMENSIONALARRAY::init_typeDefaultTo(const T&& toValue_start, const T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    for(auto& e:data) e=toValue_start;
}

PREFIX
constexpr void MULTIDIMENSIONALARRAY::init_incrementFrom(const T&& toValue_start, const T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    data[0]=toValue_start;
    for(int i=1; i<totalSize; ++i) data[i]=data[i-1]+proceedByOrWith_optional;
}

PREFIX
constexpr void MULTIDIMENSIONALARRAY::init_decrementFrom(const T&& toValue_start, const T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    data[0]=toValue_start;
    for(int i=1; i<totalSize; ++i) data[i]=data[i-1]-proceedByOrWith_optional;
}

PREFIX
constexpr void MULTIDIMENSIONALARRAY::init_multiplyFromBy(const T&& toValue_start, const T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    data[0]=toValue_start;
    for(int i=1; i<totalSize; ++i) data[i]=data[i-1]*proceedByOrWith_optional;
}

PREFIX
constexpr void MULTIDIMENSIONALARRAY::init_divideFromBy(const T&& toValue_start, const T&& proceedByOrWith_optional)
requires(std::is_arithmetic_v<T>)
{
    data[0]=toValue_start;
    for(int i=1; i<totalSize; ++i) data[i]=data[i-1]/proceedByOrWith_optional;
}


PREFIX
template<int... VALUES>
constexpr size_t MULTIDIMENSIONALARRAY::getIndexMappedAs1D() const {
        const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
        using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
        const auto& n = VA_pack<VALUES...>::data::index;
        using neverUsed = decltype(n); // to check warnings

        size_t result{0};
        {
            size_t tempResult{0};
            for(int i=0; i<d; ++i) {
            	tempResult=1;//i+1; creates wrong values if set to i+1

                for(int j=i+1; j<d; ++j)  tempResult*=N::index[j];

                tempResult*=( (n[i]));
                result+=tempResult;
            }
        }
        #ifdef __DEBUG_ON
            std::cout << "   Offset: " << result << std::endl;
        #endif
        return result;
}

PREFIX
[[deprecated("Does not yet work, fix tuple to VA_pack and vice-versa")]]
constexpr size_t MULTIDIMENSIONALARRAY::getIndexMappedAs1D(decltype(dimensionBoundariesQuery::getAsTuple() )&& tuple) const {
    std::cout << "getIndexMappedAs1D::B" << std::endl;
    static_assert(totalSize == std::tuple_size_v<tuple>);
    return 69;
    #ifdef __DEBUG_ON
        std::cout << "Function does not work yet." << std::endl;
    #endif
/*
    using indices = std::make_index_sequence<totalSize-1>;
    auto d = MULTIDIMENSIONALARRAY::totalSize;
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    using n = VA_pack<VALUES...>::data;

    size_t result{0};
    {
        size_t tempResult{0};
        for(int i=0; i<d; ++i) {
        	tempResult=1;// creates wrong result if tempResult set to i+1
            for(int j=i+1; j<d; ++j)  tempResult*=N::index[j];

            tempResult*=( (n::index[i]));
            result+=tempResult;
                }
    }

    for(int i=0; i<totalSize; ++) std::get<i>(tuple);
    std::apply([](auto&&... args) {((std::cout << args << '\n'), ...);}, t);
    */
    return std::get<0>(tuple);
}
#ifdef __DEBUG_ON

    template<typename T,int... DIM>
    void bughunt<T,DIM...>::pushInfoToStream_Bitsize(const char* newlinePrefix, std::ostream& target) const {
        target << newlinePrefix << "bit size of data: " << sizeof(parent->data) <<  " (" <<  sizeof(parent->data)/sizeof(T) << " elements)\n";
        target << newlinePrefix << "bit size of struct: " << sizeof(*parent) <<  "\n";
    }

PREFIX
constexpr void MULTIDIMENSIONALARRAY::initBughunt(const int IDforCTOR, std::string_view argumentString)
{
    debug=std::unique_ptr<bughunt<T, DIM...>>(new bughunt<T, DIM...>(*this)); //new bughunt<T, DIM...>(*this);
    std::cout << CtrIDAtLine << IDforCTOR;
    if(argumentString!="")
    std::cout << " (" << argumentString <<")";
    std::cout << std::endl;
}

PREFIX
constexpr void MULTIDIMENSIONALARRAY::initBughunt(const int IDforCTOR, setupByWider auto initMethod, int asInt_value1, int asInt_value2)
{
    debug=std::unique_ptr<bughunt<T, DIM...>>(new bughunt<T, DIM...>(*this)); //new bughunt<T, DIM...>(*this);
    std::cout << CtrIDAtLine << IDforCTOR << " (" <<  aNDAr::detail::debug::initMethodName[static_cast<int>(static_cast<initialisationMethod>(initMethod))];
    if(asInt_value1!=0) std::cout <<", toValue_start: " << asInt_value1;
    if(asInt_value2!=1) std::cout << ", proceedByOrWith_optional: " << asInt_value2;
    std::cout  << ")" << std::endl;
}


    template<typename T,int... DIM>
    void bughunt<T,DIM...>::pushInfoToStream_Boundaries(const char* newlinePrefix, std::ostream& target) const  {
        target << newlinePrefix;
         (target  << "[" << DIM << "]", ...) << "\n";
        //for(int i=0, iMax = dimensionBoundaries.size-1; i<=iMax; ++i)
        //    target << "Index [" << i << "]   = " << (int)dimensionBoundaries.at(i) << '\n';
    }


template<typename T,int... DIM>
void bughunt<T,DIM...>::pushInfoToStream_ContentAsInteger(const char* newlinePrefix, std::ostream& target) const
{
    static_assert(std::is_convertible_v<T,int>,"Needs to be convertible to int.");
    target << newlinePrefix;
    //for(int i=0, iMax=sizeof(parent->data)/sizeof(T)-2; i<iMax; ++i) /// TODO totalSize#
    for(auto i = parent->begin(), iMax=parent->beforeEnd(2); i!=iMax; ++i)
        target << '\'' << asIntForConsolePrint(*i) << "\', ";
    target << '\'' << asIntForConsolePrint(*parent->beforeEnd(2)) << "\' and \'" <<  asInt(*parent->beforeEnd(1)) << "\'";
}

template<typename T,int... DIM>
void bughunt<T,DIM...>::pushInfoToStream_Content(const char* newlinePrefix, std::ostream& target) const
{
    if constexpr(!canPrintedByConsole_v<T>) {std::cout << "Not printable content:\n";
    for(auto i = parent->begin(), iMax=parent->beforeEnd(2); i!=iMax; ++i)
        target << "\'?\', ";
    target << "\'?\' and \'?\'" << std::endl;

    return;}
    else {
    //static_assert(canPrintedByConsole_v<T>,"Needs to be printable to console(std::osstream).");
    target << newlinePrefix;
    //for(int i=0, iMax=sizeof(parent->data)/sizeof(T)-2; i<iMax; ++i) /// TODO totalSize#
    for(auto i = parent->begin(), iMax=parent->beforeEnd(2); i!=iMax; ++i)
        target << '\'' << *i << "\', ";
    target << '\'' << *parent->beforeEnd(2) //parent->data[sizeof(parent->data)/sizeof(T)-2]
           << "\' and \'" << *parent->beforeEnd(1) << "\'";
        target << std::endl;
    }
}

    template<typename T,int... DIM>
    void bughunt<T,DIM...>::printSummary(bool printHeader) const {
        if(printHeader) std::cout << "[Array #" << ID << " SUMMARY]\n";
        std::cout << "  Amount elements: " << parent->totalSize << "\n    Boundaries\n ";
        pushInfoToStream_Boundaries("      ");
    }


    template<typename T,int... DIM>
    template<bool asInteger>
    void bughunt<T,DIM...>::printDetailedInfo() const {
    std::cout << "[Array #" << ID << " DETAILED REPORT]\n";
        printSummary(false);
    	//! std::cout << "  dimensionBoundaries " << amountdimensionBoundaries << "\n     Boundaries ";
        //std::cout << "  Amount dimensions: " << dimensionBoundaries.size << "\n    Boundaries\n ";
    	//(std::cout << "[" << DIM << "]", ...) << "\n   Total length " << sizeof(data)/sizeof(T)  << "\n        Content: ";
        //pushInfoToStream_Boundaries("      ");
        std::cout << "  Sizes\n";
        pushInfoToStream_Bitsize("    ");
        std::cout << "  Content:\n";
        if constexpr(asInteger) pushInfoToStream_ContentAsInteger("    ");
        else pushInfoToStream_Content("    ");
    	std::cout << std::endl;
    }

template<typename T,int... DIM>
template <bool asInteger>
void bughunt<T,DIM...>::printContent() const
{
    if constexpr(asInteger) pushInfoToStream_ContentAsInteger("");
    else pushInfoToStream_Content("");
    std::cout << std::endl;
}

/*
template<typename T, int... DIM>
constexpr void  multiDimensionalArray<T,DIM...>::mapIndices_debug(const int expectedIndex, std::initializer_list<const int>&& list) {
#ifdef __DEBUG_ON
    debug->printSummary();
    std::cout << "Accessing at indices: ";
    for(auto& x:list) std::cout << x << " ";
    std::cout << "\n";

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = std::data(list);
    size_t result{0};
    {
        size_t tempResult{0};
        for(int i=0; i<d; ++i) {
        	tempResult=1;//i+1; creates wrong values if set to i+1

            for(int j=i+1; j<d; ++j)  tempResult*=N::index[j];

            tempResult*=( (n[i]));
            result+=tempResult;
        }
    }
    std::cout << "  Result: " << result << "\nExpected: " << expectedIndex << "\n";
#endif
}
*/
#endif
#undef PREFIX
#undef MULTIDIMENSIONALARRAY
} // aNDAr
