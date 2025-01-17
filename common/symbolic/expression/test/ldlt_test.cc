/* clang-format off to disable clang-format-includes */
#include "common/symbolic/expression/all.h"
/* clang-format on */

#include <gtest/gtest.h>

#include "common/test_utilities/eigen_matrix_compare.h"
#include "common/test_utilities/expect_no_throw.h"

namespace drake {
namespace symbolic {
namespace test {
namespace {

GTEST_TEST(SymbolicLdlt, DynamicSize) {
    // An arbitrary positive-definite matrix.
    MatrixX<double> input_d(3, 3);
    // clang-format off
  input_d << 81, -9, 63,
             -9 , 2, -5,
             63, -5, 69;
    // clang-format on
    const auto ldlt_d = input_d.ldlt();

    // Perform LDLT decomposition, with Scalar = Expression.
    const MatrixX<Expression> input_e = input_d.template cast<Expression>();
    const auto ldlt_e = input_e.ldlt();

    // Check that Expression results match double results.
    EXPECT_TRUE(CompareMatrices(MatrixX<Expression>(ldlt_e.matrixL()), MatrixX<double>(ldlt_d.matrixL())));
    EXPECT_TRUE(CompareMatrices(MatrixX<Expression>(ldlt_e.matrixU()), MatrixX<double>(ldlt_d.matrixU())));
    EXPECT_TRUE(CompareMatrices(ldlt_e.transpositionsP().indices(), ldlt_d.transpositionsP().indices()));
    EXPECT_TRUE(CompareMatrices(ldlt_e.vectorD(), ldlt_d.vectorD()));
    EXPECT_TRUE(ldlt_e.isPositive());
    EXPECT_FALSE(ldlt_e.isNegative());
    EXPECT_EQ(ldlt_e.info(), ldlt_d.info());
}

GTEST_TEST(SymbolicLdlt, Exception) {
    MatrixX<Expression> dut(1, 1);
    dut(0, 0) = 0;
    DRAKE_EXPECT_NO_THROW(dut.ldlt());
    dut(0, 0) = Variable("a(0,0)");
    EXPECT_THROW(dut.ldlt(), std::exception);
}

GTEST_TEST(SymbolicLdlt, SizeUpTo6) {
    drake::MatrixUpTo6<Expression> dut(1, 1);
    dut.setZero();
    DRAKE_EXPECT_NO_THROW(dut.ldlt());
}

}  // namespace
}  // namespace test
}  // namespace symbolic
}  // namespace drake
