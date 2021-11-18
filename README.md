```cpp
   1 #include <iostream>
   2 #include <any>
   3 #include <variant>
   4 #include <type_traits>
   5 
   6 template<class T>struct tag_t{using type=T;};
   7 template<class Tag>using type=typename Tag::Type;
   8 
   9 template<template<class...>class Z, template<class...>class Test, class T>
  10 struct apply_if:
  11   std::conditional_t< Test<T>{}, tag_t<Z<T>>, tag_t<T> >
  12 {};
  13 template<template<class...>class Z, template<class...>class Test, class T>
  14 using apply_if_t = type<apply_if<Z,Test,T>>;
  15 
  16 /*
  17 template <typename RETURNVALUE, typename CLASSTYPE, typename ARGVAL>
  18 using memberPtr = RETURNVALUE (CLASSTYPE::*)(ARGVAL);
  19 
  20 template <typename RETURNVALUE, typename ARGVAL>
  21 using functionPtr = RETURNVALUE (*)(ARGVAL);
  22 */
  23 
  24 template <typename RETURNVALUE, typename ARGVA>
  25 using functionPtrArgs = RETURNVALUE (*)(ARGVA);
  26 
  27 template <typename RETURNVALUE>
  28 using functionPtrVoid = RETURNVALUE (*)();
  29 
  30 //using functionPtr = std::add_pointer<void()>::type;
  31 
  32 // small integer value
  33 using few = unsigned char;
  34 
  35 class cProgress {
  36 	size_t valLastFrame;
  37 	size_t& value;
  38 	//functionPtrVoid<void> job;
  39 	public:
  40 		cProgress(size_t& targetVal, functionPtrVoid<void> ptr);
  41 		bool hasChanged();
  42 };
  43 
  44 // works on continous data with indices up to 255
  45 class cProgressSmall {
  46 	//functionPtrVoid<void> job;
  47 	few& value;
  48 	few valLastFrame;
  49 	public:
  50 		cProgressSmall(few targetVal);
  51 		bool hasChanged();
  52 };
  53 
  54 int main() {
  55 	std::cout << sizeof(functionPtrVoid<void>)  << "\t functionPtrVoid<void>" << std::endl;
  56 	std::cout << sizeof(size_t)  << "\t size_t" << std::endl;
  57 	std::cout << sizeof(unsigned char) << "\t unsigned char" << std::endl;
  58 	std::cout << sizeof(few)  << "\t few" << std::endl;
  59 	std::cout << sizeof(cProgress)  << "\t cProgress " << std::endl;
  60 	std::cout << sizeof(cProgressSmall)  << "\t cProgressSmall " << std::endl;
  61 	
  62 	std::cout << sizeof(std::any)  << "\t any " << std::endl;
  63 	std::cout << sizeof( std::variant<cProgress, cProgressSmall> )  << "\t variant " << std::endl;
  64 }

```

#aNDAr library
## What it is
This is the ‘a N-D Array library’, written in C++. It's purpose is to offer a easy interface to multidimensinal arrays with as little memory overhead as possible.

This is my first public Open Source project and the entire project is a learner's project focusing on understanding variadic parameter packs, fold expessions and compile time programming.

My goal is it to have a array class that


## Motivation
The linear growth of STL N-D Arrays like `std::array< std::array<char,2>, 3>` was the main reason why I wanted to write a nice alternative.


## Design goals
Providing a class that has an easy interface and doesn't requires more runtime memory than a plain C array.

If possible the compiler should calculate whatever possible at compile time.

It should be type-safe.


## Features
Multidimensinal array class for any type. Standard initialisation for char and integer types


## Missing features
Array arithmetics such as addition and multiplication
`std::vector` support


## Build requirements
C++20 compiler, Linux or Windows


## Build instructions and installation


## Tested compiler

## Examples
### Creation
Default (zero for int) initialisation:
```cpp
multiDimensionalArray<int, 2,3> array; // creates a 2×3 row-major array with all elements set to 0.
multiDimensionalArray<int, 2,3> array{};
```
All elements to the same value:
```cpp
multiDimensionalArray<int, 2,3> array{5};
```
Starting from a value (3) and incrementing or add (10) until all elements got a value.
```cpp
multiDimensionalArray<int, 2,3> array{initialisationMethod::increment_ByOne, 3}; // 3 to 8
multiDimensionalArray<int, 2,3> array{initialisationMethod::incrementFrom_By, 3, 10}; // {3, 13}, {23, 33}, {43 and 53}
```
### Access
### Access


## API Reference


## Acknowledgement/Credits
[‘Memory layout of multi-dimensional arrays’](https://eli.thegreenplace.net/2015/memory-layout-of-multi-dimensional-arrays/) by Eli Bendersky on September 26, 2015 at 06:06
