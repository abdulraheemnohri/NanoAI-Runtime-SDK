cmake_minimum_required(VERSION 3.10)
project(nanoai_runtime_x)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    core/include
    core/runtime/engine
    core/runtime/executor
    core/runtime/scheduler
    core/runtime/dispatcher
    core/runtime/pipelines
    core/runtime/workers
    core/hardware/discovery
    core/hardware/profiling
    core/hardware/monitoring
    core/hardware/balancing
    core/memory/allocator
    core/memory/cache
    core/memory/compression
    core/security/sandbox
    core/security/permissions
    core/security/verification
    core/telemetry
    core/events
    core/logging
    core/runtime/config
    hal/cpu
    hal/gpu
    hal/npu
    backends/nvidia/cuda
    backends/apple/metal
    backends/qualcomm/hexagon
    models/registry
    models/metadata
    models/converters
    models/optimization
    models/quantization
    formats
    scheduler/hardware_aware
    cluster/discovery
    cluster/node_manager
    cluster/workload_manager
    cluster/synchronization
    cluster/replication
    cluster/networking
    agents/orchestration
    agents/memory
    plugins/api
    plugins/manager
    dashboard/backend/api
)

file(GLOB_RECURSE SOURCES
    "core/*.cpp"
    "hal/*.cpp"
    "backends/*.cpp"
    "models/*.cpp"
    "formats/*.cpp"
    "scheduler/*.cpp"
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
