#pragma once

// Internal use only. Users should not include this header file directly.
// Instead, they should say `#include "common/symbolic/expression.h"`.

// Many symbolic types are not closed under their defined operations, e.g.,
// relational operations (i.e., ``<``) over Expression produce a Formula.
// To ensure that this library's definitions are always consistent, we use
// this header to define the API as a single, consistent component. This
// macro provides a fail-fast that the all.h order is always obeyed.
#define DRAKE_COMMON_SYMBOLIC_EXPRESSION_ALL

// Do not alpha-sort the following block of hard-coded #includes, which is
// protected by `clang-format on/off`.
//
// This particular order ensures that everyone sees the order that respects the
// inter-dependencies of the symbolic headers. This shields us from triggering
// undefined behaviors due to varying the order of template specializations.
//
// clang-format off
#include "common/symbolic/expression/variable.h"
#include "common/symbolic/expression/variables.h"
#include "common/symbolic/expression/environment.h"
#include "common/symbolic/expression/expression_kind.h"
#include "common/symbolic/expression/boxed_cell.h"
#include "common/symbolic/expression/expression.h"
#include "common/symbolic/expression/expression_visitor.h"
#include "common/symbolic/expression/ldlt.h"
#include "common/symbolic/expression/formula.h"
#include "common/symbolic/expression/formula_visitor.h"
// clang-format on

#undef DRAKE_COMMON_SYMBOLIC_EXPRESSION_ALL
