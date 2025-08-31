#include <iostream>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Scene Editor");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(SKYBLUE);
            if (GuiButton({ 50, 200, 100, 50 }, "Load Scene"))
            {

            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

