#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(pydrake LANGUAGES C CXX)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG)

set(AUTODIFF_FILES
        autodiffutils/autodiffutils_py_everything.cc
)

set(COMMON_FILES
        common/cpp_param_pybind.cc
        common/eigen_geometry_py.cc
        common/module_py.cc
        common/schema_py.cc
        common/text_logging_pybind.cc
        common/value_py.cc
)

set(GEOMETRY_FILES
        geometry/geometry_py.cc
        geometry/geometry_py_common.cc
        geometry/geometry_py_hydro.cc
        geometry/geometry_py_meshes.cc
        geometry/geometry_py_optimization.cc
        geometry/geometry_py_render.cc
        geometry/geometry_py_scene_graph.cc
        geometry/geometry_py_visualizers.cc
)

set(MANIPULATION_FILES
        manipulation/manipulation_py.cc
        manipulation/manipulation_py_kuka_iiwa.cc
        manipulation/manipulation_py_schunk_wsg.cc
        manipulation/manipulation_py_util.cc
)

set(MATH_FILES
        math/math_py_matmul.cc
        math/math_py_monolith.cc
        math/math_py_operators.cc
)

set(MULTIBODY_FILES
        multibody/fem_py.cc
        multibody/inverse_kinematics_py.cc
        multibody/inverse_kinematics_py_differential.cc
        multibody/math_py.cc
        multibody/meshcat_py.cc
        multibody/optimization_py.cc
        multibody/parsing_py.cc
        multibody/plant_py.cc
        multibody/rational_py.cc
        multibody/tree_py.cc
        multibody/tree_py_inertia.cc
)

set(PLANNING_FILES
        planning/planning_py.cc
        planning/planning_py_collision_checker.cc
        planning/planning_py_collision_checker_interface_types.cc
        planning/planning_py_graph_algorithms.cc
        planning/planning_py_iris_from_clique_cover.cc
        planning/planning_py_robot_diagram.cc
        planning/planning_py_trajectory_optimization.cc
        planning/planning_py_visibility_graph.cc
        planning/planning_py_zmp_planner.cc
)

set(SOLVERS_FILES
        solvers/solvers_py.cc
        solvers/solvers_py_augmented_lagrangian.cc
        solvers/solvers_py_branch_and_bound.cc
        solvers/solvers_py_clarabel.cc
        solvers/solvers_py_clp.cc
        solvers/solvers_py_csdp.cc
        solvers/solvers_py_evaluators.cc
        solvers/solvers_py_gurobi.cc
        solvers/solvers_py_ipopt.cc
        solvers/solvers_py_mathematicalprogram.cc
        solvers/solvers_py_mixed_integer_optimization_util.cc
        solvers/solvers_py_mixed_integer_rotation_constraint.cc
        solvers/solvers_py_mobylcp.cc
        solvers/solvers_py_mosek.cc
        solvers/solvers_py_nlopt.cc
        solvers/solvers_py_osqp.cc
        solvers/solvers_py_scs.cc
        solvers/solvers_py_sdpa_free_format.cc
        solvers/solvers_py_semidefinite_relaxation.cc
        solvers/solvers_py_snopt.cc
        solvers/solvers_py_unrevised_lemke.cc
)

set(SYMBOLIC_FILES
        symbolic/symbolic_py_monolith.cc
        symbolic/symbolic_py_unapply.cc
)

set(SYSTEM_FILES
        systems/analysis_py.cc
        systems/controllers_py.cc
        systems/estimators_py.cc
        systems/framework_py.cc
        systems/framework_py_semantics.cc
        systems/framework_py_systems.cc
        systems/framework_py_values.cc
        systems/lcm_py.cc
        systems/lcm_py_bind_cpp_serializers.cc
        systems/primitives_py.cc
        systems/rendering_py.cc
        systems/sensors_py.cc
        systems/sensors_py_camera_config.cc
        systems/sensors_py_image.cc
        systems/sensors_py_image_io.cc
        systems/sensors_py_lcm.cc
        systems/sensors_py_rgbd.cc
        systems/sensors_py_rotary_encoders.cc
)

set(VISUAL_FILES
        visualization/visualization_py.cc
        visualization/visualization_py_config.cc
        visualization/visualization_py_image_systems.cc
        visualization/visualization_py_sliders.cc
)

set(PROJECT_FILES
        ${AUTODIFF_FILES}
        ${COMMON_FILES}
        ${GEOMETRY_FILES}
        ${MANIPULATION_FILES}
        ${MATH_FILES}
        ${MULTIBODY_FILES}
        ${PLANNING_FILES}
        ${SOLVERS_FILES}
        ${SYMBOLIC_FILES}
        ${SYSTEM_FILES}
        ${VISUAL_FILES}
        lcm_py.cc
        perception_py.cc
        polynomial_py.cc
        trajectories_py.cc
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        pybind11::headers
)
