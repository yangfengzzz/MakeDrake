#include "pydrake/documentation_pybind.h"
#include "pydrake/pydrake_pybind.h"
#include "pydrake/solvers/solvers_py.h"
#include "solvers/sdpa_free_format.h"

namespace drake {
namespace pydrake {
namespace internal {

void DefineSolversSdpaFreeFormat(py::module m) {
  // NOLINTNEXTLINE(build/namespaces): Emulate placement in namespace.
  using namespace drake::solvers;
  constexpr auto& doc = pydrake_doc.drake.solvers;

  py::enum_<RemoveFreeVariableMethod>(
      m, "RemoveFreeVariableMethod", doc.RemoveFreeVariableMethod.doc)
      .value("kNullspace", RemoveFreeVariableMethod::kNullspace,
          doc.RemoveFreeVariableMethod.kNullspace.doc)
      .value("kTwoSlackVariables", RemoveFreeVariableMethod::kTwoSlackVariables,
          doc.RemoveFreeVariableMethod.kTwoSlackVariables.doc)
      .value("kLorentzConeSlack", RemoveFreeVariableMethod::kLorentzConeSlack,
          doc.RemoveFreeVariableMethod.kLorentzConeSlack.doc);

  m.def("GenerateSDPA", &solvers::GenerateSDPA, py::arg("prog"),
      py::arg("file_name"),
      py::arg("method") = RemoveFreeVariableMethod::kNullspace,
      doc.GenerateSDPA.doc);
}

}  // namespace internal
}  // namespace pydrake
}  // namespace drake
