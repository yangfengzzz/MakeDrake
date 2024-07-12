#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(systems LANGUAGES C CXX)

set(ANALYSIS_FILES
        analysis/antiderivative_function.cc
#        analysis/batch_eval.cc
        analysis/bogacki_shampine3_integrator.cc
        analysis/dense_output.cc
        analysis/explicit_euler_integrator.cc
        analysis/hermitian_dense_output.cc
        analysis/implicit_euler_integrator.cc
        analysis/implicit_integrator.cc
        analysis/initial_value_problem.cc
        analysis/integrator_base.cc
        analysis/lyapunov.cc
        analysis/monte_carlo.cc
        analysis/radau_integrator.cc
        analysis/realtime_rate_calculator.cc
        analysis/region_of_attraction.cc
        analysis/runge_kutta2_integrator.cc
        analysis/runge_kutta3_integrator.cc
        analysis/runge_kutta5_integrator.cc
        analysis/scalar_dense_output.cc
        analysis/scalar_initial_value_problem.cc
        analysis/scalar_view_dense_output.cc
        analysis/semi_explicit_euler_integrator.cc
        analysis/simulator.cc
        analysis/simulator_config.cc
        analysis/simulator_config_functions.cc
        analysis/simulator_gflags.cc
        analysis/simulator_print_stats.cc
        analysis/simulator_status.cc
        analysis/stepwise_dense_output.cc
        analysis/velocity_implicit_euler_integrator.cc
)

set(BENCHMARKING_FILES
        benchmarking/framework_benchmarks.cc
        benchmarking/multilayer_perceptron_benchmark.cc
)

set(CONTROLLER_FILES
        controllers/dynamic_programming.cc
        controllers/finite_horizon_linear_quadratic_regulator.cc
        controllers/inverse_dynamics.cc
        controllers/inverse_dynamics_controller.cc
        controllers/joint_stiffness_controller.cc
        controllers/linear_model_predictive_controller.cc
        controllers/linear_quadratic_regulator.cc
        controllers/pid_controlled_system.cc
        controllers/pid_controller.cc
)

set(ESTIMATOR_FILES
        estimators/kalman_filter.cc
        estimators/luenberger_observer.cc
)

set(FRAMEWORK_FILES
        framework/abstract_value_cloner.cc
        framework/abstract_values.cc
        framework/basic_vector.cc
        framework/cache.cc
        framework/cache_entry.cc
        framework/context.cc
        framework/context_base.cc
        framework/continuous_state.cc
        framework/dependency_tracker.cc
        framework/diagram.cc
        framework/diagram_builder.cc
        framework/diagram_context.cc
        framework/diagram_continuous_state.cc
        framework/diagram_discrete_values.cc
        framework/diagram_output_port.cc
        framework/diagram_state.cc
        framework/discrete_values.cc
        framework/event_collection.cc
        framework/event_status.cc
        framework/fixed_input_port_value.cc
        framework/input_port.cc
        framework/input_port_base.cc
        framework/leaf_context.cc
        framework/leaf_output_port.cc
        framework/leaf_system.cc
        framework/model_values.cc
        framework/output_port.cc
        framework/output_port_base.cc
        framework/parameters.cc
        framework/port_base.cc
        framework/scalar_conversion_traits.cc
        framework/single_output_vector_source.cc
        framework/state.cc
        framework/subvector.cc
        framework/supervector.cc
        framework/system.cc
        framework/system_base.cc
        framework/system_constraint.cc
        framework/system_output.cc
        framework/system_scalar_converter.cc
        framework/system_symbolic_inspector.cc
        framework/system_type_tag.cc
        framework/system_visitor.cc
        framework/value_producer.cc
        framework/vector_base.cc
        framework/vector_system.cc
        framework/witness_function.cc
)

set(LCM_FILES
        lcm/lcm_buses.cc
        lcm/lcm_config_functions.cc
        lcm/lcm_interface_system.cc
        lcm/lcm_log_playback_system.cc
        lcm/lcm_publisher_system.cc
        lcm/lcm_scope_system.cc
        lcm/lcm_subscriber_system.cc
        lcm/lcm_system_graphviz.cc
        lcm/serializer.cc
)

set(OPTIMIZATION_FILES
        optimization/system_constraint_adapter.cc
        optimization/system_constraint_wrapper.cc
)

set(PRIMITIVES_FILES
        primitives/adder.cc
        primitives/affine_system.cc
        primitives/barycentric_system.cc
        primitives/constant_value_source.cc
        primitives/constant_vector_source.cc
        primitives/demultiplexer.cc
        primitives/discrete_derivative.cc
        primitives/discrete_time_delay.cc
        primitives/discrete_time_integrator.cc
        primitives/first_order_low_pass_filter.cc
        primitives/gain.cc
        primitives/integrator.cc
        primitives/linear_system.cc
        primitives/linear_system_internal.cc
        primitives/linear_transform_density.cc
        primitives/matrix_gain.cc
        primitives/multilayer_perceptron.cc
        primitives/multiplexer.cc
        primitives/pass_through.cc
        primitives/port_switch.cc
        primitives/random_source.cc
        primitives/saturation.cc
        primitives/shared_pointer_system.cc
        primitives/sine.cc
        primitives/symbolic_vector_system.cc
        primitives/trajectory_affine_system.cc
        primitives/trajectory_linear_system.cc
        primitives/trajectory_source.cc
        primitives/transfer_function.cc
        primitives/vector_log.cc
        primitives/vector_log_sink.cc
        primitives/wrap_to_system.cc
        primitives/zero_order_hold.cc
)

set(RENDERING_FILES
        rendering/multibody_position_to_geometry_pose.cc
)

set(SENSOR_FILES
        sensors/accelerometer.cc
        sensors/beam_model.cc
        sensors/beam_model_params.cc
        sensors/camera_config.cc
        sensors/camera_config_functions.cc
        sensors/camera_info.cc
        sensors/gyroscope.cc
        sensors/image.cc
        sensors/image_file_format.cc
        sensors/image_io_internal.cc
        sensors/image_io_load.cc
        sensors/image_io_save.cc
        sensors/image_to_lcm_image_array_t.cc
        sensors/image_writer.cc
        sensors/lcm_image_array_to_images.cc
        sensors/lcm_image_traits.cc
        sensors/pixel_types.cc
        sensors/rgbd_sensor.cc
        sensors/rgbd_sensor_async.cc
        sensors/rgbd_sensor_discrete.cc
        sensors/rotary_encoders.cc
        sensors/sim_rgbd_sensor.cc
        sensors/vtk_diagnostic_event_observer.cc
        sensors/vtk_image_reader_writer.cc
)

set(PROJECT_FILES
        ${ANALYSIS_FILES}
        ${BENCHMARKING_FILES}
        ${CONTROLLER_FILES}
        ${ESTIMATOR_FILES}
        ${FRAMEWORK_FILES}
        ${LCM_FILES}
        ${OPTIMIZATION_FILES}
        ${PRIMITIVES_FILES}
        ${RENDERING_FILES}
        ${SENSOR_FILES}
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        ${VTK_LIBRARIES}
        common_robotics_utilities
        lcm_types
)
