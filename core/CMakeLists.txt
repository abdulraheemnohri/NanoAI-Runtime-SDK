cmake_minimum_required(VERSION 3.10)
project(nanoai-core VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(nanoai SHARED
    src/runtime.cpp
)

target_include_directories(nanoai PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(nanoai PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Test executable
add_executable(test_runtime src/test_runtime.cpp)
target_link_libraries(test_runtime nanoai)

# Installation logic
install(TARGETS nanoai
    EXPORT NanoAITargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/nanoai DESTINATION include)
