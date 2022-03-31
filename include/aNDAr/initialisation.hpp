// Copyright (c) 2021 Oparilames under MIT License
// Exact license terms can be found in the LICENSE file
// found in the root-level directory of this distribution.
//
// Usable constants to deal with diffrent artithmetical
// initialisations for N-Dimensional array/vector types
#include <aNDAr/initialisation.inl>

namespace aNDAr{
static constexpr auto initialiseByIncrementFrom{initialisationMethod::incrementFrom};
static constexpr auto initialiseByDecrementFrom{initialisationMethod::decrementFrom};
static constexpr auto initialiseByMultiplyFromBy{initialisationMethod::multiplyFromBy};
static constexpr auto initialiseByDivideFromBy{initialisationMethod::divideFromBy};

static constexpr detail::iM_constant_incrementFrom incrementFrom;
static constexpr detail::iM_constant_decrementFrom decrementFrom;
static constexpr detail::iM_constant_multiplyFromBy multiplyFromBy;
static constexpr detail::iM_constant_divideFromBy divideFromBy;
#undef diMc
}; // aNDAr
