#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(multibody LANGUAGES C CXX)

set(CONSTRAINT_FILES
        constraint/constraint_solver.cc
)

set(CONTACT_SOLVERS
        contact_solvers/sap/contact_problem_graph.cc
        contact_solvers/sap/dense_supernodal_solver.cc
        contact_solvers/sap/expect_equal.cc
        contact_solvers/sap/partial_permutation.cc
        contact_solvers/sap/sap_ball_constraint.cc
        contact_solvers/sap/sap_constraint.cc
        contact_solvers/sap/sap_constraint_bundle.cc
        contact_solvers/sap/sap_constraint_jacobian.cc
        contact_solvers/sap/sap_contact_problem.cc
        contact_solvers/sap/sap_coupler_constraint.cc
        contact_solvers/sap/sap_distance_constraint.cc
        contact_solvers/sap/sap_fixed_constraint.cc
        contact_solvers/sap/sap_friction_cone_constraint.cc
        contact_solvers/sap/sap_holonomic_constraint.cc
        contact_solvers/sap/sap_hunt_crossley_constraint.cc
        contact_solvers/sap/sap_limit_constraint.cc
        contact_solvers/sap/sap_model.cc
        contact_solvers/sap/sap_pd_controller_constraint.cc
        contact_solvers/sap/sap_solver.cc
        contact_solvers/sap/sap_solver_results.cc
        contact_solvers/sap/sap_weld_constraint.cc
        contact_solvers/sap/validate_constraint_gradients.cc
        contact_solvers/block_3x3_sparse_matrix.cc
        contact_solvers/block_3x3_sparse_matrix.cc
        contact_solvers/block_sparse_lower_triangular_or_symmetric_matrix.cc
        contact_solvers/block_sparse_matrix.cc
        contact_solvers/block_sparse_supernodal_solver.cc
        contact_solvers/conex_supernodal_solver.cc
        contact_solvers/contact_configuration.cc
        contact_solvers/contact_solver.cc
        contact_solvers/contact_solver_results.cc
        contact_solvers/linear_operator.cc
        contact_solvers/matrix_block.cc
        contact_solvers/minimum_degree_ordering.cc
        contact_solvers/newton_with_bisection.cc
        contact_solvers/pgs_solver.cc
        contact_solvers/point_contact_data.cc
        contact_solvers/schur_complement.cc
        contact_solvers/sparse_linear_operator.cc
        contact_solvers/supernodal_solver.cc
        contact_solvers/system_dynamics_data.cc
)

set(FEM_FILES
        fem/acceleration_newmark_scheme.cc
        fem/calc_lame_parameters.cc
        fem/corotated_model.cc
        fem/corotated_model_data.cc
        fem/damping_model.cc
        fem/deformation_gradient_data.cc
        fem/dirichlet_boundary_condition.cc
        fem/discrete_time_integrator.cc
        fem/fem_element.cc
        fem/fem_model.cc
        fem/fem_model_impl.cc
        fem/fem_plant_data.cc
        fem/fem_solver.cc
        fem/fem_state.cc
        fem/fem_state_system.cc
        fem/isoparametric_element.cc
        fem/linear_constitutive_model.cc
        fem/linear_constitutive_model_data.cc
        fem/linear_corotated_model.cc
        fem/linear_corotated_model_data.cc
        fem/linear_simplex_element.cc
        fem/matrix_utilities.cc
        fem/quadrature.cc
        fem/schur_complement.cc
        fem/simplex_gaussian_quadrature.cc
        fem/velocity_newmark_scheme.cc
        fem/volumetric_element.cc
)

set(HYDROELASTICS_FILES
        hydroelastics/hydroelastic_engine.cc
)

