/* clang-format off to disable clang-format-includes */
#include "common/ad/test/standard_operations_test.h"
#include "common/autodiff.h"
/* clang-format on */

namespace drake {
namespace test {
namespace {

TEST_F(AutoDiffXdTest, Tanh) {
    CHECK_UNARY_FUNCTION(tanh, x, y, 0.1);
    CHECK_UNARY_FUNCTION(tanh, x, y, -0.1);
    CHECK_UNARY_FUNCTION(tanh, y, x, 0.1);
    CHECK_UNARY_FUNCTION(tanh, y, x, -0.1);
}

}  // namespace
}  // namespace test
}  // namespace drake