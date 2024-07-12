#pragma once

#include "pydrake/pydrake_pybind.h"
#include "common/autodiff.h"

DRAKE_PYBIND11_NUMPY_OBJECT_DTYPE(  // NOLINT
    drake::AutoDiffXd)
