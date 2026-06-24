cmake_minimum_required(VERSION 3.10)
project(nanoai_ultimate)
set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

include_directories(core/include core/hardware core/scheduler core/agents core/telemetry core/runtime core/plugins core/memory core/security cluster/node cluster/discovery cluster/synchronization models/registry)
file(GLOB_RECURSE SOURCES "core/*.cpp" "cluster/*.cpp" "models/registry/*.cpp")
add_library(nanoai SHARED ${SOURCES})
add_executable(nanoai_ultimate examples/launch_demo_ultimate.cpp)
target_link_libraries(nanoai_ultimate nanoai pthread)

target_include_directories(nanoai
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
    TARGETS nanoai nanoai_ultimate
    EXPORT NanoAITargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/include/nanoai
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT NanoAITargets
    FILE NanoAITargets.cmake
    NAMESPACE NanoAI::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NanoAI
)
