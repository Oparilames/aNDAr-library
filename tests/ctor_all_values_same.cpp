// https://godbolt.org/z/4xTTav7Ko
#include <cstdio> // std::size_t
#include <stdexcept> // std::invalid_argument
#include <iostream>
#include <tuple> // for tuple
#define ALLOW_COMPILER_ERROR true


constexpr char* readme{"The following program is my attempt \
to initalise a c-style integer array \
with non-type variadic template arguments.\
\
My problem is that I won't be able to create a tuple from a numberSequence." };
#include <iostream>
#include <array>
#include <utility>

// A template struct to receive 'amount' times the value 'value'.
template <int amount, int value>
struct numberSequence {
    static constexpr int val=numberSequence<amount-1, value>::val;
};

template<int value>
struct numberSequence<0,value> {
        static constexpr int val=value;
};
namespace detail {
// primitive, quick and dirty tag dispatching to differentiate one path to receive a STL array and the other to receice a c-style array.
struct tag_A{};
struct tag_B{};

// Two variants to return array data types from a numberSequence.
// This one works
template<const int value, size_t ... amount>
consteval auto nTimesNumbersOf_impl(tag_A notUsed, std::index_sequence<amount...>)
{
	return std::array<int, sizeof...(amount)>
		{ numberSequence<amount,value>::val... };
}

// This one doesn't
template<const int value, size_t ... amount>
consteval auto nTimesNumbersOf_impl(tag_B notUsed, std::index_sequence<amount...> notUsed2)
{
    constexpr int size{sizeof...(amount)};

    // Gives 1 error: too many initializers for 'std::tuple<int, int, int>'
    //return std::tuple<decltype(static_cast<int>(amount))...>{numberSequence<amount,value>::val...};
    // Gives 2 errors:
    // 1. class template argument deduction failed
    // 2. no matching function for call to 'tuple(const int&, const int&, const int&)'

    constexpr auto factorial = [](int n) {
        constexpr auto fact_impl = [](int n, const auto& impl) -> int {
            return n > 1 ? n * impl(n - 1, impl) : 1;
        };
        return fact_impl(n, fact_impl);
    };

    int tmpAr[size]{ (int (amount),...)};

/*
    for(int i=0; i<size;++i)
    //int cntr=-1;
    (void(tmpAr[i]=numberSequence<amount,value>::val), ...);
*/
    return *tmpAr;
    //return std::tuple{numberSequence<size,value>::val...};
}
} // detail

// API/call function
template<const int amount, const int value>
consteval auto nTimesNumbersOf()
{
    using namespace detail;
    if constexpr(!ALLOW_COMPILER_ERROR)
	return nTimesNumbersOf_impl<value>(tag_A{}, std::make_index_sequence<amount>());
    else
	return nTimesNumbersOf_impl<value>(tag_B{}, std::make_index_sequence<amount>());
}

#define recusriveSetValue(x,amount) nTimesNumbersOf_impl<value>(tag_B{}, std::make_index_sequence<amount>())
void test_autoInit_viatupleOrSTLarray() {
    auto ar=nTimesNumbersOf<3,15>();

    std::cout << typeid(decltype(ar)).name() << std::endl;
}
// https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/



template<const int amount, const int value>
void test_tryToInitcArray_viaTupleOrSTLarray() {
    using namespace detail;
    constexpr int peter[amount]{nTimesNumbersOf_impl<value>(tag_B{}, std::make_index_sequence<amount>())};
    std::cout << "Content: ";
    for(auto c:peter)
    std::cout << c << ' ';
    std::cout << "\n" << std::endl;
}

int main() {
    test_autoInit_viatupleOrSTLarray();
    test_tryToInitcArray_viaTupleOrSTLarray<3,15>();
}
