// Copyright (C) 2021 Oparilames <oparilames@arcor.de>
// This file is subject to the GNU General Public License v3.0.
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.

#include "array.hpp"

template <typename T, typename... Args>
consteval size_t getMappedIndex(T& Ar_nD, const std::tuple<Args...> &t) {
	size_t tmpIdx = 0;
		//std::cout << "Get mapped index … " << t. << std::endl;
    std::apply([&](const auto &... args) {
        //tmpIdx+=((Ar_nD.getRangeOfDimension(args)), ...);
		///std::cout << "+" << ((int)Ar_nD.indexBoundary[args],...) << std::endl;
		//! tmpIdx+=(Ar_nD.indexBoundary[args],...);
		tmpIdx+=(Ar_nD.dimensionBoundary.index[args],...);
    }, t);
	return tmpIdx;
}
