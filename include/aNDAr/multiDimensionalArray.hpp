// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.

// Interface for multi-dimensional array struct
#ifndef INCLUDEGUARD_MULTIDIMENSIONALARRAY
#define INCLUDEGUARD_MULTIDIMENSIONALARRAY
#include <optional>
#ifdef __DEBUG_ON
    //#include "counter.cpp"
    #include <aNDAr/counter.inl>
#endif // __DEBUG_ON
#include <initializer_list> // std::initializer_list
#include <memory> // std::unique_ptr
#include <aNDAr/variadicParameterPacks.hpp>
#include <aNDAr/initialisation.hpp>
#include <aNDAr/array.hpp>

namespace std {
    typedef decltype(nullptr) nullptr_t;
};
namespace aNDAr {
template<typename T, int... DIM>
struct bughunt;

template<typename T, int... DIM>
struct multiDimensionalArray
{
    static_assert(((DIM>=0) && ...), "Can't create multidimensional array with boundary size smaller than 1. Did you tried to access an existing one? Try [...], at, get or set methods called func_runtimeVariables(...) or func_compileTimeExpressions<...>().");

    using dimensionBoundariesQuery = VA_pack<DIM...>;
    using dimensionBoundariesValue = typename dimensionBoundariesQuery::data;

    constexpr static size_t totalSize{dimensionBoundariesValue::productOfElements};
    static_assert((totalSize!=1), "Can't create 1D array. To create use aNDAr::array or your favorite array datatype/struct.");
    constexpr static size_t amountDimensions{dimensionBoundariesQuery::data::size};

private:
    //T data[totalSize]{T{}};
    detail::array<T,totalSize> data; // takes care about default initialisation for T
    constexpr int getMappedIndex2022(auto&& n);
public:
    /// CTors
    constexpr multiDimensionalArray();
    constexpr multiDimensionalArray(T&& defaultInitialisationValue);

    constexpr multiDimensionalArray(const setupByWider auto&&    initMethod, T&& toValue_start=static_cast<T>(0), T&& proceedByOrWith_optional=static_cast<T>(1))
    requires(std::is_arithmetic_v<T>);
    constexpr multiDimensionalArray(const initialisationMethod initMethod, T&& toValue_start=static_cast<T>(0), T&& proceedByOrWith_optional=static_cast<T>(1)) requires(std::is_arithmetic_v<T>);

    // non-artithmetic types
    constexpr multiDimensionalArray(const setupByWider auto&&    initMethod, T&& toValue_start=T{}, T&& proceedByOrWith_optional=T{})
    requires(!std::is_arithmetic_v<T>);
    constexpr multiDimensionalArray(const initialisationMethod initMethod, T&& toValue_start=T{}, T&& proceedByOrWith_optional=T{})    requires(!std::is_arithmetic_v<T>);

    // char by string-like data
    constexpr multiDimensionalArray(const std::initializer_list<const T> values)
    requires(anyOfType<T, char, char16_t, char32_t, wchar_t>);

    constexpr multiDimensionalArray(const std::initializer_list<const std::basic_string_view<T>> values)
    requires(anyOfType<T, char, char8_t, char16_t, char32_t, wchar_t>);

    constexpr multiDimensionalArray(std::string_view&& values)
    requires(anyOfType<T, char, char16_t, char32_t, wchar_t>);

    /// Setters
template<int... VALUES>
    constexpr void set(const T value) ;

    std::optional<T> writeDataAtIndex(T&& toWrite, int atIndices,...);

    constexpr void setAll(std::initializer_list<T> values);

    /// Getters/access
    inline constexpr void operator()() const; // conflict with default C'TOR
template<int... VALUES>
    inline constexpr const T& operator()() const
    requires(!std::is_same_v<T,void>)
    ;
	
    constexpr detail::array<T,totalSize>& readData() const;

    //// 2022 constexpr T& operator[] (int indexToFind[amountDimensions]);
    constexpr T& operator[](int idx) const;

    constexpr T& operator[](const int (&indexToFind)[amountDimensions]);

    constexpr T& operator[](std::initializer_list<const int>&& list);

    constexpr T& operator[](decltype(dimensionBoundariesQuery::getAsTuple() )&& tuple);

    // std::array, std::span, possibly std::views
    constexpr T&operator[](withRandomAccessIterator auto containerWithIndicesToFind);

    // Access operators for c-style arrays
    // int array variable rvalue
    inline consteval T& operator[](const int (&&indexToFind)[amountDimensions]);

    // int array lvalue
    constexpr T& operator[](const int (indexToFind)[amountDimensions])
    requires(sizeof(int)*totalSize<=sizeof(int*));

    // int array reference
    constexpr T& operator[](const int (&indexToFind)[amountDimensions])
    requires(sizeof(int)*totalSize>sizeof(int*));


    template<int... VALUES>
    constexpr auto& at() const
    requires(sizeof...(VALUES) == amountDimensions);
    constexpr T& at(int idx) const; // also get?


    /// Iterators and debugging

