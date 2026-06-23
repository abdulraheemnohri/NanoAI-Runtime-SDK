cmake_minimum_required(VERSION 3.10)
project(nanoai-core VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NANOAI_SOURCES
    src/runtime.cpp
    src/acceleration/selector.cpp
    src/acceleration/cpu_info.cpp
    src/conversion/converter.cpp
    src/networking/network_manager.cpp
)

# Check if JNI is available (for Android/Java SDKs)
find_package(JNI)
if (JNI_FOUND)
    message(STATUS "JNI found, building JNI bridge")
    include_directories(${JNI_INCLUDE_DIRS})
    list(APPEND NANOAI_SOURCES ../sdks/android/jni/nanoai_jni.cpp)
endif()

add_library(nanoai SHARED
    ${NANOAI_SOURCES}
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
