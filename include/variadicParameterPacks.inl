// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

// Offers a struct to keep parameter packs for variadic templates together
// Also contains commonly usable low level functions to interact with such packs
// struc stores IN_VALUES in a static array of int and offers read-only acces via:
// compile time computation: at<>
// compile time or run time: at()

#include "variadicParameterPacks.hpp"

namespace aNDAr {
	
template<int... IN_VALUES>
inline const constexpr int VA_pack<IN_VALUES...>::at(int idx) {

    if (idx >= DATA::size || idx<0) {
        throw std::invalid_argument("Index in parameter pack out of array boundary.");
    }
	return DATA::index[idx];
}

template<int... IN_VALUES>
template<int IDX>
inline const consteval int VA_pack<IN_VALUES...>::at() {
	static_assert(IDX<=DATA::size && IDX>=0,"Index out of boundary.");

	return DATA::index[IDX];
}

template<int... IN_VALUES>
inline const consteval auto VA_pack<IN_VALUES...>::getAsTuple()
{
    return std::tuple{ IN_VALUES...};
}

template<int... IN_VALUES>
inline const consteval auto VA_pack<IN_VALUES...>::operator[] (int indexToFind) {
    return DATA::index[indexToFind];
}
} // aNDAr