set(INVERSE_KINEMATICS_FILES
        inverse_kinematics/angle_between_vectors_constraint.cc
        inverse_kinematics/angle_between_vectors_cost.cc
        inverse_kinematics/com_in_polyhedron_constraint.cc
        inverse_kinematics/com_position_constraint.cc
        inverse_kinematics/constraint_relaxing_ik.cc
        inverse_kinematics/differential_inverse_kinematics.cc
        inverse_kinematics/differential_inverse_kinematics_integrator.cc
        inverse_kinematics/distance_constraint.cc
        inverse_kinematics/distance_constraint_utilities.cc
        inverse_kinematics/gaze_target_constraint.cc
        inverse_kinematics/global_inverse_kinematics.cc
        inverse_kinematics/inverse_kinematics.cc
        inverse_kinematics/kinematic_evaluator_utilities.cc
        inverse_kinematics/minimum_distance_lower_bound_constraint.cc
        inverse_kinematics/minimum_distance_upper_bound_constraint.cc
        inverse_kinematics/orientation_constraint.cc
        inverse_kinematics/orientation_cost.cc
        inverse_kinematics/point_to_line_distance_constraint.cc
        inverse_kinematics/point_to_point_distance_constraint.cc
        inverse_kinematics/polyhedron_constraint.cc
        inverse_kinematics/position_constraint.cc
        inverse_kinematics/position_cost.cc
        inverse_kinematics/unit_quaternion_constraint.cc
)

set(MATH_FILES
        math/spatial_algebra.cc
)

set(MESHCAT_FILES
        meshcat/contact_visualizer.cc
        meshcat/hydroelastic_contact_visualizer.cc
        meshcat/joint_sliders.cc
        meshcat/point_contact_visualizer.cc
)

set(OPTIMIZATION_FILES
        optimization/centroidal_momentum_constraint.cc
        optimization/contact_wrench_evaluator.cc
        optimization/manipulator_equation_constraint.cc
        optimization/quaternion_integration_constraint.cc
        optimization/sliding_friction_complementarity_constraint.cc
        optimization/spatial_velocity_constraint.cc
        optimization/static_equilibrium_constraint.cc
        optimization/static_equilibrium_problem.cc
        optimization/static_friction_cone_complementarity_constraint.cc
        optimization/static_friction_cone_constraint.cc
        optimization/toppra.cc
)

set(PARRSING_FILES
        parsing/collision_filter_groups.cc
        parsing/detail_collision_filter_group_resolver.cc
        parsing/detail_collision_filter_groups_impl.cc
        parsing/detail_common.cc
        parsing/detail_composite_parse.cc
        parsing/detail_dmd_parser.cc
        parsing/detail_ignition.cc
        parsing/detail_instanced_name.cc
        parsing/detail_make_model_name.cc
        parsing/detail_mesh_parser.cc
        parsing/detail_mujoco_parser.cc
        parsing/detail_path_utils.cc
        parsing/detail_sdf_diagnostic.cc
        parsing/detail_sdf_geometry.cc
        parsing/detail_sdf_parser.cc
        parsing/detail_select_parser.cc
        parsing/detail_tinyxml.cc
        parsing/detail_tinyxml2_diagnostic.cc
        parsing/detail_urdf_geometry.cc
        parsing/detail_urdf_parser.cc
        #        parsing/detail_usd_geometry.cc
        #        parsing/detail_usd_parser.cc
        #        parsing/detail_usd_parser_off.cc
        parsing/package_map.cc
        parsing/parser.cc
        parsing/process_model_directives.cc
        parsing/scoped_names.cc
)

set(PLANT_FILES
        plant/calc_distance_and_time_derivative.cc
        plant/compliant_contact_manager.cc
        plant/contact_jacobians.cc
        plant/contact_properties.cc
        plant/contact_results.cc
        plant/contact_results_to_lcm.cc
        plant/coulomb_friction.cc
        plant/deformable_contact_info.cc
        plant/deformable_driver.cc
        plant/deformable_model.cc
        plant/discrete_update_manager.cc
        plant/dummy_physical_model.cc
        plant/externally_applied_spatial_force.cc
        plant/externally_applied_spatial_force_multiplexer.cc
        plant/force_density_field.cc
        plant/hydroelastic_contact_info.cc
        plant/hydroelastic_traction_calculator.cc
        plant/internal_geometry_names.cc
        plant/make_discrete_update_manager.cc
        plant/multibody_plant.cc
        plant/multibody_plant_config.cc
        plant/multibody_plant_config_functions.cc
        plant/physical_model.cc
        plant/physical_model_collection.cc
        plant/point_pair_contact_info.cc
        plant/propeller.cc
        plant/sap_driver.cc
        plant/scalar_convertible_component.cc
        plant/slicing_and_indexing.cc
        plant/tamsi_driver.cc
        plant/wing.cc
)

