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
    ${PROJECT_ROOT}/src
    ${PROJECT_ROOT}/include
    ${PROJECT_ROOT}/include/imgui
)

# Source files from the original project
set(GAME_SOURCES
    ${PROJECT_ROOT}/src/ESP.cpp
    ${PROJECT_ROOT}/src/GUI.cpp
    ${PROJECT_ROOT}/src/Player.cpp
    ${PROJECT_ROOT}/src/Game.cpp
    ${PROJECT_ROOT}/src/Drawing.cpp
    ${PROJECT_ROOT}/src/Aimbot.cpp
    ${PROJECT_ROOT}/src/Config.cpp
)

# ImGui sources
set(IMGUI_SOURCES
    ${PROJECT_ROOT}/src/imgui.cpp
    ${PROJECT_ROOT}/src/imgui_draw.cpp
    ${PROJECT_ROOT}/src/imgui_widgets.cpp
    ${PROJECT_ROOT}/src/imgui_tables.cpp
    ${PROJECT_ROOT}/src/imgui_impl_opengl3.cpp
    ${PROJECT_ROOT}/src/imgui_impl_android.cpp
)

# JNI bridge
set(JNI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/native-lib.cpp
)

# Create shared library
add_library(viluaos SHARED 
    ${GAME_SOURCES}
    ${IMGUI_SOURCES}
    ${JNI_SOURCES}
)

# Link libraries
target_link_libraries(viluaos
    android
    log
    EGL
    GLESv2
    GLESv3
)

# Set output name
set_target_properties(viluaos PROPERTIES
    OUTPUT_NAME "viluaos"
)
