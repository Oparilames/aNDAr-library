# aNDAr library
## What it is
This is the ‘a N-D Array library’, written in C++. It's purpose is to provide a easy interface to typesafe multidimensinal arrays with as little memory overhead---compared to C-arrays---as possible.


## Motivation
The linear growth in length of nested STL N-D arrays¹ was the main reason why I wanted to write a nice alternative. I also had learning benefits in mind.

___
¹like `std::array< std::array<char,2>, 3>` for a two-dimensional char array.


## Design goals
If possible the compiler should calculate whatever possible at compile time.

It should be type-safe, access to elements beyond an array's boundaries should not be possible.

Plain old C++ data types should be supported by a wide range of constructors.

The code should follow Kate Gregory's philosophy of good names, readability and no need for comments.

## Features
- [x] Multidimensinal array class for any type.
- [ ] Multidimensinal vector class for any type.
-     Standard initialisation for char and integer type types including incremental initialisation from a start value
      - [x] for array
      - [ ] for vector
- [ ] char array initialisation with strings
- [ ] ...

### Naming
The namespace for this library is `aNDAr`. The array class is called `multiDimensionalArray` and the vector class is called `multiDimensionalVector`.
If you don't like long type names, you can either put a `#define __SHORTNAMES_YES` before including anything of this library into your project---or you can use `#include "alternativeNames.inl"`. In this case this needs to get parsed before `multiDimensionalArray.hpp` or `multiDimensionalVector.hpp`
|test|
|===================|
|this|
|out yes|

## Missing features
- Array arithmetics such as addition and multiplication.
- Pure `consteval` conform class.
- Multidimensional runtime class for a alternative to `std::vector`.


## Build requirements
C++20 compiler, Linux or Windows


## Build instructions and installation
You can include the library by simply adding the multiDimensionalArray.cpp to your project and passing it's directory to the compiler and linker.


## Tested compiler

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
In `line 6` we start at -7 and increment until the end of the array. This leads to `'-7', '-5', '-3', '-1', '1', '3', […] until '39'`
`Line 7` does basically the same but it decrements the value. `'-7', '-9', '-11', …` all the way to `'-53'`.
`Line 8` multiplies the values by to each time so we start off with `'-7', '-14', '-28'` and end at `'-58720256'`.
For `line 9` we divide by two (rounded). The first four elements from `<0,0,0>` to `<0,1,0>` are assigned to `'-7', '-3', '-1', '0'` the rest of the values are assigned to 0 too.

The `lines 13---15' initialise the char arrays so that their elements contain the given strings.
The `16th line` starts at the decimal unicode value for `a` and adds so we have the small letter from a to 'x'. 
This also works for other arithmetic types so that the last parameter in `line 6---7` is only needed if you want other values than 1.

### Access
You can access the array data by using the provided functions:
```cpp
multiDimensionalArray<char, 4, 2, 3> array(initialisationMethod::incrementFrom, 'a');
std::cout << array.get<0,0,0>() << "\n";
array<0,0,0>.set('y');
std::cout << array.get<0,0,0>() << "\n";

std::cout << array[array.getMappedIndex<3,1,2>()] << std::endl;
```


## API Reference


## Acknowledgement/Credits
[‘Memory layout of multi-dimensional arrays’](https://eli.thegreenplace.net/2015/memory-layout-of-multi-dimensional-arrays/) by Eli Bendersky on September 26, 2015 at 06:06
[“Naming is Hard: Let's Do Better”, ACCU 2021](https://www.youtube.com/watch?v=ZDluHz-ybPE) by Kate Gregory

[CppCon 2015: Kate Gregory “Stop Teaching C"](https://www.youtube.com/watch?v=YnWhqhNdYyk) by Kate Gregory

[CppCon 2018: Kate Gregory “Simplicity: Not Just For Beginners”](https://www.youtube.com/watch?v=n0Ak6xtVXno) by Kate Gregory from 0:55 m onwards.
