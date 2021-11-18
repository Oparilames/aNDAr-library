// Copyright (C) 2021 Oparilames <oparilames@arcor.de>
// This file is subject to the GNU General Public License v3.0.
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.

#include "multiDimensionalArray.hpp"
#include "concepts.hpp"
#include <initializer_list>

#define MULTIDIMENSIONALARRAY template<typename T,int... DIM> multiDimensionalArray<T,DIM...>

// if no argument passed standard initialisation, else count upwards from start value (TODO: check if prefix increment operator for T exists)
template<typename T,int... DIM>
constexpr multiDimensionalArray<T,DIM...>::multiDimensionalArray(T startVal,bool b) {
	if(!b) return;
    if constexpr(std::is_integral_v<T>) --startVal;
    if constexpr(!std::is_convertible_v<T,int>) for(auto& e:data) e=++startVal;
    else {
		    int i=-1; for(auto& e:data)
			     e=static_cast<T>(++i);
        }
}

template<typename T,int... DIM>
constexpr multiDimensionalArray<T,DIM...>::multiDimensionalArray(std::initializer_list<T> values) {
      if (values.size() == sizeof(data)/sizeof(T)) {}else{ throw 0;};
    int cntr=-1;
    for(T i: values)
        data[++cntr]=i;
}



template<typename T,int... DIM>
constexpr multiDimensionalArray<T,DIM...>::multiDimensionalArray(std::initializer_list<std::string_view> values) requires(std::is_same_v<T, char>) {
    int cntr{0};
    for(auto& x: values) cntr+=x.length();
    if(cntr!=totalSize) {std::cout << "Provided Elements (" << cntr << ") don't match required array size:" << totalSize << "\n";return; }

    cntr=-1;
    for(std::string_view list: values)
        for(char j: list)
            data[++cntr]=j;
}
template<typename T,int... DIM>
constexpr multiDimensionalArray<T,DIM...>::multiDimensionalArray(std::string_view values) requires(std::is_same_v<T, char>) {
    int cntr=values.length();
    if(cntr!=totalSize) {std::cout << "Provided Elements (" << cntr << ") don't match required array size:" << totalSize << "\n";return; }
    cntr=-1;
    for(char i: values) {
        std::cout << i << std::endl;
        data[++cntr]=i;
        }
}

template<typename T,int... DIM>
template<T... VALUES>
constexpr void multiDimensionalArray<T,DIM...>::setAll() {
	errorCheck_amountValuesEqualsArraySize<VALUES...>();
        size_t i = 0;
       (void(data[i++] = VALUES) , ...);
	}

  template<typename T,int... DIM>
      constexpr void multiDimensionalArray<T,DIM...>::setAll(std::initializer_list<T> values) {
            if (values.size() == sizeof(data)/sizeof(T)) {}else{ throw 0;};
        //std::cout << "size/bound\t" << values.size() << '/' << sizeof(data)/sizeof(T) << std::endl;
      		//static_assert(values.size() != sizeof(data)/sizeof(T), "Wrong number of values for array.");
          int cntr=-1;
          for(T i: values)
              data[++cntr]=i;
      }

 template<typename T,int... DIM>
    template<int... VALUES>
        inline constexpr auto& multiDimensionalArray<T,DIM...>::get() const {
            errorCheck_amountValuesEqualsDimensionsAvailable<VALUES...>();
            return data[getMappedIndex<VALUES...>()];
  	    }

 template<typename T,int... DIM>
    template<int... VALUES>
        inline constexpr void multiDimensionalArray<T,DIM...>::set(const T value) {
            errorCheck_amountValuesEqualsDimensionsAvailable<VALUES...>();
            data[getMappedIndex<VALUES...>()]=value;
  	    }

  template<typename T,int... DIM>
    template<int... VALUES>
  	constexpr size_t multiDimensionalArray<T,DIM...>::getMappedIndex(int expectedIndex) const {
        errorCheck_amountValuesEqualsDimensionsAvailable<VALUES...>();
    	errorCheck_ValuesWithinBoundary<VALUES...>();
        numberPack<VALUES...> access;

    #define d dimensionBoundaries.size
    #define N dimensionBoundaries
    #define n access
/*
    const int d{dimensionBoundaries.size};
    const int N[d]= dimensionBoundaries.index;//{dim1, dim2, dim3};
    const int n[d]=access.index;// {I, J, K}; // .index
*/
    size_t result{0};
    {
    size_t tempResult{0};

    for(int i=0; i<d; ++i) {
    	tempResult=1;//i+1; creates wrong values if set to i+1
        for(int j=i+1; j<d; ++j)  tempResult*=N[j];
        tempResult*=( (n[i]));
        result+=tempResult;
    }}

    #undef d
    #undef N
    #undef n
    return result;
}


