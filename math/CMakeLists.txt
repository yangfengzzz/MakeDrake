#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(math LANGUAGES C CXX)

set(PROJECT_FILES
        autodiff.h
        autodiff.cc
        autodiff_gradient.h
        autodiff_gradient.cc
        barycentric.h
        barycentric.cc
        binomial_coefficient.h
        binomial_coefficient.cc
        bspline_basis.h
        bspline_basis.cc
        continuous_algebraic_riccati_equation.h
        continuous_algebraic_riccati_equation.cc
        continuous_lyapunov_equation.h
        continuous_lyapunov_equation.cc
        cross_product.h
        cross_product.cc
        differentiable_norm.h
        differentiable_norm.cc
        discrete_algebraic_riccati_equation.h
        discrete_algebraic_riccati_equation.cc
        discrete_lyapunov_equation.h
        discrete_lyapunov_equation.cc
        eigen_sparse_triplet.h
        eigen_sparse_triplet.cc
        evenly_distributed_pts_on_sphere.h
        evenly_distributed_pts_on_sphere.cc
        fast_pose_composition_functions_avx2_fma.cc
        gradient.h
        gradient.cc
        gray_code.h
        gray_code.cc
        hopf_coordinate.h
        hopf_coordinate.cc
        jacobian.h
        jacobian.cc
        linear_solve.h
        linear_solve.cc
        matrix_util.h
        matrix_util.cc
        normalize_vector.h
        normalize_vector.cc
        quadratic_form.h
        quadratic_form.cc
        quaternion.h
        quaternion.cc
        random_rotation.h
        random_rotation.cc
        rigid_transform.h
        rigid_transform.cc
        roll_pitch_yaw.h
        roll_pitch_yaw.cc
        rotation_conversion_gradient.h
        rotation_conversion_gradient.cc
        rotation_matrix.h
        rotation_matrix.cc
        soft_min_max.h
        soft_min_max.cc
        unit_vector.h
        unit_vector.cc
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        hwy::hwy
)
