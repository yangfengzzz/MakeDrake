cmake_minimum_required(VERSION 3.28)
project(MakeDrake)

set(CMAKE_CXX_STANDARD 20)
find_package(Eigen3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
set(GFLAGS_USE_TARGET_NAMESPACE ON)
find_package(gflags CONFIG REQUIRED)

add_executable(MakeDrake main.cpp)

add_subdirectory(common)
add_subdirectory(math)
add_subdirectory(math/test)