// Copyright (C) 2021 Oparilames <oparilames@arcor.de>
// This file is subject to the GNU General Public License v3.0.
// Exact license terms can be found in the LICENSE file
// found in the top-level directory of this distribution.
// Commonly usable low level functions regarding variadic packs
#ifndef INCLUDEGUARD_VARIADICPACKS
#define INCLUDEGUARD_VARIADICPACKS
	#include <cstdio> // std::size_t
	#include <concepts> // std::is_fundamental<T> and so on
	#include <stdexcept>
  using few = signed char;


  //TODO: bugfix: doesn't work with floats for some reason
  template<std::integral auto... VALUES >
  struct multiplyTemplateParameterPack {
  	constexpr static const auto value = (... * VALUES);
  };

		template<int... IN_VALUES>
		struct numberPack {
		    template<int... IN_VALUES_OTHER>
            friend class numberPack; // in order to access private member

			inline constexpr static const int size{sizeof...(IN_VALUES)};
private:
				inline constexpr static const int index[size]={IN_VALUES...};
public:
				consteval numberPack(){}
                template<bool=false>
                consteval auto getAsTuple() const {return std::tuple{ IN_VALUES...}; };

				constexpr static const auto productOfElements{(... * IN_VALUES)};
                constexpr static const auto productOfElementsStartWithOne{(... * (1+IN_VALUES))};

                // would be only allowed in immediate functions if consteval instead of constexpr
                constexpr auto operator[] (int indexToFind) const {return at(indexToFind);};

				constexpr const int at(int idx) const {if(idx>=size || idx<0) throw std::invalid_argument("Index in parameter pack out of array boundary."); return index[idx];} // not necessarily needed?

                template<int IDX>
				consteval const int at() const {static_assert(IDX<=size && IDX>=0,"Index out of boundary."); return index[IDX];} // not necessarily needed?

				template<int... IN_VALUES_OTHER>
				consteval bool areAllIndicesSmallerThan() const {
					const numberPack<IN_VALUES_OTHER...> other;
					static_assert(size==other.size,"Number of arguments are diffrent.");
					for(int i=0; i<size; ++i)
                        if(other.index[i]<0) return false;
                        else
						    if (index[i] < other.index[i]) return false;
					return true;
				}
                template<int... IN_VALUES_OTHER>
                consteval bool fitsIn(numberPack<IN_VALUES_OTHER...> theOtherOne) {
                    static_assert(size==theOtherOne.size,"Wrong number of values for array.");
                    if(size > theOtherOne.size) return false;
                    return areAllIndicesSmallerThan<IN_VALUES_OTHER...>();
                }
                /*
				template<int... IN_VALUES_OTHER>
				consteval bool areAllIndicesSmallerThan(numberPack<IN_VALUES_OTHER...> other) {
					//const numberPack<IN_VALUES_OTHER...> other;
					static_assert(size==other.size,"Number of arguments are diffrent.");
					for(int i=0; i<size; ++i)
						if (index[i] < other.index[i]) return false;
					return true;
				}*/

				template<int... COMPAREVALUES>
				consteval const bool indexOutOfBoundaries() {
		  			std::common_type_t<decltype(COMPAREVALUES)...> result; // make sure to receive all as same type.
		  			int idx=-1;
		  			// for each of COMPAREVALUES: within corresponding indexBoundary?

		        return (   (   (std::less<int>()(COMPAREVALUES,(int)index[++idx]) == true)
		  			            || (COMPAREVALUES<0) )
		  					  && ... // to stop even if only one index is out of boundarie
		            );
				}
		};
/*
        		template<std::initializer_list<int> T1, std::initializer_list<int> T2>
                template<int... V2>
        		consteval bool doesNumberPackFitInOther (numberPack<int... V1> firstOne, numberPack<int...V2> secondOne) {
                    if constexpr (!(firstOne.fitsIn(secondOne))) return false;
                    return indexOutOfBoundaries<V2...>();
                }
*/

template <int... firstInts, int... secondInts>
void function(std::tuple<numberPack<firstInts>...> a,
          std::tuple<numberPack<secondInts>...> b)
{
}
#endif // INCLUDEGUARD_VARIADICPACKS
