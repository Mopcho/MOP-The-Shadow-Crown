cmake_minimum_required(VERSION 3.31)
project(MopDungeon CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

# --- RayLib ---
set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "") # Dont build RAYLIB examples
FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES src/main.cpp)

add_executable(MopDungeon ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE include)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMENT "Copying resource files..."
)
add_dependencies(${PROJECT_NAME} copy_resources)

