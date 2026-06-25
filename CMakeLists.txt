cmake_minimum_required(VERSION 3.10)
project(nanoai_runtime_x)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    core/include
    core/runtime
    core/hardware
    core/memory
    core/security
    core/telemetry
    hal
    backends
    models
    cluster
    agents
    plugins
    dashboard/backend/api
)

file(GLOB_RECURSE SOURCES
    "core/*.cpp"
    "hal/*.cpp"
    "backends/*.cpp"
    "models/*.cpp"
    "cluster/*.cpp"
    "agents/*.cpp"
    "plugins/*.cpp"
    "dashboard/backend/*.cpp"
)

add_library(nanoai SHARED ${SOURCES})

if(DEFINED ENV{JAVA_HOME})
  include(FindJNI)
  if(JNI_FOUND)
    target_sources(nanoai PRIVATE sdk/android/jni/nanoai_jni.cpp)
    target_include_directories(nanoai PRIVATE ${JNI_INCLUDE_DIRS})
  endif()
endif()

add_executable(nrx_demo examples/launch_demo_ultimate.cpp)
target_link_libraries(nrx_demo nanoai pthread dl)

add_executable(full_system_test examples/full_system_test.cpp)
target_link_libraries(full_system_test nanoai pthread dl)
