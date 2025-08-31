cmake_minimum_required(VERSION 3.31)
project(mopengine VERSION 0.1.0 DESCRIPTION "A cool game engine" LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

include(FetchContent)
include(GNUInstallDirs)

set(MOPENGINE_SOURCES src/Animation.cpp src/Button.cpp src/KinematicBody2D.cpp src/MusicPlayer.cpp src/Scene.cpp src/TileSet.cpp src/AnimationPlayer.cpp)
set(MOPENGINE_HEADERS
    include/mopengine/Animation.hpp
    include/mopengine/Button.hpp
    include/mopengine/KinematicBody2D.hpp
    include/mopengine/MusicPlayer.hpp
    include/mopengine/Scene.hpp
    include/mopengine/TileSet.hpp
    include/mopengine/AnimationPlayer.hpp
)

add_library(${PROJECT_NAME}
    ${MOPENGINE_SOURCES}
)
target_compile_definitions(${PROJECT_NAME} PRIVATE MOPENGINE_MAKEDLL)

set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "") # Dont build RAYLIB examples
FetchContent_MakeAvailable(raylib)

# --- RayGui ---
set(RAYGUI_VERSION 4.0)
FetchContent_Declare(
    raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui
    GIT_TAG ${RAYGUI_VERSION}
)
FetchContent_MakeAvailable(raygui)
add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake ${raygui_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib raygui)
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${MOPENGINE_HEADERS})
install(DIRECTORY include/mopengine DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
target_include_directories(${PROJECT_NAME} PUBLIC include)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
configure_file(engine.pc.in engine.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/engine.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
