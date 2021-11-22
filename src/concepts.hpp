// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.

// Offers several concepts and type_trait magic
#ifndef INCLUDEGUARD_CONCEPTS
#define INCLUDEGUARD_CONCEPTS
#include <type_traits>
#include <ostream>
template<typename T, typename ... U>
concept anyOfType = (std::same_as<T, U> || ...);


template<bool ... T>
inline constexpr bool allTruthIn ( ){return (... && T);};

template<bool ... T>
inline constexpr bool anyTruthIn ( ){return (... || T);};

// needed for initialisation arithmetic for arrays/vectors
template<typename T, typename = void>
struct hasIncrementOperator: std::false_type {};
template<typename T, typename = void>
struct hasDecrementOperator: std::false_type {};


// some types may not be arithmetic or integral but still support addition, subtraction,
// multiplication and division
template<typename T>
struct hasIncrementOperator<T, std::void_t<  decltype( std::declval<T&>()++ )  > >
 : std::true_type {};

 template<typename T>
 struct hasDecrementOperator<T, std::void_t<  decltype( std::declval<T&>()-- )  > >
  : std::true_type {};

template<class T>
    inline constexpr bool hasIncrementOperator_v = hasIncrementOperator<std::ostream,T>::value;
template<class T>
    inline constexpr bool hasDecrementOperator_v = hasDecrementOperator<std::ostream,T>::value;


// TODO: declutter and write for divide operator too
template<class SELF, class OTHER=SELF, class = void>
struct isMultiplyAssignableTo : std::false_type {};

template<class T, class = void>
struct hasIntegralMultiplyAssignmentOperator : std::false_type {};

template<class SELF, class OTHER>
struct isMultiplyAssignableTo
<SELF, OTHER,
    decltype(
        void(
            std::declval<SELF&>() *= std::declval<OTHER>()
        )
    )
> : std::true_type {};

template<class T>
inline constexpr bool hasMultiPlayOperator_self_v = isMultiplyAssignableTo<T>::value;
// types taken from __is_integral_helper in type_traits (/usr/include/c++/11/type_traits) delivered by g++

template<class T>
inline constexpr bool hasMultiPlayOperator_basicIntegral_v =
    anyTruthIn<
        isMultiplyAssignableTo<T,bool>::value,
        isMultiplyAssignableTo<T,char>::value,
        isMultiplyAssignableTo<T,signed char>::value,
        isMultiplyAssignableTo<T,unsigned char>::value,
        isMultiplyAssignableTo<T,char16_t>::value,
        isMultiplyAssignableTo<T,char32_t>::value,
        isMultiplyAssignableTo<T,short>::value,
        isMultiplyAssignableTo<T,unsigned short>::value,
        isMultiplyAssignableTo<T,int>::value,
        isMultiplyAssignableTo<T,unsigned int>::value,
        isMultiplyAssignableTo<T,long>::value,
        isMultiplyAssignableTo<T,unsigned long>::value,
        isMultiplyAssignableTo<T,long long>::value,
        isMultiplyAssignableTo<T,unsigned long long>::value
    >();

template<class T>
inline consteval bool hasMultiplyOperatorForIntegral_orSpecialCases(){
    bool evaluated=hasMultiPlayOperator_basicIntegral_v<T>;
    #ifdef __WCHAR_TYPE__
        evaluated += isMultiplyAssignableTo<T,wchar_t>::value;
    #endif
    #ifdef _GLIBCXX_USE_CHAR8_T
        evaluated+=isMultiplyAssignableTo<T,char8_t>::value;
    #endif
    #if defined(__GLIBCXX_TYPE_INT_N_0)
        evaluated+=anyTruthIn< isMultiplyAssignableTo<T,__GLIBCXX_TYPE_INT_N_0>::value, isMultiplyAssignableTo<T,unsigned __GLIBCXX_TYPE_INT_N_0>::value>::value;
    #endif
    #if defined(__GLIBCXX_TYPE_INT_N_1)
        evaluated+=anyTruthIn< isMultiplyAssignableTo<T,__GLIBCXX_TYPE_INT_N_1>::value, isMultiplyAssignableTo<T,unsigned __GLIBCXX_TYPE_INT_N_1>::value>::value;
    #endif
    #if defined(__GLIBCXX_TYPE_INT_N_2)
        evaluated+=anyTruthIn< isMultiplyAssignableTo<T,__GLIBCXX_TYPE_INT_N_2>::value, isMultiplyAssignableTo<T,unsigned __GLIBCXX_TYPE_INT_N_2>::value>::value;
    #endif
    #if defined(__GLIBCXX_TYPE_INT_N_3)
        evaluated+=anyTruthIn< isMultiplyAssignableTo<T,__GLIBCXX_TYPE_INT_N_3>::value, isMultiplyAssignableTo<T,unsigned __GLIBCXX_TYPE_INT_N_3>::value>::value;
    #endif
    return evaluated;
}

template<class T>
inline constexpr bool hasMultiPlayOperator_integral_v = hasMultiplyOperatorForIntegral_orSpecialCases<T>();

template<class T>
inline constexpr bool hasMultiPlayOperator_v = hasMultiPlayOperator_self_v<T>*hasMultiPlayOperator_integral_v<T>;

// Output operator into osstream available?
// from https://quuxplusone.github.io/blog/2018/09/08/problems-concepts-should-solve/
// and https://stackoverflow.com/a/49026811
template<typename S, typename T, typename = void>
struct is_to_stream_writable: std::false_type {};

template<typename S, typename T>
struct is_to_stream_writable<S, T,
        std::void_t<  decltype( std::declval<S&>()<<std::declval<T>() )  > >
  : std::true_type {};

template<class T>
inline constexpr bool canPrintedByConsole_v = is_to_stream_writable<std::ostream,T>::value;


// If we want to print something to the console that is more complicated.
// should be used in pushInfoToStream_ functions and alike.
// TODO: Check and replace
template<typename T>
  requires (!canPrintedByConsole_v<T> && std::is_convertible_v<T,int>)
constexpr inline int transformToPrintable(T& value) {
  return static_cast<int>(value);
}

template<typename T>
  requires (canPrintedByConsole_v<T> && !std::is_convertible_v<T,int>)
constexpr inline T& transformToPrintable(T& value) {
  return value;
}
#endif // INCLUDEGUARD_CONCEPTS
