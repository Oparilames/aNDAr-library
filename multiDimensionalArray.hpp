// Copyright (C) 2021 Oparilames <oparilames@arcor.de>
// This file is subject to the GNU General Public License v3.0.
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.
#ifndef INCLUDEGUARD_MULTIDIMENSIONALARRAY
#define INCLUDEGUARD_MULTIDIMENSIONALARRAY
  #include "array.cpp"
  #include "variadicParameterPacks.hpp"
  #include <type_traits>  // remove_cvref_t
  #include <initializer_list> // std::initializer_list
  #include <iostream>
  #include <ostream>
  template<typename T,int... DIM>
  struct multiDimensionalArray {
      static_assert(((DIM>=0) && ...), "Can't create array with boundary size smaller than 1. Did you tried to access an existing array? Try [...], at(...), at<...>(), get<...>() or set<...>().");

      inline constexpr static numberPack<DIM...> dimensionBoundaries{};
      inline constexpr static size_t totalSize{dimensionBoundaries.productOfElements};
      static_assert(dimensionBoundaries.productOfElements!=1, "Can't create 1D array.");

      T data[totalSize]{T{}};

      constexpr multiDimensionalArray(T startVal=T{}, bool incrementalInitialisation=false);
      constexpr multiDimensionalArray(std::initializer_list<T> values);
      constexpr multiDimensionalArray(std::initializer_list<std::string_view> values) requires(std::is_same_v<T, char>);
      constexpr multiDimensionalArray(std::string_view values) requires(std::is_same_v<T, char>);

      constexpr auto operator[] (int indexToFind) const {return at(indexToFind);};

      constexpr const T& at(int idx) const {if(idx>=totalSize || idx<0) throw std::invalid_argument("Index out of array boundary."); return data[idx];} // not necessarily needed?

      template<int... VALUES>
            constexpr size_t getMappedIndex(int expectedIndex=-1) const;

      template<int... VALUES>
            inline constexpr auto& get() const;
      template<int... VALUES>
            inline constexpr void set(const T value) ;

      template<T... VALUES>
            constexpr void setAll();

      constexpr void setAll(std::initializer_list<T> values);

private:
    template<T... VALUES>
    consteval static void errorCheck_amountValuesEqualsDimensionsAvailable() {
        static_assert(dimensionBoundaries.size == sizeof...(VALUES), "Array dimensions don't match given amount of dimensions");
    }

    template<T... VALUES>
    consteval static void errorCheck_amountValuesEqualsArraySize() {
        //numberPack<VALUES...> access;
        //static_assert(access.size == dimensionBoundaries.size, "Wrong number of values for array.");
        static_assert(sizeof...(VALUES) == sizeof(data)/sizeof(T), "Values don't match amount of elements in array.");
    }
        template<T... VALUES>
    consteval static void errorCheck_ValuesWithinBoundary() {
    	static_assert(dimensionBoundaries.template areAllIndicesSmallerThan< VALUES... >(),"Declared index not within array boundaries.");
    }
  };

namespace debug
{
  template<typename T,int... DIM>
  struct multiDimensionArray: public ::multiDimensionalArray<T,DIM...>{
     using baseClassAccess = multiDimensionalArray<T,DIM...>;

    const counter<struct mdarray_debug_tag> ID{};
    const counter<multiDimensionalArray<T,DIM...>> ID_exactBoundaries{};



    consteval const size_t get1DLength() const {return sizeof(baseClassAccess::data)/sizeof(T);}
    consteval const void setValueOf1DIndexTo(int IDX) {baseClassAccess::data[IDX]=IDX;}
    consteval const void setValueOf1DIndexTo(int IDX, int val) {baseClassAccess::data[IDX]=val;}
    consteval const T getValueOf1DIndex(int IDX) const {return baseClassAccess::data[IDX];}




    constexpr void pushInfoToStream_ID() {
        std::cout << "  ID: " << ID<<"/" << ID.getMax() << "\n";
        std::cout << "  ID within arrays of the same dimension and type: " << ID_exactBoundaries << "/" << ID_exactBoundaries.getMax() << "\n";
    }
private:
    constexpr void pushInfoToStream_Bitsize(const char* newlinePrefix, std::ostream& target=std::cout) const;
    constexpr void pushInfoToStream_Boundaries(const char* newlinePrefix, std::ostream& target=std::cout) const ;
    constexpr void pushInfoToStream_ContentAsInteger(const char* newlinePrefix, std::ostream& target=std::cout) const;
    constexpr void pushInfoToStream_Content(const char* newlinePrefix, std::ostream& target=std::cout) const;
public:
    template <bool asInteger=false>
        void printDetailedInfo() const ;
        void printSummary(bool printHeader=true) const;

    template <bool asInteger=false>
        void printContent() const;


    template<int... VALUES>
        constexpr size_t getMappedIndex(int expectedIndex=-1) const;
  };
}; // debug
#endif // INCLUDEGUARD_MULTIDIMENSIONALARRAY
