/* clang-format off to disable clang-format-includes */
#include "common/ad/test/standard_operations_test.h"
#include "common/autodiff.h"
/* clang-format on */

namespace drake {
namespace test {
namespace {

TEST_F(AutoDiffXdTest, Atan2) {
    CHECK_BINARY_FUNCTION_ADS_ADS(atan2, x, y, 0.1);
    CHECK_BINARY_FUNCTION_ADS_ADS(atan2, x, y, -0.1);
    CHECK_BINARY_FUNCTION_ADS_ADS(atan2, y, x, 0.4);
    CHECK_BINARY_FUNCTION_ADS_ADS(atan2, y, x, -0.4);
}

}  // namespace
}  // namespace test
}  // namespace drake
