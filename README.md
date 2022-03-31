# aNDAr library
## What is this?
This is readme for the ‘a N-D Array library’. The library is written in modern C++, has no external dependencies and is intended to provide a simple interface to typesafe multidimensinal arrays with as little memory overhead—compared to C style arrays—as possible.

## Table of content
- [aNDAr library](#andar-library)
  * [What is this?](what-is-this)
  * [Table of content](table-of-content)
  * [Motivation](#motivation)
    + [A solution?](#a-solution)
  * [Design goals](#design-goals)
  * [Features](#features)
    + [Naming](#naming)
  * [Build requirements](#build-requirements)
  * [Build instructions and installation](#build-instructions-and-installation)
  * [Tested compiler](#tested-compiler)
  * [Examples](#examples)
    + [Creation](#creation)
    + [Access](#access)
  * [API Reference](api-reference)
- [Appindex](#appindex)
  * [Acknowledgement/Credits](#acknowledgement/credits)
## Motivation
In the beginning I wanted to write this library for three reasons, each demonstrated in the following lines of code.

Please be aware that this is a snippet and I use `using namespace std` to shorten type names. (Full source code in [`tutorial/compareArraytypes.cpp`](tutorial/compareArraytypes.cpp))
```cpp
  35     // dimension's boundaries
  36     const int N1{2}, N2{4}, N3{3};
  39     const int beyondN1{N1+10}, beyondN2{N2+10}, beyondN3{N3+10};
  40 
  41     // used datatype for this example
  42     using T = int;
  43 
  44     // Arrays instantiations
  45     T array_inC[N1][N2][N3];
  46     array< array< array<T,N1>, N2>, N3> array_STL;
  47 
  55     // Writing values
  56     array_inC[beyondN1][beyondN2][beyondN3] = 99;
  57     array_STL[beyondN1][beyondN2][beyondN3] = 99;
```
We define our array boundaries in line 36 and constants to access indices later on in the line 37. Note: The access indices are clearly beyond the boundaries we dedeclared the line before.

Lines 45 and 46 are supposed to create a 2×3×4 array of integers. Both arrays should have 2 elements, each of those made from 3 elements that store 4 integer values each.

What we do in lines 56 and 57 is to write values to data outside of the arrays' bondaries.

So what _potential_ problems do we have here?

1. The arrays are **neither default initialised nor initialised at all**. Demonstrated in lines 50 and 53 in the source code. Would be diffrent for static or global arrays.
2. The **data** is **diffrently distributed** within the memory occupied by the arrays. Unfortunately `array_STL` is a 4×3×2 array instead of a 2×3×4. 
3. The way of declareing **nested STL container** quickly becomes **rather inconvenient** to work with.
4. We can **write to data outside of array boundary** as we did in lines 56 and 57. This may sometimes be needed, but usually I'd say a programmer wants to neither exceed nor to fall below the index boundary when accessing elements in an array.

Of course, `std::array` ca be used with iterators to mitigate the concern raised in my forth point, but if we have multidimensional arrays of let's say char, we'd waste memory for the pointers for each additional dimension.

### A solution?
The third *issue* was the main reason why I wanted to write a nice alternative. The other reasons came up one by one after I started to work on this project.

Let me show you a version of the code from above featuring bugfixes and a third alternative to create a typesafe and memory-inexpensive array using this library.

The follwing code is just another snippet and can be found in full at [`tutorial/compareArraytypesNew.cpp`](tutorial/compareArraytypesNew.cpp). It uses an additional `using namespace aNDAr` statement.

```cpp
  35     // dimension's boundaries
  36     const int N1{2}, N2{4}, N3{3};
  39     const int beyondN1{N1+10}, beyondN2{N2+10}, beyondN3{N3+10};
  41 
  42     // used datatype for this example
  43     using T = int;
  44 
  45     // Arrays instantiations
  46     T array_C[N1][N2][N3]{0};           array_C;
  47     array< array< array<T,N1>, N2>, N3> array_STL{0};
  48     arrayND<int,N1,N2,N3>               array_aNDAr;
  49 
  62     array_C[beyondN1][beyondN2][beyondN3] = 99;
  63     array_STL[beyondN1][beyondN2][beyondN3] = 99;
  64  // array_aNDAr.set<beyondN1,beyondN2,beyondN3>(99); // won't compile
  65     array_aNDAr.writeDataAtIndex(99,beyondN1,beyondN2,beyondN3);
```

But it comes with costs:

1. The compiler requires time to deal with the heavy use of variadic template packs and stuff like that.
2. A lot of code can technically be inlined, so application size may grow.
3. Mapping multidimensional indices at runtime to their 1D equivalent is not trivial and comes with costs most people would like to avoid.
4. Your time reading the documentation and code


## Design goals
The compiler should calculate whatever possible at compile time.

It should be type-safe, access to elements beyond an array's boundaries should not be possible.

Plain old C++ data types should be supported by a wide range of constructors.

The code should follow Kate Gregory's philosophy of good naming, readability and as little need for comments as possible.

## Features
- Multidimensinal array class for any type.
- Standard initialisation for char and integer type types including incremental initialisation from a start value
  - char container initialisation with strings
- [x] Functions for debug reasons such as print outs, mapping nD-indices to their 1D equivalent.
- [ ] Container arithmetics such as addition and multiplication.
- [ ] Pure compile time computation executed classes.
- [ ] Calculations on GPU.

### Naming
The namespace for this library is `aNDAr`. The main class is called `multiDimensionalArray`.

If you don't like long type names, you can either use `#include "shortNames.inl"` before including anything of this library into your project—or you can put a `#define __SHORTNAMES_ON` at the same position. Choosing the former requires to get parsed before `multiDimensionalArray.hpp` or `multiDimensionalVector.hpp`.
| Contaier Type | class name    | Alternative Names| Specialisation|
| :---            | ---:                          | :---               | :--           |
| nD Array          | multiDimensionalArray | arrayND, arND     |  no           |
|                |   | array2D, ar2D     |  2  dimension
|                | | array3D, ar3D | 3 dimensions
|                |  | array4D, ar4D| 4 dimensions

### Construction
When constructing you have plenty of options, if the ND array you create is a integal datatype (checked with `std::is_arithmetic_v<T>`). 
| initialisationMethod | ::incrementFrom, ::decrementFrom, ::multiplyFromBy, ::divideFromBy |
| :--- | ---:
| setup |
| beginWith |
you can use the `FromBy` and `From` argument followed by one or two arguments to initialise your array in a simple pattern.

## Examples

### Creation
Here are some example calls how to initialise an N-D array:
```cpp
   1 multiDimensionalArray<int, 4, 2, 3> array_L01;
   2 multiDimensionalArray<int, 4, 2, 3> array_L02{};
   3 multiDimensionalArray<int, 4, 2, 3> array_L03(initialisationMethod::typeDefaultTo);
   4 multiDimensionalArray<int, 4, 2, 3> array_L04{initialisationMethod::typeDefaultTo, -7};
   5 multiDimensionalArray<int, 4, 2, 3> array_L05(-7);
   6 multiDimensionalArray<int, 4, 2, 3> array_L06{initialisationMethod::incrementFrom, -7, 2};
   7 multiDimensionalArray<int, 4, 2, 3> array_L07{initialisationMethod::decrementFrom, -7, 2};
   8 multiDimensionalArray<int, 4, 2, 3> array_L08{initialisationMethod::multiplyFromBy, -7, 2};
   9 multiDimensionalArray<int, 4, 2, 3> array_L09{initialisationMethod::divideFromBy, -7, 2};
  10
  11 multiDimensionalArray<char, 4, 2, 3> array_L11{};
  12 multiDimensionalArray<char, 4, 2, 3> array_L12('a');
  13 multiDimensionalArray<char, 4, 2, 3> array_L13({"Greetings, dear readers."});
  14 multiDimensionalArray<char, 4, 2, 3> array_L14(std::string_view("How are you doing today?"));
  15 multiDimensionalArray<char, 4, 2, 3> array_L15{"Keep up the good work :)"};
  16 multiDimensionalArray<char, 4, 2, 3> array_L16(initialisationMethod::incrementFrom, 'a');

```
__Default initialisation:__
```cpp
   1 multiDimensionalArray<int, 4, 2, 3> array_L01;
   2 multiDimensionalArray<int, 4, 2, 3> array_L02{};
   3 multiDimensionalArray<int, 4, 2, 3> array_L03(initialisationMethod::typeDefaultTo);
```
All three ways create a 3D (4×2×3) row-major array with all elements set to the default value of `int`.

If you want to initialise them with a different value here are your options:
```cpp
   4 multiDimensionalArray<int, 4, 2, 3> array_L04{initialisationMethod::typeDefaultTo, -7};
   5 multiDimensionalArray<int, 4, 2, 3> array_L05(-7);
```

__Patternised initialisation:__
If you need to set all array elements to a increasing or decreasing order you can do it like so:
```cpp
   6 multiDimensionalArray<int, 4, 2, 3> array_L06{initialisationMethod::incrementFrom, -7, 2};
   7 multiDimensionalArray<int, 4, 2, 3> array_L07{initialisationMethod::decrementFrom, -7, 2};
   8 multiDimensionalArray<int, 4, 2, 3> array_L08{initialisationMethod::multiplyFromBy, -7, 2};
   9 multiDimensionalArray<int, 4, 2, 3> array_L09{initialisationMethod::divideFromBy, -7, 2};

  13 multiDimensionalArray<char, 4, 2, 3> array_L13({"Greetings, dear readers."});
  14 multiDimensionalArray<char, 4, 2, 3> array_L14(std::string_view("How are you doing today?"));
  15 multiDimensionalArray<char, 4, 2, 3> array_L15{"Keep up the good work :)"};
  16 multiDimensionalArray<char, 4, 2, 3> array_L16(initialisationMethod::incrementFrom, 'a');
```
In `line 6` we start at -7 and increment until the end of the array. This leads to `-7, -5, -3, -1, 1, 3, […]` until `39`.

`Line 7` does basically the same but it decrements the value. `-7, -9, -11, …` all the way to `-53`.

`Line 8` multiplies the values by to each time so we start off with `-7, -14, -28` and end at `-58720256`.

For `line 9` we divide by two (rounded). The first four elements from `<0,0,0>` to `<0,1,0>` are assigned to `-7, -3, -1, 0` the rest of the values are assigned to `0` too.

The `lines 13—15` initialise the char arrays so that their elements contain the given strings.

The `16th line` starts at the decimal unicode value for `a` continues from there on. This yields in the small letter from *a* to *x*.
This also works for other arithmetic types so that the last parameter in `line 6—7` is only needed if you want other values than 1.

### Access
You can access the array data by using the provided functions:
```cpp
multiDimensionalArray<char, 4, 2, 3> array(initialisationMethod::incrementFrom, 'a');
std::cout << array.get<0,0,0>() << "\n";
array<0,0,0>.set('y');
std::cout << array.get<0,0,0>() << "\n";

std::cout << array[array.getMappedIndex<3,1,2>()] << std::endl;
```


## Build requirements
C++20 compiler, Linux or Windows


## Build instructions and installation
You can include the library by simply adding the multiDimensionalArray.cpp to your project and passing it's directory to the compiler and linker.


## Tested compiler
g++ (GCC) 11.2.0


## API Reference


# Appindex
## Acknowledgement/Credits
[‘Memory layout of multi-dimensional arrays’](https://eli.thegreenplace.net/2015/memory-layout-of-multi-dimensional-arrays/) by Eli Bendersky on September 26, 2015 at 06:06
[“Naming is Hard: Let's Do Better”, ACCU 2021](https://www.youtube.com/watch?v=ZDluHz-ybPE) by Kate Gregory

[CppCon 2015: Kate Gregory “Stop Teaching C"](https://www.youtube.com/watch?v=YnWhqhNdYyk) by Kate Gregory

[CppCon 2018: Kate Gregory “Simplicity: Not Just For Beginners”](https://www.youtube.com/watch?v=n0Ak6xtVXno) by Kate Gregory from 0:55 m onwards.
