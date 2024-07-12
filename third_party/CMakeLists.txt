# robotics utilities
set(COMMON_ROBOTICS_UTILITIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/common_robotics_utilities")
set(COMMON_ROBOTICS_FILES
        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/base64_helpers.cpp"
        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/conversions.cpp"
        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/math.cpp"
#        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/ros_conversions.cpp"
        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/serialization.cpp"
        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/time_optimal_trajectory_parametrization.cpp"
        "${COMMON_ROBOTICS_UTILITIES_DIR}/src/common_robotics_utilities/zlib_helpers.cpp"
)

add_library(common_robotics_utilities STATIC ${COMMON_ROBOTICS_FILES})

target_include_directories(common_robotics_utilities SYSTEM PUBLIC ${COMMON_ROBOTICS_UTILITIES_DIR}/include)

target_link_libraries(common_robotics_utilities PRIVATE
        Eigen3::Eigen
)

set_target_properties(common_robotics_utilities PROPERTIES FOLDER "ThirdParty" POSITION_INDEPENDENT_CODE ON)

# conex
set(CONEX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/conex")
file(GLOB CONEX_FILES ${CONEX_DIR}/conex/*.cc)

add_library(conex STATIC ${CONEX_FILES})

target_include_directories(conex SYSTEM PUBLIC ${CONEX_DIR})

target_link_libraries(conex PRIVATE
        Eigen3::Eigen
)

set_target_properties(conex PROPERTIES FOLDER "ThirdParty" POSITION_INDEPENDENT_CODE ON)
