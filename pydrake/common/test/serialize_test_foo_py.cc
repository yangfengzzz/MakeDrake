#include "pydrake/common/test/serialize_test_foo_py.h"

#include "pydrake/common/serialize_pybind.h"

namespace drake {
namespace pydrake {
namespace test {

PYBIND11_MODULE(serialize_test_foo, m) {
  py::class_<Foo> cls(m, "Foo");
  DefAttributesUsingSerialize(&cls);
}

}  // namespace test
}  // namespace pydrake
}  // namespace drake
