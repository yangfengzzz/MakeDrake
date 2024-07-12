#pragma once

#include "pydrake/pydrake_pybind.h"
#include "common/polynomial.h"

DRAKE_PYBIND11_NUMPY_OBJECT_DTYPE(  // NOLINT
    drake::Polynomial<double>)
DRAKE_PYBIND11_NUMPY_OBJECT_DTYPE(  // NOLINT
    drake::Polynomial<drake::AutoDiffXd>)
DRAKE_PYBIND11_NUMPY_OBJECT_DTYPE(  // NOLINT
    drake::Polynomial<drake::symbolic::Expression>)
