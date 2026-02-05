cmake_minimum_required(VERSION 3.22.1)
project(viluaos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get the project root directory (4 levels up from CMakeLists.txt)
get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../.." ABSOLUTE)

# Android NDK configuration
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -fvisibility=hidden")

# Include directories
include_directories(
    ${PROJECT_ROOT}/include
)

# JNI bridge - simple minimal library
set(JNI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/native-lib.cpp
)

# Create shared library
add_library(viluaos SHARED 
    ${JNI_SOURCES}
)

# Link libraries
target_link_libraries(viluaos
    android
    log
)

# Set output name
set_target_properties(viluaos PROPERTIES
    OUTPUT_NAME "viluaos"
)
