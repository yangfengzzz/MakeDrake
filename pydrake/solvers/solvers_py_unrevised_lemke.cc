#include "pydrake/common/value_pybind.h"
#include "pydrake/documentation_pybind.h"
#include "pydrake/pydrake_pybind.h"
#include "pydrake/solvers/solvers_py.h"
#include "solvers/unrevised_lemke_solver.h"

namespace drake {
namespace pydrake {
namespace internal {
void DefineSolversUnrevisedLemke(py::module m) {
  // NOLINTNEXTLINE(build/namespaces): Emulate placement in namespace.
  using namespace drake::solvers;
  constexpr auto& doc = pydrake_doc.drake.solvers;
  py::class_<UnrevisedLemkeSolver<double>, SolverInterface>(
      m, "UnrevisedLemkeSolver", doc.UnrevisedLemkeSolver.doc)
      .def(py::init<>(), doc.UnrevisedLemkeSolver.ctor.doc)
      .def_static("id", &UnrevisedLemkeSolver<double>::id,
          doc.UnrevisedLemkeSolver.id.doc);
}
}  // namespace internal
}  // namespace pydrake
}  // namespace drake
