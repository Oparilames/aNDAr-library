// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.
//
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
#include <tuple>
#include <iostream>

namespace aNDAr {
template<const int... IN_VALUES>
struct VA_pack {
    constexpr VA_pack()=default;
    inline static constexpr int at(int idx, int errorReturnValue);
    inline static constexpr int at(int idx);

	template<int IDX>
	inline static consteval int at();

	inline static consteval auto getAsTuple();

	inline consteval auto operator[] (int indexToFind);

	template<int... IN_VALUES_OTHER>
	inline static constexpr bool areAllIndicesSmallerThan(VA_pack<IN_VALUES_OTHER...> theOtherOne);
	template<int... IN_VALUES_OTHER>
	inline static consteval bool areAllIndicesSmallerThan();


	template<int... IN_VALUES_OTHER>
	inline static constexpr bool canHold(VA_pack<IN_VALUES_OTHER...> theOtherOne);
	template<int... IN_VALUES_OTHER>
	inline static consteval bool canHold();

	template<int... COMPAREVALUES>
	inline static consteval bool indexOutOfBoundariesOf();


	struct data {
		data() = delete;
		data(const VA_pack::data&) = delete;
		data(VA_pack::data&&) = delete;

		inline static constexpr auto productOfElements{(... * IN_VALUES)};
		inline static constexpr auto productOfElementsStartWithOne{(... * (1+IN_VALUES))};
		inline static constexpr int index[]{IN_VALUES...};
		inline static constexpr auto size{sizeof...(IN_VALUES)};
	};
    ///using DATA = VA_pack<IN_VALUES...>::data;
};
/// Needs to get implemented.
/// for getIndexMappedAs1D(decltype(dimensionBoundariesQuery::getAsTuple()
struct tuple_Pack {
    tuple_Pack()=default;
};
auto createVAPackFromTuple(auto&& tuple) {
	constexpr int iMax = std::tuple_size_v<tuple>;
	int indices[iMax];
	int curIdx = -1;
	std::apply([&curIdx, &indices](auto&&... args) {(( indices[++curIdx]=args), ...);}, tuple);

    for(int i=0; i<iMax; ++i) std::cout << indices[i] << ' ';

    std::cout << std::endl;
	return VA_pack<indices>{};
}

} // aNDAr
#include <aNDAr/variadicParameterPacks.inl>
#endif // INCLUDEGUARD_VAPACK
