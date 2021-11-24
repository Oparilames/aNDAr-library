// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

// Offers a struct to keep parameter packs for variadic templates together
// Also contains commonly usable low level functions to interact with such packs
// struc stores IN_VALUES in a static array of int and offers read-only acces via:
// compile time computation: at<>
// compile time or run time: at()
#ifndef INCLUDEGUARD_VAPACK
#define INCLUDEGUARD_VAPACK
#include <cstdio> // std::size_t
#include <stdexcept> // std::invalid_argument
#include <type_traits>
#include <ctime>
#include <iostream>

namespace aNDAr {
template<int... IN_VALUES>
struct VA_pack;
namespace detail {
template<int... IN_VALUES>
struct _VA_pack {
	_VA_pack() = delete;
	_VA_pack(const _VA_pack&) = delete;
	_VA_pack(_VA_pack&&) = delete;

	inline static const constexpr auto size{sizeof...(IN_VALUES)};

	inline static const constexpr auto productOfElements{(... * IN_VALUES)};
    inline static const constexpr auto productOfElementsStartWithOne{(... * (1+IN_VALUES))};

	private:
	inline static const constexpr int index[]{IN_VALUES...};

    friend class VA_pack; // in order to access private member
    template<int... IN_VALUES_PACKFUNC>
    template<int... IN_VALUES_OTHER>
    friend inline const consteval bool VA_pack<IN_VALUES_PACKFUNC...>::areAllIndicesSmallerThan();
};
} // detail

template<int... IN_VALUES>
struct VA_pack {
	using I = VA_pack<IN_VALUES...>;
	using DATA = detail::_VA_pack<IN_VALUES...>;
	
	inline const static constexpr int at(int idx);

    template<int IDX>
	inline const static consteval int at();

    // carefully reviewing all functions from here onwards
    inline const static consteval auto getAsTuple();

    inline const consteval auto operator[] (int indexToFind);

	template<int... IN_VALUES_OTHER>
	inline const static consteval bool areAllIndicesSmallerThan();


    template<int... IN_VALUES_OTHER>
    inline consteval bool fitsIn(VA_pack<IN_VALUES_OTHER...> theOtherOne);

    template<int... COMPAREVALUES>
	consteval const bool indexOutOfBoundaries();
};
} // aNDAr
#include "variadicParameterPacks.inl"
static_assert( !std::is_constructible<detail::_VA_pack<0>>::value, "not constructible.");
static_assert( !std::is_default_constructible<detail::_VA_pack<0>>::value, "not default constructible" );
static_assert( !std::is_copy_constructible<detail::_VA_pack<0>>::value, "not copyable" );
static_assert( !std::is_trivially_constructible<detail::_VA_pack<0>>::value, "not trivially constructible");
static_assert( !std::is_move_constructible<detail::_VA_pack<0>>::value, "not move constructible");
#endif // INCLUDEGUARD_VAPACK
