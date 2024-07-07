cmake_minimum_required(VERSION 3.28)
project(MakeDrake)

set(CMAKE_CXX_STANDARD 17)
find_package(Eigen3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(MakeDrake main.cpp)

add_subdirectory(math)
add_subdirectory(math/test)