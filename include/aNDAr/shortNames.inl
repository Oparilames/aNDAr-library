// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.
//
// Optional file offering name shortcuts for several N-Dimensional array/vector types
//#include "multiDimensionalArray.hpp"
//#include "multiDimensionalVector.hpp"
namespace aNDAr {
	namespace shortName {
#ifdef INCLUDEGUARD_MULTIDIMENSIONALARRAY
#ifndef INCLUDEGUARD_SHORTNAMES_ARRAY
#define INCLUDEGUARD_SHORTNAMES_ARRAY
/*
// main class of the library
template<typename T,int... DIM>
    struct multiDimensionalArray;
*/
#include <aNDAr/multiDimensionalArray.hpp>
/*template<typename T,int... DIM>
    using multiDimensionalArray = aNDAr::multiDimensionalArray<T,DIM...>;
  */  
// alternative class names
template<typename T,int... DIM>
    using arND = aNDAr::multiDimensionalArray<T,DIM...>;
template<typename T,int D1st, int D2nd>
    using ar2D = aNDAr::multiDimensionalArray<T,D1st, D2nd>;
    template<typename T,int D1st, int D2nd, int D3rd>
    using ar3D = aNDAr::multiDimensionalArray<T,D1st, D2nd, D3rd>;
template<typename T,int D1st, int D2nd, int D3rd, int D4th>
    using ar4D = aNDAr::multiDimensionalArray<T,D1st, D2nd, D3rd,D4th>;
template<typename T,int... DIM>
    using arrayND = aNDAr::multiDimensionalArray<T,DIM...>;
template<typename T,int D1st, int D2nd>
    using array2D = aNDAr::multiDimensionalArray<T,D1st, D2nd>;
    template<typename T,int D1st, int D2nd, int D3rd>
    using array3D = aNDAr::multiDimensionalArray<T,D1st, D2nd, D3rd>;
template<typename T,int D1st, int D2nd, int D3rd, int D4th>
    using array4D = aNDAr::multiDimensionalArray<T,D1st, D2nd, D3rd,D4th>;
#endif // INCLUDEGUARD_SHORTNAMES_ARRAY
#endif // INCLUDEGUARD_MULTIDIMENSIONALARRAY

#ifdef INCLUDEGUARD_MULTIDIMENSIONALVECTOR
#ifndef INCLUDEGUARD_SHORTNAMES_VECTOR
#define INCLUDEGUARD_SHORTNAMES_VECTOR
template<typename T,int... DIM>
    struct aNDAr::multiDimensionalVector;

template<typename T,int... DIM>
using vecND = aNDAr::multiDimensionalVector<T,DIM...>;
template<typename T,int D1st, int D2nd>
using vec2D = aNDAr::multiDimensionalVector<T,D1st, D2nd>;
template<typename T,int D1st, int D2nd, int D3rd>
using vec3D = aNDAr::multiDimensionalVector<T,D1st, D2nd, D3rd>;
template<typename T,int D1st, int D2nd, int D3rd, int D4th>
using vec4D = aNDAr::multiDimensionalVector<T,D1st, D2nd, D3rd,D4th>;

template<typename T,int... DIM>
using vectorND = aNDAr::multiDimensionalVector<T,DIM...>;
template<typename T,int D1st, int D2nd>
using vector2D = aNDAr::multiDimensionalVector<T,D1st, D2nd>;
template<typename T,int D1st, int D2nd, int D3rd>
using vector3D = aNDAr::multiDimensionalVector<T,D1st, D2nd, D3rd>;
template<typename T,int D1st, int D2nd, int D3rd, int D4th>
using vector4D = aNDAr::multiDimensionalVector<T,D1st, D2nd, D3rd,D4th>;
#endif // INCLUDEGUARD_SHORTNAMES_VECTOR
#endif // INCLUDEGUARD_MULTIDIMENSIONALVECTOR

#ifdef INCLUDEGUARD_INITIALISATIONMETHOD
#ifndef INCLUDEGUARD_SHORTNAMES_INITIALISATIONMETHOD
#define INCLUDEGUARD_SHORTNAMES_INITIALISATIONMETHOD
using setup = aNDAr::initialisationMethod;
using beginWith = aNDAr::initialisationMethod;
#endif // INCLUDEGUARD_SHORTNAMES_INITIALISATIONMETHOD
#endif // INCLUDEGUARD_INITIALISATIONMETHOD
}
} // aNDAr
