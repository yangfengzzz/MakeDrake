#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(drake-lcm LANGUAGES C CXX)

set(PROJECT_FILES
        drake_lcm.cc
        drake_lcm_base.cc
        drake_lcm_interface.cc
        drake_lcm_log.cc
        lcm_messages.cc
        lcmt_drake_signal_utils.cc
)

add_library(${PROJECT_NAME} STATIC ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        ${GLIB2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        Eigen3::Eigen
        fmt::fmt-header-only
        lcm_types
)
