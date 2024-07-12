#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(solvers LANGUAGES C CXX)

set(PROJECT_FILES
        aggregate_costs_constraints.cc
        augmented_lagrangian.cc
        branch_and_bound.cc
        choose_best_solver.cc

        #
        no_clarabel.cc
        #        clarabel_solver.cc
        #        clarabel_solver_common.cc

        #
        no_clp.cc
        #        clp_solver.cc
        #        clp_solver_common.cc

        #
        no_gurobi.cc
        #        gurobi_solver.cc
        #        gurobi_solver_common.cc
        #        gurobi_solver_internal.cc

        #
        no_ipopt.cc
        #        ipopt_solver.cc
        #        ipopt_solver_common.cc
        #        ipopt_solver_internal.cc

        #
        no_mosek.cc
        #        mosek_solver.cc
        #        mosek_solver_common.cc
        #        mosek_solver_internal.cc

        #
        no_nlopt.cc
        #        nlopt_solver.cc
        #        nlopt_solver_common.cc

        #
        no_osqp.cc
        #        osqp_solver.cc
        #        osqp_solver_common.cc

        #
        no_scs.cc
        #        scs_clarabel_common.cc
        #        scs_solver.cc
        #        scs_solver_common.cc

        #
        no_snopt.cc
        #        snopt_solver.cc
        #        snopt_solver_common.cc

        #
        no_csdp.cc
        #        csdp_cpp_wrapper.cc
        #        csdp_solver.cc
        #        csdp_solver_common.cc
        #        csdp_solver_error_handling.cc
        #        csdp_solver_internal.cc

        common_solver_option.cc
        constraint.cc
        cost.cc
        create_constraint.cc
        create_cost.cc
        decision_variable.cc
        equality_constrained_qp_solver.cc
        evaluator_base.cc
        get_program_type.cc
        indeterminate.cc
        integer_inequality_solver.cc
        linear_system_solver.cc
        mathematical_program.cc
        mathematical_program_doxygen.h
        mathematical_program_result.cc
        minimum_value_constraint.cc
        mixed_integer_optimization_util.cc
        mixed_integer_rotation_constraint.cc
        mixed_integer_rotation_constraint_internal.cc
        moby_lcp_solver.cc
        non_convex_optimization_util.cc
        program_attribute.cc
        rotation_constraint.cc
        sdpa_free_format.cc
        semidefinite_relaxation.cc
        semidefinite_relaxation_internal.cc
        solution_result.cc
        solve.cc
        solver_base.cc
        solver_id.cc
        solver_interface.cc
        solver_options.cc
        solver_type_converter.cc
        sos_basis_generator.cc
        sparse_and_dense_matrix.cc
        unrevised_lemke_solver.cc
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
