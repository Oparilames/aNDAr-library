```javascript {.line-numbers}
function add(x, y) {
  return x + y;
}
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
