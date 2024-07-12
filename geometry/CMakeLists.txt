#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(geometry LANGUAGES C CXX)

set(OPTIMIZATION_FILES
        optimization/affine_ball.cc
        optimization/affine_subspace.cc
        optimization/c_iris_collision_geometry.cc
        optimization/cartesian_product.cc
        optimization/convex_set.cc
        optimization/cspace_free_box.cc
        optimization/cspace_free_internal.cc
        optimization/cspace_free_polytope.cc
        optimization/cspace_free_polytope_base.cc
        optimization/cspace_separating_plane.cc
        optimization/geodesic_convexity.cc
        optimization/graph_of_convex_sets.cc
        optimization/hpolyhedron.cc
        optimization/hyperellipsoid.cc
        optimization/hyperrectangle.cc
        optimization/intersection.cc
        optimization/iris.cc
        optimization/iris_internal.cc
        optimization/minkowski_sum.cc
        optimization/point.cc
        optimization/spectrahedron.cc
        optimization/test_utilities.cc
        optimization/vpolytope.cc
)

set(PROFILING_FILES
        #        profiling/contact_surface_rigid_bowl_soft_ball.cc
)

set(PROXIMITY_FILES
        proximity/aabb.cc
        proximity/boxes_overlap.cc
        proximity/bvh.cc
        proximity/calc_distance_to_surface_mesh.cc
        proximity/collision_filter.cc
        proximity/collisions_exist_callback.cc
        proximity/contact_surface_utility.cc
        proximity/deformable_contact_geometries.cc
        proximity/deformable_contact_geometries.h
        proximity/deformable_field_intersection.cc
        proximity/deformable_mesh_intersection.cc
        proximity/detect_zero_simplex.cc
        proximity/distance_to_point_callback.cc
        proximity/distance_to_shape_callback.cc
        proximity/distance_to_shape_touching.cc
        proximity/field_intersection.cc
        proximity/find_collision_candidates_callback.cc
        proximity/hydroelastic_internal.cc
        proximity/make_box_field.cc
        proximity/make_box_mesh.cc
        proximity/make_capsule_mesh.cc
        proximity/make_convex_hull_mesh.cc
        proximity/make_convex_hull_mesh_impl.cc
        proximity/make_convex_mesh.cc
        proximity/make_cylinder_field.cc
        proximity/make_cylinder_mesh.cc
        proximity/make_mesh_field.cc
        proximity/make_mesh_from_vtk.cc
        proximity/mesh_half_space_intersection.cc
        proximity/mesh_intersection.cc
        proximity/mesh_plane_intersection.cc
        proximity/mesh_to_vtk.cc
        proximity/meshing_utilities.cc
        proximity/obb.cc
        proximity/obj_to_surface_mesh.cc
        proximity/penetration_as_point_pair_callback.cc
        proximity/polygon_surface_mesh.cc
        proximity/polygon_surface_mesh_field.cc
        proximity/polygon_to_triangle_mesh.cc
        proximity/proximity_utilities.cc
        proximity/refine_mesh.cc
        proximity/sorted_triplet.cc
        proximity/triangle_surface_mesh.cc
        proximity/triangle_surface_mesh_field.cc
        proximity/volume_mesh.cc
        proximity/volume_mesh_field.cc
        proximity/volume_mesh_refiner.cc
        proximity/volume_to_surface_mesh.cc
        proximity/vtk_to_volume_mesh.cc
)

set(QUERY_RESULT_FILES
        query_results/contact_surface.cc
        query_results/deformable_contact.cc
)

set(RENDER_FILES
        render/light_parameter.cc
        render/render_camera.cc
        render/render_engine.cc
        render/render_label.cc
        render/render_material.cc
        render/render_mesh.cc
)

set(RENDER_GL_FILES
        render_gl/factory.cc
        render_gl/internal_opengl_context.cc
        render_gl/internal_render_engine_gl.cc
        render_gl/internal_shader_program.cc
        render_gl/internal_shape_meshes.cc
        render_gl/internal_texture_library.cc
        render_gl/no_factory.cc
)

set(RENDER_GLTF_CLIENT
        render_gltf_client/factory.cc
        render_gltf_client/internal_http_service.cc
        render_gltf_client/internal_http_service_curl.cc
        render_gltf_client/internal_merge_gltf.cc
        render_gltf_client/internal_render_client.cc
        render_gltf_client/internal_render_engine_gltf_client.cc
        render_gltf_client/render_engine_gltf_client_params.cc
)

set(RENDER_VTK
        render_vtk/factory.cc
        render_vtk/internal_render_engine_vtk.cc
        render_vtk/internal_render_engine_vtk_base.cc
        render_vtk/internal_vtk_util.cc
        render_vtk/render_engine_vtk_params.cc
)

set(PROJECT_FILES
        ${OPTIMIZATION_FILES}
        ${PROXIMITY_FILES}
        ${QUERY_RESULT_FILES}
        ${RENDER_FILES}
#        ${RENDER_GL_FILES}
        ${RENDER_GLTF_CLIENT}
        ${RENDER_VTK}
        collision_filter_declaration.cc
        collision_filter_manager.cc
        deformable_mesh_with_bvh.cc
        drake_visualizer.cc
        geometry_frame.cc
        geometry_instance.cc
        geometry_properties.cc
        geometry_roles.cc
        geometry_state.cc
        geometry_version.cc
        internal_frame.cc
        internal_geometry.cc
        kinematics_vector.cc
        make_mesh_for_deformable.cc
        mesh_deformation_interpolator.cc
        meshcat.cc
        meshcat_animation.cc
        meshcat_file_storage_internal.cc
        meshcat_graphviz.cc
        meshcat_internal.cc
        meshcat_point_cloud_visualizer.cc
        meshcat_recording_internal.cc
        meshcat_visualizer.cc
        proximity_engine.cc
        proximity_properties.cc
        query_object.cc
        read_obj.cc
        rgba.cc
        scene_graph.cc
        scene_graph_config.cc
        scene_graph_inspector.cc
        shape_specification.cc
        utilities.cc
        vtk_opengl_init.cc
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
        tinyobjloader::tinyobjloader
        common_robotics_utilities
        nlohmann_json::nlohmann_json
        lcm_types
        stduuid
)
