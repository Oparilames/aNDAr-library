// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.

// 1D array class with at least 2 elements
#ifndef INCLUDEGUARD_ARRAY
#define INCLUDEGUARD_ARRAY
#ifdef __DEBUG_ON
    //#include "counter.cpp"
#endif // __DEBUG_ON
#include <cstring>          // std::memcpy
#include <initializer_list> // std::initializer_list
#include <utility>          // std::index_sequence
#include <iterator> // std::contiguous_iterator_tag usw.
namespace aNDAr::detail {
template<typename T, int size>
struct array {
    static_assert(size >= 2, "Can't create array with boundary size smaller than 2");
    T data[size];
private:
    template <std::size_t ... PackTrick>
    constexpr array(T const& value, std::index_sequence<PackTrick...>);
public:
    constexpr array();
    constexpr array(T&& value);

    constexpr array(const array<T,size>& other) = default;
    constexpr array& operator=(const array<T,size>& other)=default;

    struct Iterator;
    constexpr Iterator begin();
    constexpr Iterator end();
    constexpr Iterator beforeEnd(const int howMany);

    constexpr T& operator[](int idx);
    constexpr const T& operator[](int idx) const; // needed with this signature?


    // from https://internalpointers.com/post/writing-custom-iterators-modern-cpp
    // TODO: use concepts rather than tags
    struct Iterator
    {
        using iterator_category = std::contiguous_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;  // or also value_type*
        using reference         = T&;  // or also value_type&

        constexpr Iterator(pointer ptr) : dataPointer(ptr) {}

        constexpr reference operator*() const { return *dataPointer; }
        constexpr pointer operator->() { return dataPointer; }

        // Prefix increment
        constexpr Iterator& operator++() { dataPointer++; return *this; }

        // Postfix increment
        constexpr Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        friend constexpr bool operator== (const Iterator& a, const Iterator& b) { return a.dataPointer == b.dataPointer; };
        friend constexpr bool operator!= (const Iterator& a, const Iterator& b) { return a.dataPointer != b.dataPointer; };

    private:
        pointer dataPointer;
    };
};

template<typename T, typename T_array>
static constexpr T_array uniformInitialisedTo(T&& uniformInitValue);
} // aNDAr::detail
#include <aNDAr/array.inl>
#endif // INCLUDEGUARD_ARRAY
