// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

// Offers a struct to keep parameter packs for variadic templates together
// Also contains commonly usable low level functions to interact with such packs
// struc stores IN_VALUES in a static array of int and offers read-only acces via:
// compile time computation: at<>
// compile time or run time: at()
#include "variadicParameterPacks.hpp"
template<int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline const consteval bool VA_pack<IN_VALUES...>::areAllIndicesSmallerThan()
{
    using other = detail::_VA_pack<IN_VALUES_OTHER...>;
    /// using own = numberPack<IN_VALUES...>; // I or DATA
    static_assert(DATA::size==other::size,"Number of arguments are diffrent.");

    for(int i=0; i<DATA::size; ++i)
        if(other::index[i]<0) return false;
        else
			if (DATA::index[i] < other::index[i]) return false;

		return true;
}

template<int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline consteval bool VA_pack<IN_VALUES...>::fitsIn(VA_pack<IN_VALUES_OTHER...> theOtherOne)
{
    static_assert(DATA::size==VA_pack<IN_VALUES_OTHER...>::DATA::size,"Wrong number of values for array.");

    if(DATA::size < VA_pack<IN_VALUES_OTHER...>::DATA::size) return false;

    return areAllIndicesSmallerThan<IN_VALUES_OTHER...>();
}
