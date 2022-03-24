// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

// Offers a struct to keep parameter packs for variadic templates together
// Also contains commonly usable low level functions to interact with such packs
// struc stores IN_VALUES in a static array of int and offers read-only acces via:
// compile time computation: at<>
// compile time or run time: at()
#include <aNDAr/variadicParameterPacks.hpp>
namespace aNDAr {

template<int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline consteval bool VA_pack<IN_VALUES...>::areAllIndicesSmallerThan()
{
    using OTHER = VA_pack<IN_VALUES_OTHER...>;

    /// using own = numberPack<IN_VALUES...>; // I or data
    static_assert(data::size == OTHER::data::size,"Number of arguments are diffrent.");

    for(int i=0; i < data::size; ++i)
		if (data::index[i] > OTHER::data::index[i]) return false;

	return true;
}


template<int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline constexpr bool VA_pack<IN_VALUES...>::areAllIndicesSmallerThan(VA_pack<IN_VALUES_OTHER...> theOtherOne)
{
    using OTHER = VA_pack<IN_VALUES_OTHER...>;

    /// using own = numberPack<IN_VALUES...>; // I or data
    static_assert(data::size == OTHER::data::size,"Number of arguments are diffrent.");

    for(int i=0; i < data::size; ++i)
		if (data::index[i] > OTHER::data::index[i]) return false;

	return true;
}

template<int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline constexpr bool VA_pack<IN_VALUES...>::canHold(VA_pack<IN_VALUES_OTHER...> theOtherOne)
{
    static_assert(data::size == VA_pack<IN_VALUES_OTHER...>::data::size,"Wrong number of values for array.");

    if(data::size < VA_pack<IN_VALUES_OTHER...>::data::size) return false;

    return areAllIndicesSmallerThan(theOtherOne);
}

template<int... IN_VALUES>
template<int... IN_VALUES_OTHER>
inline consteval bool VA_pack<IN_VALUES...>::canHold()
{
    static_assert(data::size == VA_pack<IN_VALUES_OTHER...>::data::size,"Wrong number of values for array.");

    if(data::size < VA_pack<IN_VALUES_OTHER...>::data::size) return false;

    return areAllIndicesSmallerThan<IN_VALUES_OTHER...>();
}

template<int... IN_VALUES>
template<int... COMPAREVALUES>
inline consteval bool VA_pack<IN_VALUES...>::indexOutOfBoundariesOf() {
	std::common_type_t<decltype(COMPAREVALUES)...> result; // make sure to receive all as same type.
	int idx=-1;

	// for each of COMPAREVALUES: within corresponding indexBoundary?
	return (   (    (std::less<int>()(COMPAREVALUES,(int)data::index[++idx]) == true)
	  		     || (COMPAREVALUES<0) )
			 && ... // to stop even if only one index is out of boundarie
	        );
}
} // aNDAr
