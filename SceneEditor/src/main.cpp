#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include <functional>
#include "Scene.hpp"

std::vector<Scene> scenes;

int main()
{
    unsigned int selectedScene = 0;
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Scene Editor");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        scenes[selectedScene].Process();
        BeginDrawing();
            ClearBackground(SKYBLUE);
            scenes[selectedScene].Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
