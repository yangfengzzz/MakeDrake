#include "pydrake/pydrake_pybind.h"
#include "pydrake/symbolic_types_pybind.h"

namespace drake {

using symbolic::Variable;

namespace pydrake {

PYBIND11_MODULE(odr_test_module, m) {
  m.doc() = "Test ODR using Variable.";

  m.def("new_variable",
      [](const std::string& name) { return new Variable(name); });
}

}  // namespace pydrake
}  // namespace drake
