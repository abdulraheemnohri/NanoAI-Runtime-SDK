cmake_minimum_required(VERSION 3.10)
project(nanoai)

set(CMAKE_CXX_STANDARD 17)

include_directories(include src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(nanoai SHARED ${SOURCES})

# Tests
add_executable(hw_test tests/test_hardware_exposure.cpp)
target_link_libraries(hw_test nanoai)

add_executable(comprehensive_test tests/test_comprehensive_routing.cpp)
target_link_libraries(comprehensive_test nanoai)
