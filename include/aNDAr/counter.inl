// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.
//
// Implements a per-type counter for debbuging purposes
// see multiDimensionalArray.hpp for more information.
#ifndef INCLUDEGUARD_COUNTER_INL
#define INCLUDEGUARD_COUNTER_INL
#include <stddef.h> // size_t
#include <cstddef> // std::size_t (and size_t)
#include <ostream> //std::ostream

namespace aNDAr{
namespace detail {
template <typename T>
    struct counter {
    private:
		static inline int maxValue{0};
    public:
        static constexpr int getMax() {return maxValue;};
        const int value{++maxValue};
        ~counter() {--maxValue;};
        inline constexpr int operator()() const {return value;}
    inline friend std::ostream& operator<<(std::ostream& os, const counter<T>& dt) {
    	os << dt.value;
    	return os;
    }
};
} // namespace detail
} // namespace aNDAr
#endif // INCLUDEGUARD_COUNTER_INL