namespace debug
{
    template<typename T,int... DIM>
        using baseClassAccess = multiDimensionalArray<T,DIM...>;
};
template<typename T,int... DIM>
constexpr void debug::multiDimensionArray<T,DIM...>::pushInfoToStream_Bitsize(const char* newlinePrefix, std::ostream& target) const {
    target << newlinePrefix << "bit size of data: " << sizeof(baseClassAccess::data) <<  " (" <<  sizeof(baseClassAccess::data)/sizeof(T) << " elements)\n";
    target << newlinePrefix << "bit size of struct: " << sizeof(*this) <<  "\n";
}


template<typename T,int... DIM>
constexpr void debug::multiDimensionArray<T,DIM...>::pushInfoToStream_Boundaries(const char* newlinePrefix, std::ostream& target) const  {
    target << newlinePrefix;
     (target  << "[" << DIM << "]", ...) << "\n";
    //for(int i=0, iMax = dimensionBoundaries.size-1; i<=iMax; ++i)
    //    target << "Index [" << i << "]   = " << (int)dimensionBoundaries.at(i) << '\n';
}


template<typename T,int... DIM>
constexpr void debug::multiDimensionArray<T,DIM...>::pushInfoToStream_ContentAsInteger(const char* newlinePrefix, std::ostream& target) const {
    static_assert(std::is_convertible_v<T,int>,"Needs to be convertible to int.");
    target << newlinePrefix;
    for(int i=0, iMax=sizeof(baseClassAccess::data)/sizeof(T)-2; i<iMax; ++i) /// TODO totalSize#
        target << '\'' << asInt(baseClassAccess::data[i]) << "\', ";
    target << '\'' << asInt(baseClassAccess::data[sizeof(baseClassAccess::data)/sizeof(T)-2]) << "\' and \'" <<  asInt(baseClassAccess::data[sizeof(baseClassAccess::data)/sizeof(T)-1]) << "\'\n";
}

template<typename T,int... DIM>
constexpr void debug::multiDimensionArray<T,DIM...>::pushInfoToStream_Content(const char* newlinePrefix, std::ostream& target) const {
    static_assert(canBeOutput_v<T>,"Needs to be printable.");
    target << newlinePrefix;
    for(int i=0, iMax=sizeof(baseClassAccess::data)/sizeof(T)-2; i<iMax; ++i) /// TODO totalSize#
        target << '\'' << baseClassAccess::data[i] << "\', ";
        target << '\'' << baseClassAccess::data[sizeof(baseClassAccess::data)/sizeof(T)-2] << "\' and \'" <<  baseClassAccess::data[sizeof(baseClassAccess::data)/sizeof(T)-1] << "\'\n";
        target << std::endl;
}

template<typename T,int... DIM>
void debug::multiDimensionArray<T,DIM...>::printSummary(bool printHeader) const {
    if(printHeader) std::cout << "[Array #" << ID << " SUMMARY]\n";
    std::cout << "  Amount dimensions: " << baseClassAccess::dimensionBoundaries.size << "\n    Boundaries\n ";
    pushInfoToStream_Boundaries("      ");
}


