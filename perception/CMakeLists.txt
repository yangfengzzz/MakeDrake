#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(perception LANGUAGES C CXX)

set(PROJECT_FILES
        depth_image_to_point_cloud.cc
        point_cloud.cc
        point_cloud_flags.cc
        point_cloud_to_lcm.cc
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
