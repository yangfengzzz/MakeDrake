/* clang-format off to disable clang-format-includes */
#include "common/ad/test/standard_operations_test.h"
#include "common/autodiff.h"
/* clang-format on */

namespace drake {
namespace test {
namespace {

TEST_F(AutoDiffXdTest, Cosh) {
    CHECK_UNARY_FUNCTION(cosh, x, y, 0.1);
    CHECK_UNARY_FUNCTION(cosh, x, y, -0.1);
    CHECK_UNARY_FUNCTION(cosh, y, x, 0.1);
    CHECK_UNARY_FUNCTION(cosh, y, x, -0.1);
}

}  // namespace
}  // namespace test
}  // namespace drake