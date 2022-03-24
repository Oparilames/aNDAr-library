#ifndef INCLUDEGUARD_INLINE_MULTIDIMENSIONALARRAY
#define INCLUDEGUARD_INLINE_MULTIDIMENSIONALARRAY
#include <aNDAr/multiDimensionalArray.hpp>


namespace aNDAr {

#define PREFIX template<typename T, int... DIM>
#define MULTIDIMENSIONALARRAY multiDimensionalArray<T,DIM...>

#ifdef __DEBUG_ON

// 2022: changed to != instead of ==
template<typename T, int... DIM>
template<T... VALUES>
consteval void multiDimensionalArray<T,DIM...>::errorCheck_amountValuesEqualsDimensionsAvailable() {
    static_assert(VA_pack<VALUES...>::data::size == dimensionBoundariesValue::size, "Array dimensions don't match given amount of dimensions");

}

template<typename T, int... DIM>
template<T... VALUES>
consteval void multiDimensionalArray<T,DIM...>::errorCheck_amountValuesEqualsArraySize() {
    VA_pack<DIM...> me;
    static_assert(VA_pack<VALUES...>::canHold(VA_pack<DIM...>{}), "Values don't match amount of elements in array.");
    /// static_assert(sizeof...(VALUES) == sizeof(data)/sizeof(T), "Values don't match amount of elements in array.");
}

template<typename T, int... DIM>
template<T... VALUES>
consteval void multiDimensionalArray<T,DIM...>::errorCheck_ValuesWithinBoundary() {
    /// static_assert(dimensionBoundaries.template areAllIndicesSmallerThan< VALUES... >(),"Declared index not within array boundaries.");
}
#endif

PREFIX std::optional<T> MULTIDIMENSIONALARRAY::writeDataAtIndex(T&& toWrite, int atIndices,...) {

}

PREFIX
[[deprecated("Currently without use?")]]
inline constexpr void MULTIDIMENSIONALARRAY::operator()() const{
}

PREFIX
template<int... VALUES>
inline constexpr const T& MULTIDIMENSIONALARRAY::operator()() const
requires(!std::is_same_v<T,void>)
{
	#ifdef __DEBUG_ON
    MULTIDIMENSIONALARRAY::errorCheck_amountValuesEqualsDimensionsAvailable<VALUES...>();
    MULTIDIMENSIONALARRAY::errorCheck_ValuesWithinBoundary<VALUES...>();
    #endif
    return data[static_cast<int>(getIndexMappedAs1D<VALUES...>())];
}

/*
PREFIX const int MULTIDIMENSIONALARRAY::randomAccess(multiArAcces auto index) {
    const auto& n = index;
    std::cout << n[0] << "/" << n[totalSize-1] << std::endl;
}
*/
//template<typename T, int... DIM>
PREFIX inline constexpr T& MULTIDIMENSIONALARRAY::operator[] (int indexToFind[totalSize]) {
    #ifdef __DEBUG_ON
        std::cout << "Access A" << std::endl;
    #endif

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = indexToFind;
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
    return data[result];
};

template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](int idx) const {
    #ifdef __DEBUG_ON
        std::cout << "Access B" << std::endl;
    #endif
    return const_cast<T&>(static_cast<const T&>(data[idx]));
    //return const_cast<T&>(static_cast<const T&>(data[idx]));//const_cast<T&>(static_cast<const multiDimensionalArray<T,DIM...>&>(*this)[idx]);
}


template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](const int (&indexToFind)[totalSize]) {
    #ifdef __DEBUG_ON
        std::cout << "Access C (mapping to check)" << std::endl;
    #endif

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = indexToFind;

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
    return data[result];
}


template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](decltype(dimensionBoundariesQuery::getAsTuple() )&& tuple) {
    std::cout << "Access T (mapping to implement)" << std::endl;
    return data[0];//data[result];
}

template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](std::initializer_list<const int>&& list) {
    #ifdef __DEBUG_ON
        std::cout << "Access D" << std::endl;
    #endif
    if(list.size() >= totalSize) { std::cout << "Out of boundary"<<std::endl; return data[0];}

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
    #ifdef __DEBUG_ON
        std::cout << "   Offset: " << result << std::endl;
    #endif
    return data[result];
}

template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](withRandomAccessIterator auto containerWithIndicesToFind) {
    #ifdef __DEBUG_ON
        std::cout << "Access E" << std::endl;
    #endif
    if(containerWithIndicesToFind.size() >= totalSize) { std::cout << "Out of boundary"<<std::endl; return data[0];}

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = std::data(containerWithIndicesToFind);

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
    return data[result];
}

template<typename T, int... DIM>
inline consteval T& multiDimensionalArray<T,DIM...>::operator[](const int (&&indexToFind)[totalSize]) {
    #ifdef __DEBUG_ON
        std::cout << "Access F (to check)" << std::endl;
    #endif

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = indexToFind;

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
    return data[result];
}



template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](const int (indexToFind)[totalSize])
requires(sizeof(int)*totalSize<=sizeof(int*)) {
    #ifdef __DEBUG_ON
        std::cout << "Access G (to check)" << std::endl;
    #endif

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = indexToFind;

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
    return data[result];
}



template<typename T, int... DIM>
inline constexpr T& multiDimensionalArray<T,DIM...>::operator[](const int (&indexToFind)[totalSize])
requires(sizeof(int)*totalSize>sizeof(int*)) {
    #ifdef __DEBUG_ON
        std::cout << "Access H (to check)" << std::endl;
    #endif

    const int d = static_cast<int>(MULTIDIMENSIONALARRAY::dimensionBoundariesQuery::data::size);
    using N = MULTIDIMENSIONALARRAY::dimensionBoundariesValue;
    const auto& n = indexToFind;

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
    return data[result];
}




template<typename T, int... DIM>
template<int... VALUES>
constexpr auto& multiDimensionalArray<T,DIM...>::at() const
requires(sizeof...(VALUES) == totalSize) {

}

template<typename T, int... DIM>
constexpr T& multiDimensionalArray<T,DIM...>::at(int idx) const {

}



























} // aNDAr
#undef PREFIX
#undef MULTIDIMENSIONALARRAY
// because it's a template class source code needs to stay in the same translation unit
#include <aNDAr/multiDimensionalArray.cpp>
#endif // INCLUDEGUARD_INLINE_MULTIDIMENSIONALARRAY
