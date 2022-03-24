// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.
//
// Usable constants to deal with diffrent artithmetical
// initialisations for N-Dimensional array/vector types
#include <aNDAr/concepts.hpp>
#ifndef INCLUDEGUARD_INITIALISATIONMETHOD
#define INCLUDEGUARD_INITIALISATIONMETHOD
namespace aNDAr{
enum class initialisationMethod {
  incrementFrom=0,
  decrementFrom,

  multiplyFromBy,
  divideFromBy
};
template<typename T>
concept setupBy = (std::is_nothrow_convertible_v<std::remove_cvref_t<T>,initialisationMethod> && !std::same_as<std::remove_cvref_t<T>,initialisationMethod>);
template<typename T>
concept setupByWider = (std::is_nothrow_convertible_v<std::remove_cvref_t<T>,initialisationMethod> || std::same_as<std::remove_cvref_t<T>,initialisationMethod>);

namespace detail {
namespace debug
{
  constexpr static inline const std::string_view initMethodName[]{
      "initialisationMethod::incrementFrom",
      "initialisationMethod::decrementFrom",

      "initialisationMethod::multiplyFromBy",
      "initialisationMethod::divideFromBy"
  };
    constexpr static inline const std::string_view initMethodName_brief[]{
        "by::incrementFrom",
        "by::decrementFrom",

        "by::multiplyFromBy",
        "by::divideFromBy"
    };
}; // debug

template<initialisationMethod DI>
using iM_constant = std::integral_constant<initialisationMethod, DI>;

typedef iM_constant<initialisationMethod::incrementFrom>  iM_constant_incrementFrom;
typedef iM_constant<initialisationMethod::decrementFrom>  iM_constant_decrementFrom;
typedef iM_constant<initialisationMethod::multiplyFromBy> iM_constant_multiplyFromBy;
typedef iM_constant<initialisationMethod::divideFromBy>   iM_constant_divideFromBy;

consteval initialisationMethod undo_SetupBy(setupByWider auto&& toFind) {
    using T = std::remove_cvref_t<decltype(toFind)>;
    if (std::same_as<initialisationMethod,T>) return toFind;
    else return static_cast<initialisationMethod>(toFind);// toFind();
}
constexpr bool compareInitMethod(setupByWider auto&& compare, initialisationMethod with) {
    return (undo_SetupBy(compare) == with);
}

constexpr std::string_view initMethodTitle(setupByWider auto toFind,int shorter=false) {
    if (shorter!=false)  return debug::initMethodName_brief[static_cast<int>(static_cast<initialisationMethod>(toFind))];
    return debug::initMethodName[static_cast<int>(static_cast<initialisationMethod>(toFind))];
}

} // detail
template<typename T>
concept setupNoMultiplicationOrDivision = ((std::is_nothrow_convertible_v<T,initialisationMethod> || std::same_as<T,initialisationMethod>) && !anyOfType<T, long/*decltype(multiplyFromBy),decltype(divideFromBy),initialisationMethod_multiplyFromBy, initialisationMethod_divideFromBy*/ > );

}; // aNDAr
#endif // INCLUDEGUARD_INITIALISATIONMETHOD
