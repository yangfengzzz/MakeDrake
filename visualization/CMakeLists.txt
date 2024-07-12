#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(visualization LANGUAGES C CXX)

set(PROJECT_FILES
        colorize_depth_image.cc
        colorize_label_image.cc
        concatenate_images.cc
        inertia_visualizer.cc
        meshcat_pose_sliders.cc
        visualization_config.cc
        visualization_config_functions.cc
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        lcm_types
)