set(RATIONAL_FILES
        rational/rational_forward_kinematics.cc
        rational/rational_forward_kinematics_internal.cc
)

set(TOPOLOGY_FILES
        topology/link_joint_graph.cc
        topology/multibody_graph.cc
        topology/spanning_forest.cc
        topology/spanning_forest_mobod.cc
)

set(TREE_FILES
        tree/acceleration_kinematics_cache.cc
        tree/articulated_body_force_cache.cc
        tree/articulated_body_inertia.cc
        tree/articulated_body_inertia_cache.cc
        tree/ball_rpy_joint.cc
        tree/body_node.cc
        tree/body_node_impl.cc
        tree/door_hinge.cc
        tree/element_collection.cc
        tree/fixed_offset_frame.cc
        tree/force_element.cc
        tree/frame.cc
        tree/frame_base.cc
        tree/geometry_spatial_inertia.cc
        tree/joint.cc
        tree/joint_actuator.cc
        tree/linear_bushing_roll_pitch_yaw.cc
        tree/linear_spring_damper.cc
        tree/mobilizer.cc
        tree/mobilizer_impl.cc
        tree/model_instance.cc
        tree/multibody_element.cc
        tree/multibody_forces.cc
        tree/multibody_tree.cc
        tree/multibody_tree_system.cc
        tree/multibody_tree_topology.cc
        tree/planar_joint.cc
        tree/planar_mobilizer.cc
        tree/position_kinematics_cache.cc
        tree/prismatic_joint.cc
        tree/prismatic_mobilizer.cc
        tree/prismatic_spring.cc
        tree/quaternion_floating_joint.cc
        tree/quaternion_floating_mobilizer.cc
        tree/revolute_joint.cc
        tree/revolute_mobilizer.cc
        tree/revolute_spring.cc
        tree/rigid_body.cc
        tree/rotational_inertia.cc
        tree/rpy_ball_mobilizer.cc
        tree/rpy_floating_joint.cc
        tree/rpy_floating_mobilizer.cc
        tree/scoped_name.cc
        tree/screw_joint.cc
        tree/screw_mobilizer.cc
        tree/spatial_inertia.cc
        tree/uniform_gravity_field_element.cc
        tree/unit_inertia.cc
        tree/universal_joint.cc
        tree/universal_mobilizer.cc
        tree/velocity_kinematics_cache.cc
        tree/weld_joint.cc
        tree/weld_mobilizer.cc
)

set(TRIANGLE_QUADRATURE_FILES
        triangle_quadrature/triangle_quadrature.cc
)

set(PROJECT_FILES
        ${CONSTRAINT_FILES}
        ${CONTACT_SOLVERS}
        ${FEM_FILES}
        ${HYDROELASTICS_FILES}
        ${INVERSE_KINEMATICS_FILES}
        ${MATH_FILES}
        ${MESHCAT_FILES}
        ${OPTIMIZATION_FILES}
        ${PARRSING_FILES}
        ${PLANT_FILES}
        ${RATIONAL_FILES}
        ${TOPOLOGY_FILES}
        ${TREE_FILES}
        ${TRIANGLE_QUADRATURE_FILES}
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
        conex
        tinyxml2::tinyxml2
        sdformat13::core GzURDFDOM::GzURDFDOM sdformat13::requested sdformat13::sdformat13
        lcm_types

)
