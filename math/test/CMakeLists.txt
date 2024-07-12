#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(math-tests LANGUAGES C CXX)

set(PROJECT_FILES
        autodiff_test.cc
        barycentric_test.cc
        binomial_coefficient_test.cc
        bspline_basis_test.cc
        compute_numerical_gradient_test.cc
        continuous_algebraic_riccati_equation_test.cc
        continuous_lyapunov_equation_test.cc
        convert_time_derivative_test.cc
        cross_product_test.cc
        differentiable_norm_test.cc
        discrete_algebraic_riccati_equation_test.cc
        discrete_lyapunov_equation_test.cc
        eigen_sparse_triplet_test.cc
        evenly_distributed_pts_on_sphere_test.cc
        #        expmap_test.cc
        #        fast_pose_composition_functions_test.cc
        gradient_util_test.cc
        gray_code_test.cc
        hopf_coordinate_test.cc
        jacobian_test.cc
        linear_solve_test.cc
        matrix_util_test.cc
        normalize_vector_test.cc
        quadratic_form_test.cc
        quaternion_test.cc
        random_rotation_test.cc
        rigid_transform_test.cc
        roll_pitch_yaw_test.cc
        rotation_conversion_test.cc
        rotation_matrix_test.cc
        soft_min_max_test.cc
        unit_vector_test.cc
        wrap_to_test.cc
)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        math
        hwy::hwy
        GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        common
        systems
        solvers
        absl::any absl::log absl::base absl::raw_hash_set
)
