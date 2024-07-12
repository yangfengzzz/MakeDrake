#include "common/drake_throw.h"

#include <stdexcept>

#include "common/test_utilities/expect_no_throw.h"
#include <gtest/gtest.h>

namespace {

GTEST_TEST(DrakeThrowTest, BasicTest) {
    DRAKE_EXPECT_NO_THROW(DRAKE_THROW_UNLESS(true));
    EXPECT_THROW(DRAKE_THROW_UNLESS(false), std::runtime_error);
}

}  // namespace
