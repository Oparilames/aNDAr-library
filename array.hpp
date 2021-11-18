// Copyright (C) 2021 Oparilames <oparilames@arcor.de>
// This file is subject to the GNU General Public License v3.0.
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.

#ifndef INCLUDEGUARD_ARRAY
#define INCLUDEGUARD_ARRAY
#include <stddef.h> // size_t
#include <cstddef> // std::size_t (and size_t)
#include <tuple> // std::tuple
#include <ostream> //std::ostream

template <typename T>
    struct counter {
    private:
		static inline int maxValue{0};
    public:
        constexpr int getMax() const {return maxValue;};
        const int value{++maxValue};
        ~counter() {--maxValue;};
    inline friend std::ostream& operator<<(std::ostream& os, const counter<T>& dt) {
    	os << dt.value;
    	return os;
    }
};


template <typename T, typename... Args>
consteval size_t getMappedIndex(T& Ar_nD, const std::tuple<Args...> &t);

#endif // INCLUDEGUARD_ARRAY
