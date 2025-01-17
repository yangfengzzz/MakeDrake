#include "pydrake/documentation_pybind.h"
#include "pydrake/pydrake_pybind.h"
#include "pydrake/solvers/solvers_py.h"
#include "pydrake/symbolic_types_pybind.h"
#include "solvers/mixed_integer_optimization_util.h"

namespace drake {
namespace pydrake {
namespace internal {

void DefineSolversMixedIntegerOptimizationUtil(py::module m) {
  // NOLINTNEXTLINE(build/namespaces): Emulate placement in namespace.
  using namespace drake::solvers;
  constexpr auto& doc = pydrake_doc.drake.solvers;

  m.def(
      "AddLogarithmicSos2Constraint",
      [](MathematicalProgram* prog,
          const VectorX<symbolic::Expression>& lambdas,
          const std::string& binary_variable_name) {
        return AddLogarithmicSos2Constraint(
            prog, lambdas, binary_variable_name);
      },
      py::arg("prog"), py::arg("lambdas"),
      py::arg("binary_variable_name") = "y",
      doc.AddLogarithmicSos2Constraint.doc_3args_prog_lambda_y);

  m.def("AddSos2Constraint", &AddSos2Constraint, py::arg("prog"),
      py::arg("lambdas"), py::arg("y"), doc.AddSos2Constraint.doc);

  m.def(
      "AddLogarithmicSos1Constraint",
      [](MathematicalProgram* prog, int num_sections) {
        return AddLogarithmicSos1Constraint(prog, num_sections);
      },
      py::arg("prog"), py::arg("num_lambda"),
      doc.AddLogarithmicSos1Constraint.doc_2args);

  {
    py::enum_<IntervalBinning>(m, "IntervalBinning", doc.IntervalBinning.doc)
        .value("kLogarithmic", IntervalBinning::kLogarithmic)
        .value("kLinear", IntervalBinning::kLinear);
  }

  m.def(
      "AddBilinearProductMcCormickEnvelopeSos2",
      [](MathematicalProgram* prog, const symbolic::Variable& x,
          const symbolic::Variable& y, const symbolic::Expression& w,
          const VectorX<double>& phi_x, const VectorX<double>& phi_y,
          const VectorX<symbolic::Expression>& Bx,
          const VectorX<symbolic::Expression>& By, IntervalBinning binning) {
        return AddBilinearProductMcCormickEnvelopeSos2(
            prog, x, y, w, phi_x, phi_y, Bx, By, binning);
      },
      py::arg("prog"), py::arg("x"), py::arg("y"), py::arg("w"),
      py::arg("phi_x"), py::arg("phi_y"), py::arg("Bx"), py::arg("By"),
      py::arg("binning"), doc.AddBilinearProductMcCormickEnvelopeSos2.doc);
}

}  // namespace internal
}  // namespace pydrake
}  // namespace drake
