// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

#include <aNDAr/obsolte_arrayacces.hpp>

template <typename T, typename... Args>
[[deprecated("Use member variable of multiDimensionalArray instead.")]]
consteval size_t getMappedIndex(T& Ar_nD, const std::tuple<Args...> &t) {
	size_t tmpIdx = 0;
    std::apply([&](const auto &... args) {
		tmpIdx+=(Ar_nD.dimensionBoundary.index[args],...);
    }, t);
	return tmpIdx;
}
