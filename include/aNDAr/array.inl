
#ifndef INCLUDEGUARD_ARRAY_INL
#define INCLUDEGUARD_ARRAY_INL
#include <aNDAr/array.hpp>

#ifdef __DEBUG_ON
#include <cwctype> // std::wctrans; /usr/local/include/c++/11.2.0/iostream
#include <iostream>
#endif

namespace aNDAr::detail {

template<typename T, int size>
constexpr array<T,size>::Iterator array<T,size>::begin() {
    return Iterator(&data[0]);
}

template<typename T, int size>
constexpr array<T,size>::Iterator array<T,size>::end() {
    return Iterator(&data[size]);
}

template<typename T, int size>
constexpr array<T,size>::Iterator array<T,size>::beforeEnd(const int howMany) {
    return Iterator(&data[size-howMany]);

}

template<typename T, int size>
template <std::size_t ... PackTrick>
constexpr array<T,size>::array(T const& value, std::index_sequence<PackTrick...>)
    : data{(static_cast<void>(PackTrick), value)...}
{

}


template<typename T, int size>
constexpr array<T,size>::array()
    : array(T{}, std::make_index_sequence<size>{})
{

};
template<typename T, int size>
constexpr array<T,size>::array(T&& value)
    : array(std::forward<decltype(value)>(value), std::make_index_sequence<size>{}) {
}

template<typename T, int size>
inline constexpr T&  array<T,size>::operator[](int idx) {
    // static_assert(asConstexprNew(idx)<size, "Wrong size");
    return data[idx];
};

template<typename T, int size>
inline constexpr const T&  array<T,size>::operator[](int idx) const {
    // static_assert(asConstexprNew(idx)<size, "Wrong size");
    return data[idx];
};


template<typename T, typename T_array>
constexpr T_array uniformInitialisedTo(T&& uniformInitValue) {
    return T_array{std::forward<T>(uniformInitValue)};
}
} // aNDAr::detail

#endif // INCLUDEGUARD_ARRAY_INL
