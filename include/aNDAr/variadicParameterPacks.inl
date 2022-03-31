// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.
//
// inline function suggestions for variadicParameterPacks.hpp
// See included file for more details

#include <aNDAr/variadicParameterPacks.hpp>

namespace aNDAr {
template<const int... IN_VALUES>
inline constexpr int VA_pack<IN_VALUES...>::at(int idx) {

    if (idx >= data::size || idx<0) {
        throw std::invalid_argument("Index in parameter pack out of array boundary.");
    }
	return data::index[idx];
}
template<const int... IN_VALUES>
inline constexpr int VA_pack<IN_VALUES...>::at(int idx, int errorReturnValue) {
    if (idx >= data::size || idx<0) return errorReturnValue;
	return data::index[idx];
}

template<const int... IN_VALUES>
template<const int IDX>
inline consteval int VA_pack<IN_VALUES...>::at() {
	static_assert(IDX <= data::size && IDX>=0,"Index out of boundary.");

	return data::index[IDX];
}

template<const int... IN_VALUES>
inline consteval auto VA_pack<IN_VALUES...>::getAsTuple()
{
    return std::tuple{ IN_VALUES...};
}

template<const int... IN_VALUES>
inline consteval auto VA_pack<IN_VALUES...>::operator[] (int indexToFind) {
    return data::index[indexToFind];
}

template <int N, int... INDICES>
consteval const int sumOfExactNIndices() requires(sizeof...(INDICES)==N) {
    return  {(... + INDICES)};
}

template <int... INDICES>
consteval const int sumOfIndices() {
    return  {(... + INDICES)};
}

/// 2022 – looks more complicated than the implementation in variadicParameterPacks.cpp
/**
template<const int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline constexpr bool VA_pack<IN_VALUES...>::areAllIndicesSmallerThan(VA_pack<IN_VALUES_OTHER...> theOtherOne) {
    using otherType = decltype(theOtherOne);
    static_assert(data::size==otherType::data::size,"Number of arguments are diffrent.");
    auto otherTuple = VA_pack<IN_VALUES_OTHER...>::getAsTuple();

    VA_pack<IN_VALUES...> q{};
    bool returnValue{true};
    detail::tupleForLoop<decltype(otherTuple), 0>::call(
        otherTuple,
        [&q,&returnValue](int i, auto& tupleElementValue) {
            if(returnValue==false) return 0;
            if(tupleElementValue <0 || data::index[i] <  tupleElementValue) returnValue=false;
            return 1;
        });
/// / *
///     //Index_AssignForEach<data::size,
///     for(int i=0; i<data::size; ++i)
///         if(theOtherOne[i]<0) return false;
///         else
///               if (data::index[i] < theOtherOne[i]) return false;
/// * /
    return returnValue;
}
**/
/// 2022 – looks more complicated than the implementation in variadicParameterPacks.cpp
/**
template<const int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline consteval bool VA_pack<IN_VALUES...>::areAllIndicesSmallerThan() {
    using otherType = VA_pack<IN_VALUES_OTHER...>;
    static_assert(data::size==otherType::data::size,"Number of arguments are diffrent.");
    auto otherTuple = VA_pack<IN_VALUES_OTHER...>::getAsTuple();

    VA_pack<IN_VALUES...> q{};
    bool returnValue{true};
    detail::tupleForLoop<decltype(otherTuple), 0>::call(
        otherTuple,
        [&q,&returnValue](int i, auto& tupleElementValue) {
            if(returnValue==false) return 0;
            if(tupleElementValue <0 || data::index[i] <  tupleElementValue) returnValue=false;
            return 1;
        });

        return returnValue;
}
**/

template<const int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline constexpr bool VA_pack<IN_VALUES...>::canHold(VA_pack<IN_VALUES_OTHER...> theOtherOne) {
    using other = VA_pack<IN_VALUES_OTHER...>;
    
    static_assert(data::size == other::data::size,"Wrong number of values for array.");

    if(data::size < other::data::size) return false;

    return areAllIndicesSmallerThan(theOtherOne);
}

template<const int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline consteval bool VA_pack<IN_VALUES...>::canHold() {
    using other = VA_pack<IN_VALUES_OTHER...>;
    
    static_assert(data::size == other::data::size,"Wrong number of values for array.");

    if(data::size < other::data::size) return false;

    return areAllIndicesSmallerThan<IN_VALUES_OTHER...>();
}
} // aNDAr
