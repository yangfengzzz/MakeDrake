#pragma once

#include <Eigen/Dense>

#include "common/constants.h"
#include "common/eigen_types.h"

namespace drake {
namespace math {
template <typename Derived>
drake::Matrix3<typename Derived::Scalar> VectorToSkewSymmetric(const Eigen::MatrixBase<Derived>& p) {
    EIGEN_STATIC_ASSERT_VECTOR_SPECIFIC_SIZE(Eigen::MatrixBase<Derived>, 3);

    drake::Matrix3<typename Derived::Scalar> ret;
    ret << 0.0, -p(2), p(1), p(2), 0.0, -p(0), -p(1), p(0), 0.0;
    return ret;
}

}  // namespace math
}  // namespace drake
