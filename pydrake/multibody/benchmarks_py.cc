#include "pybind11/eval.h"

#include "pydrake/documentation_pybind.h"
#include "pydrake/pydrake_pybind.h"
#include "multibody/benchmarks/acrobot/make_acrobot_plant.h"
#include "multibody/benchmarks/mass_damper_spring/mass_damper_spring_analytical_solution.h"

namespace drake {
namespace pydrake {

using geometry::SceneGraph;
using systems::LeafSystem;

// TODO(eric.cousineau): Bind additional scalar types.
using T = double;

void init_acrobot(py::module m) {
  // NOLINTNEXTLINE(build/namespaces): Emulate placement in namespace.
  using namespace drake::multibody::benchmarks::acrobot;
  constexpr auto& doc = pydrake_doc.drake.multibody.benchmarks.acrobot;

  py::module::import("pydrake.geometry");
  py::module::import("pydrake.multibody.plant");

  py::class_<AcrobotParameters>(
      m, "AcrobotParameters", doc.AcrobotParameters.doc)
      .def(py::init(), doc.AcrobotParameters.doc);

  m.def("MakeAcrobotPlant",
      py::overload_cast<const AcrobotParameters&, bool, SceneGraph<double>*>(
          &MakeAcrobotPlant),
      py::arg("default_parameters"), py::arg("finalize"),
      py::arg("scene_graph") = nullptr, doc.MakeAcrobotPlant.doc);
}

void init_all(py::module m) {
  py::dict vars = m.attr("__dict__");
  py::exec("from pydrake.multibody.benchmarks.acrobot import *", py::globals(),
      vars);
}

PYBIND11_MODULE(benchmarks, m) {
  init_acrobot(m.def_submodule("acrobot"));
  init_all(m.def_submodule("all"));

  constexpr auto& doc = pydrake_doc.drake.multibody.benchmarks;

  {
    using Class = multibody::benchmarks::MassDamperSpringAnalyticalSolution<T>;
    constexpr auto& cls_doc = doc.MassDamperSpringAnalyticalSolution;
    py::class_<Class>(m, "MassDamperSpringAnalyticalSolution", cls_doc.doc)
        .def(py::init<const T&, const T&, const T&>(), py::arg("mass"),
            py::arg("b"), py::arg("k"), cls_doc.ctor.doc)
        .def("SetInitialValue", &Class::SetInitialValue, py::arg("x0"),
            py::arg("xDt0"), cls_doc.SetInitialValue.doc)
        .def("get_x", &Class::get_x, py::arg("t"), cls_doc.get_x.doc)
        .def("get_xDt", &Class::get_xDt, py::arg("t"), cls_doc.get_xDt.doc)
        .def("get_xDtDt", &Class::get_xDtDt, py::arg("t"),
            cls_doc.get_xDtDt.doc);
  }
}

}  // namespace pydrake
}  // namespace drake