    constexpr detail::array<T,totalSize>::Iterator begin(){return data.begin();}
    constexpr detail::array<T,totalSize>::Iterator end(){return data.end();}
    constexpr detail::array<T,totalSize>::Iterator beforeEnd(const int howMany){ return data.beforeEnd(howMany);}

private:
    constexpr void init_typeDefaultTo(const T&& userVal, const T&& userSecondVal) requires(std::is_arithmetic_v<T>);
    constexpr void init_incrementFrom(const T&& userVal, const T&& userSecondVal) requires(std::is_arithmetic_v<T>);
    constexpr void init_decrementFrom(const T&& userVal, const T&& userSecondVal) requires(std::is_arithmetic_v<T>);
    constexpr void init_multiplyFromBy(const T&& userVal, const T&& userSecondVal) requires(std::is_arithmetic_v<T>);
    constexpr void init_divideFromBy(const T&& userVal, const T&& userSecondVal) requires(std::is_arithmetic_v<T>);


    template<int... VALUES>
    constexpr size_t getIndexMappedAs1D() const;
    /// TODO: like previous one but replace VALUES... by content of tuple at compiletime
    //constexpr size_t getIndexMappedAs1D(decltype(dimensionBoundaries.template getAsTuple() )&& tuple) const;
    constexpr size_t getIndexMappedAs1D(decltype(dimensionBoundariesQuery::getAsTuple() )&& tuple) const;

public:

// end of checked part of struct. Here comes bugfixing and detail stuff the user won't need to worry about.
// debug class, use with caution
#ifdef __DEBUG_ON
	inline static int accessHappened[10]{0}; // for each [] overload 
    friend class bughunt<T, DIM...>;
    std::unique_ptr<bughunt<T, DIM...>> debug;
private:
    template<T... VALUES>
    consteval static void errorCheck_amountValuesEqualsDimensionsAvailable();

    template<T... VALUES>
    consteval static void errorCheck_amountValuesEqualsArraySize();

    template<T... VALUES>
    consteval static void errorCheck_ValuesWithinBoundary();

    constexpr void initBughunt(const int IDforCTOR, std::string_view argumentString="");
    constexpr void initBughunt(const int IDforCTOR, setupByWider auto initMethod, int asInt_value1, int asInt_value2);
    constexpr void initBughunt(const int IDforCTOR, setupByWider auto initMethod, const char* asInt_value1, const char* asInt_value2);
#else // __DEBUG_ON
    constexpr void initBughunt(const int IDforCTOR, std::string_view argumentString=""){}
    constexpr void initBughunt(const int IDforCTOR, setupByWider auto initMethod, int asInt_value1, int asInt_value2){}
    constexpr void initBughunt(const int IDforCTOR, setupByWider auto initMethod, const char* asInt_value1, const char* asInt_value2){}
    //public:~multiDimensionalArray() {std::cout << "Destroyed!\n";}private:
#endif // endif




/// test, improve and implement everything beyond this point.
/// once done, IMMEDIATELY cut and paste to a suitable line in code base above.
/// User relevant functions/data must be put higher up than internal stuff.









}; // multiDimensionalArray


#ifdef __DEBUG_ON
  template<typename T,int... DIM>
  struct bughunt {
      using baseType = multiDimensionalArray<T,DIM...>;
      baseType* const parent;
      bughunt() = delete;
      bughunt(baseType& par):parent(&par){}
      ~bughunt() {
		  printContent();
		  for(int i=0; i<10; ++i)
		  if(baseType::accessHappened[i]>0) std::cout << '[' << static_cast<char>('A'+i) <<"] Access (" << i << ") has happened " << baseType::accessHappened[i] << " time" << [](bool x){if (x) return "s"; return "";}(baseType::accessHappened[i]>1) << ".\n";
		}
      const detail::counter<struct mdarray_debug_tag> ID{};
      const detail::counter<baseType> ID_exactBoundaries{};
      consteval const void setValueOf1DIndexTo(int IDX, int val) {parent.data[IDX]=val;}
      consteval const T getValueOf1DIndex(int IDX) const {return parent.data[IDX];}
      constexpr void pushInfoToStream_ID() {
          std::cout << "  ID: " << parent.ID<<"/" << parent.ID.getMax() << "\n";
          std::cout << "  ID within arrays of the same dimension and type: " << ID_exactBoundaries << "/" << ID_exactBoundaries.getMax() << "\n";
      }
      VA_pack<DIM...> mappedIndexFrom1D(int index) const;
  private:
      void pushInfoToStream_Bitsize(const char* newlinePrefix, std::ostream& target=std::cout) const;
      void pushInfoToStream_Boundaries(const char* newlinePrefix, std::ostream& target=std::cout) const ;
      void pushInfoToStream_ContentAsInteger(const char* newlinePrefix, std::ostream& target=std::cout) const;
      void pushInfoToStream_Content(const char* newlinePrefix, std::ostream& target=std::cout) const;
  public:
      template <bool asInteger=false>
        void printDetailedInfo() const ;
        void printSummary(bool printHeader=true) const;

      template <bool asInteger=false>
        void printContent() const;
        constexpr size_t getIndexMappedAs1D(const int values,...) const;

        void sizeInfo() {
            int i=0, iMax=sizeof(parent->data)/sizeof(T)-2;
            std::cout << i << " – " << iMax << " vs. " << i << " – " << parent->totalSize-2 << std::endl;
        }
  };
  #endif // __DEBUG_ON
}; // aNDAr
#include <aNDAr/multiDimensionalArray.inl>
#ifdef __SHORTNAMES_ON
    #include <aNDAr/shortNames.inl>
#endif
#endif // INCLUDEGUARD_MULTIDIMENSIONALARRAY
