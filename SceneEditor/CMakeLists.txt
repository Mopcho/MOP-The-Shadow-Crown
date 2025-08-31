cmake_minimum_required(VERSION 3.31)
project(SceneEditor CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- RayLib ---
if (NOT TARGET raylib)
    set(RAYLIB_VERSION 5.5)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib
        GIT_TAG ${RAYLIB_VERSION}
    )
    set(BUILD_EXAMPLES OFF CACHE INTERNAL "") # Dont build RAYLIB examples
    FetchContent_MakeAvailable(raylib)
endif ()

if (NOT TARGET raygui)
    # --- RayGui ---
    set(RAYGUI_VERSION 4.0)
    FetchContent_Declare(
        raygui
        GIT_REPOSITORY https://github.com/raysan5/raygui
        GIT_TAG ${RAYGUI_VERSION}
    )
    FetchContent_MakeAvailable(raygui)
    add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake ${raygui_BINARY_DIR})
endif ()

# MopDungeon
set(SOURCE_FILES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib raygui mopengine)
target_include_directories(${PROJECT_NAME} PRIVATE include)
