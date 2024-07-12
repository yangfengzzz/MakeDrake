#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(common LANGUAGES C CXX)

set(AD_FILES
        ad/internal/partials.cc
        ad/internal/standard_operations.cc
)

set(BENCHMARKING_FILES
        benchmarking/benchmark_polynomial.cc
)

set(SCHEMA_FILES
        schema/rotation.cc
        schema/stochastic.cc
        schema/transform.cc
)

set(SYMBOLIC_FILES
        symbolic/expression/all.cc
        symbolic/expression/boxed_cell.cc
        symbolic/expression/environment.cc
        symbolic/expression/expression.cc
        symbolic/expression/expression_cell.cc
        symbolic/expression/formula.cc
        symbolic/expression/formula_cell.cc
        symbolic/expression/ldlt.cc
        symbolic/expression/variable.cc
        symbolic/expression/variables.cc
        symbolic/chebyshev_basis_element.cc
        symbolic/chebyshev_polynomial.cc
        symbolic/codegen.cc
        symbolic/decompose.cc
        symbolic/generic_polynomial.cc
        symbolic/latex.cc
        symbolic/monomial.cc
        symbolic/monomial_basis_element.cc
        symbolic/monomial_util.cc
        symbolic/polynomial.cc
        symbolic/polynomial_basis_element.cc
        symbolic/rational_function.cc
        symbolic/replace_bilinear_terms.cc
        symbolic/simplification.cc
        symbolic/trigonometric_polynomial.cc
)

set(TRAJ_FILES
        trajectories/bezier_curve.cc
        trajectories/bspline_trajectory.cc
        trajectories/composite_trajectory.cc
        trajectories/derivative_trajectory.cc
        trajectories/discrete_time_trajectory.cc
        trajectories/exponential_plus_piecewise_polynomial.cc
        trajectories/path_parameterized_trajectory.cc
        trajectories/piecewise_polynomial.cc
        trajectories/piecewise_pose.cc
        trajectories/piecewise_quaternion.cc
        trajectories/piecewise_trajectory.cc
        trajectories/stacked_trajectory.cc
        trajectories/trajectory.cc
)

set(YAML_FILES
        yaml/yaml_io.cc
        yaml/yaml_io_options.cc
        yaml/yaml_node.cc
        yaml/yaml_read_archive.cc
        yaml/yaml_write_archive.cc
)

set(PROJECT_FILES
        ${AD_FILES}
        ${BENCHMARKING_FILES}
        ${SCHEMA_FILES}
        ${SYMBOLIC_FILES}
        ${TRAJ_FILES}
        ${YAML_FILES}
        add_text_logging_gflags.cc
        cond.cc
        diagnostic_policy.cc
        double_overloads.cc
        drake_assert_and_throw.cc
        drake_deprecated.cc
        drake_marker.cc
        drake_path.cc
        find_cache.cc
        find_loaded_library.cc
        find_resource.cc
#        find_runfiles.cc
        find_runfiles_stub.cc
        fmt_eigen.cc
        hash.cc
        hwy_dynamic.cc
        identifier.cc
        network_policy.cc
        nice_type_name.cc
        nice_type_name_override.cc
        parallelism.cc
        pointer_cast.cc
        polynomial.cc
        random.cc
        resource_tool.cc
        sha256.cc
        sorted_pair.cc
        temp_directory.cc
        text_logging.cc
        timer.cc
        type_safe_index.cc
        value.cc
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        benchmark::benchmark
        yaml-cpp::yaml-cpp
        gflags::gflags
)