template<typename T,int... DIM>
template<bool asInteger>
void debug::multiDimensionArray<T,DIM...>::printDetailedInfo() const {
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
void debug::multiDimensionArray<T,DIM...>::printContent() const {
    if constexpr(asInteger) pushInfoToStream_ContentAsInteger("");
    else pushInfoToStream_Content("");
    std::cout << std::endl;
}

template<typename T,int... DIM>
template<int... VALUES>
constexpr size_t debug::multiDimensionArray<T,DIM...>::getMappedIndex(int expectedIndex) const {
    numberPack<VALUES...> access;
  	static_assert(access.size == baseClassAccess::dimensionBoundaries.size, "Wrong number of values for array.");
    static_assert(baseClassAccess::dimensionBoundaries.template areAllIndicesSmallerThan< VALUES... >(),"Declared index not within array boundaries.");

    #define d baseClassAccess::dimensionBoundaries.size
    #define N baseClassAccess::dimensionBoundaries
    #define n access


    size_t result{0};
    {
    size_t tempResult{0};

    for(int i=0; i<d; ++i) {
    	tempResult=1;//i+1; creates wrong values if set to i+1
        for(int j=i+1; j<d; ++j)  tempResult*=N[j];
        tempResult*=( (n[i]));
        result+=tempResult;
    }}

    #undef d
    #undef N
    #undef n

    std::cout << "["; for(int i=0; i<access.size; ++i) std::cout << access[i] << " "; std::cout << "] mapping …\n";
    std::cout <<"   expected index: " << [=]{
        if(expectedIndex==-1) return std::string_view("not specified");
        else return std::string_view(std::to_string(expectedIndex));}()
     << "\n";
    std::cout << "   Offset: " << result << std::endl;
    std::cin.get();
    return result;
}












/*




int addValue{0};
int offset{0};


    {
        for(int currentDimensionIndex=dimensionBoundaries.size-1; currentDimensionIndex >0;  --currentDimensionIndex){
            int elementIndex = access[currentDimensionIndex];
            for(int j=0, jMax=currentDimensionIndex-1; j<jMax; ++j)
            offset+=dimensionBoundaries[j]*elementIndex;

            //int prevDimLen = dimensionBoundaries[currentDimensionIndex-1];
            std::cout << "given index: " << elementIndex << "   for dimension index: " << currentDimensionIndex << std::endl;
             //addValue+=elementIndex*prevDimLen;
        } offset+=addValue; std::cout << "Offset: " << offset << std::endl;
        }

        std::cin.get();



        // int x[3][5] row-major        3 elements, each of which is an array of 5 integers.
        /// {0, 1, 2, 3, 4}, {5, 6, 7, 8, 9}, {10, 11, 12, 13, 14}
        ///
        //                                    [0] [1] [2] [3] [4]
        ///                             [0] {  0,  1,  2,  3,  4   }
        ///                             [1] {  5,  6,  7,  8, [9]  }
        ///                             [2] { 10, 11, 12, 13, 14   }

        ///                             x[1][4]=9
        ///for(int i=dimensionBoundaries.size-1; i>=0; --i) {// {1, 0}
        ///    std::cout << "{i}\n   ";
        ///    for(int j=dimensionBoundaries[i]-1; j>=0; --j) //  {4,3,2,1,0}, {2,1,0}
        ///        std::cout << j << " ";
        ///    std::cout << std::endl;
        ///    }

        std::size_t mappedIndexFinal{access.productOfElementsStartWithOne};
        if(data[mappedIndexFinal-1] != expectedIndex){ std::cout <<"   expected data: " << expectedIndex << " vs. mapped index: " << mappedIndexFinal-1<<"\n";}
        else {
            std::cout << "   to data[" << mappedIndexFinal-1 << "] = " << data[mappedIndexFinal-1]; if(expectedIndex>-1)std::cout << " (Expeced:" << expectedIndex << ")"; std::cout << std::endl;
        }
        std::cout << std::endl;
        //return mappedIndexFinal;


  		int mappedOffset{0};
  		// int i=0
  		// SUMME von  (PRODUCT(dimensionBoundaries.size[i+1])*access.(i) )
  		// $\sum_{i=1}^{amount\ dimensions}\left(\prod_{j = i+1}^{/phi}\right) access.get(i)$
  		for(int i=0; i<dimensionBoundaries.size; ++i) {
            const auto addition=[&,*this]{
  			                           int offsetCurrentDimension{1};
  			                           for(int j=i+1; j < dimensionBoundaries.size; ++j)
  			                               offsetCurrentDimension *= (int)dimensionBoundaries[j];
  			                           return offsetCurrentDimension;
                                   }()
  							 //* access[i]
                             ;///access.get(i);
            std::cout << "+" << addition << "*" << access[i] << "=" <<addition*access[i] << std::endl;
            mappedOffset+=addition;
        }
        std::cout << "mappedOffset: " << mappedOffset << std::endl;
  		return mappedOffset;
}
*/

/*
template<typename T,int... DIM>
multiDimensionalArray::

template<typename T,int... DIM>
multiDimensionalArray::

template<typename T,int... DIM>
multiDimensionalArray::

template<typename T,int... DIM>
multiDimensionalArray::

template<typename T,int... DIM>
multiDimensionalArray::

template<typename T,int... DIM>
multiDimensionalArray::

*/
#undef MULTIDIMENSIONALARRAY
