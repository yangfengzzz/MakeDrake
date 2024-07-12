#  Copyright (c) 2024 Feng Yang
#
#  I am making my contributions/submissions to this project solely in my
#  personal capacity and am not conveying any rights to any intellectual
#  property of any third parties.

# create sample app project
project(lcm_types LANGUAGES C CXX)

file(GLOB PROJECT_FILES ./*.hpp)

add_library(${PROJECT_NAME} INTERFACE ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(${PROJECT_NAME} INTERFACE
        lcm-coretypes
)