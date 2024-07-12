#include "pydrake/pydrake_pybind.h"
#include "pydrake/systems/framework_py_semantics.h"
#include "pydrake/systems/framework_py_systems.h"
#include "pydrake/systems/framework_py_values.h"

namespace drake {
namespace pydrake {

PYBIND11_MODULE(framework, m) {
  PYDRAKE_PREVENT_PYTHON3_MODULE_REIMPORT(m);
  m.doc() = "Bindings for the core Systems framework.";

  // Import autodiff and symbolic modules so that their types are declared for
  // use as template parameters.
  py::module::import("pydrake.autodiffutils");
  py::module::import("pydrake.symbolic");

  // Incorporate definitions as pieces (to speed up compilation).
  DefineFrameworkPyValues(m);
  DefineFrameworkPySemantics(m);
  DefineFrameworkPySystems(m);
}

}  // namespace pydrake
}  // namespace drake
