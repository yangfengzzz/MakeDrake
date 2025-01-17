#include "pydrake/autodiff_types_pybind.h"
#include "pydrake/pydrake_pybind.h"
#include "math/roll_pitch_yaw.h"
#include "math/rotation_matrix.h"

namespace drake {
namespace pydrake {

PYBIND11_MODULE(autodiffutils_test_util, m) {
  m.doc() = "Utilities for testing Eigen AutoDiff Scalars";

  py::module::import("pydrake.autodiffutils");

  // For testing implicit argument conversion.
  m.def("autodiff_scalar_pass_through",
      [](const AutoDiffXd& value) { return value; });
  m.def("autodiff_vector_pass_through",
      [](const VectorX<AutoDiffXd>& value) { return value; });
  m.def("autodiff_vector3_pass_through",
      [](const Vector3<AutoDiffXd>& value) { return value; });
}

}  // namespace pydrake
}  // namespace drake
