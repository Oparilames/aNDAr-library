// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.
//
// Offers several concepts and type_trait magic
#ifndef INCLUDEGUARD_CONCEPTS
#define INCLUDEGUARD_CONCEPTS
#include <type_traits>
#include <ostream>
#include <iterator>
template<typename T, typename ... U>
concept anyOfType = (std::same_as<T, U> || ...);


template<bool ... T>
inline constexpr bool allTruthIn ( ){return (... && T);};

template<bool ... T>
inline constexpr bool anyTruthIn ( ){return (... || T);};

// needed for initialisation arithmetic for arrays/vectors
// ++, -- operators et cetera.
enum class preOrPost{neither, post, pre, both};
template< class, class = void >
struct hasPreIncrementOperator : std::false_type { };
template< class, class = void >
struct hasPostIncrementOperator : std::false_type { };
template< class, class = void >
struct hasPreDecrementOperator : std::false_type { };
template< class, class = void >
struct hasPostDecrementOperator : std::false_type { };


// some types may not be arithmetic or integral but still support addition, subtraction,
// multiplication and division

template< class T >
struct hasPreIncrementOperator<T,
           std::void_t<decltype( ++std::declval<T&>() )>
       > : std::true_type { };
template< class T >
struct hasPostIncrementOperator<T,
           std::void_t<decltype( std::declval<T&>()++ )>
       > : std::true_type { };

template< class T >
struct hasPreDecrementOperator<T,
           std::void_t<decltype( --std::declval<T&>() )>
       > : std::true_type { };
template< class T >
struct hasPostDecrementOperator<T,
           std::void_t<decltype( std::declval<T&>()-- )>
       > : std::true_type { };

template<class T>
    inline constexpr bool hasIncrementOperator_v = (hasPostIncrementOperator<T>::value || hasPreIncrementOperator<T>::value);
template<class T>
    inline constexpr bool hasDecrementOperator_v = (hasPostDecrementOperator<T>::value || hasPreDecrementOperator<T>::value);
    
template<class T>
    inline constexpr preOrPost isIncrementOperatorType = []{
        if(!hasIncrementOperator_v<T>) return preOrPost::neither;

        if (hasPostIncrementOperator<T>::value && !hasPreIncrementOperator<T>::value) return preOrPost::post;
        else if (!hasPostIncrementOperator<T>::value && hasPreIncrementOperator<T>::value)  return preOrPost::pre;
        else return preOrPost::both;}();
        
template<class T>
    inline constexpr preOrPost isDecrementOperatorType = []{
        if(!hasDecrementOperator_v<T>) return preOrPost::neither;

        if (hasPostDecrementOperator<T>::value && !hasPreDecrementOperator<T>::value) return preOrPost::post;
        else if (!hasPostDecrementOperator<T>::value && hasPreDecrementOperator<T>::value)  return preOrPost::pre;
        else return preOrPost::both;}();
        
    
    

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
inline constexpr bool hasMultiplyOperator_self_v = isMultiplyAssignableTo<T>::value;
// types taken from __is_integral_helper in type_traits (/usr/include/c++/11/type_traits) delivered by g++

template<class T>
inline constexpr bool hasMultiplyOperator_basicIntegral_v =
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
    bool evaluated=hasMultiplyOperator_basicIntegral_v<T>;
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
inline constexpr bool hasMultiplyOperator_integral_v = hasMultiplyOperatorForIntegral_orSpecialCases<T>();

template<class T>
inline constexpr bool hasMultiplyOperator_v = hasMultiplyOperator_self_v<T>+hasMultiplyOperator_integral_v<T>;

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



template <typename T, typename = void>
struct is_iterable : std::false_type {};
template <typename T>
struct is_iterable<T, std::void_t<
                              decltype(std::declval<T>().begin()),
                                decltype(std::declval<T>().end())>>
  : std::true_type {};

template<typename T, typename = void>
struct hasRandoomAccessIterator: std::false_type {};

template<typename T>
requires (std::random_access_iterator<typename T::iterator>
  || std::derived_from<typename T::Iterator::iterator_category, std::random_access_iterator_tag>

  || std::random_access_iterator<typename T::Iterator>
  || std::derived_from<typename T::iterator::iterator_category, std::random_access_iterator_tag>)
struct hasRandoomAccessIterator<T,
        std::void_t<  void  > >
  : std::true_type {};

template<typename T>
//requires (hasRandoomAccessIterator<T>::value)
concept withRandomAccessIterator = (hasRandoomAccessIterator<T>::value);

/*
template<class T>
inline constexpr bool hasIterator_v =  checkForRandomAccessIterator<T>() ;//is_iterable<T>::value;
*/
template<class T>
inline constexpr bool hasRandoomAccessIterator_v =  hasRandoomAccessIterator<T>::value ;//is_iterable<T>::value;

/*
template<typename T>
std::is_same_v<std::iterator_traits<T>::value_type ,T>
*/
#endif // INCLUDEGUARD_CONCEPTS
