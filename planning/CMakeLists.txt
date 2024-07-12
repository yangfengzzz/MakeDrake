#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(planning LANGUAGES C CXX)

set(GRAPH_FILES
        graph_algorithms/graph_algorithms_internal.cc
        graph_algorithms/max_clique_solver_base.cc
        graph_algorithms/max_clique_solver_via_greedy.cc
        graph_algorithms/max_clique_solver_via_mip.cc
)

set(IRIS_FILES
        iris/iris_from_clique_cover.cc
)

set(LOCOMOTION_FILES
        locomotion/zmp_planner.cc
)

set(TRAJECTORY_FILES
        trajectory_optimization/direct_collocation.cc
        trajectory_optimization/direct_transcription.cc
        trajectory_optimization/gcs_trajectory_optimization.cc
        trajectory_optimization/integration_constraint.cc
        trajectory_optimization/kinematic_trajectory_optimization.cc
        trajectory_optimization/multiple_shooting.cc
        trajectory_optimization/sequential_expression_manager.cc
)

set(PROJECT_FILES
        ${GRAPH_FILES}
        ${IRIS_FILES}
        ${LOCOMOTION_FILES}
        ${TRAJECTORY_FILES}
        body_shape_description.cc
        collision_avoidance.cc
        collision_checker.cc
        collision_checker_context.cc
        distance_and_interpolation_provider.cc
        linear_distance_and_interpolation_provider.cc
        robot_clearance.cc
        robot_diagram.cc
        robot_diagram_builder.cc
        scene_graph_collision_checker.cc
        unimplemented_collision_checker.cc
        visibility_graph.cc
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        common_robotics_utilities
        nanoflann::nanoflann
        lcm_types
)