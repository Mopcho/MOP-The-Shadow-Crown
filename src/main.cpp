#include <iostream>
#include <__msvc_ostream.hpp>

#include "raylib.h"
#include "../include/RigidBody2D.hpp"
#include "../include/SpriteModule.hpp"

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MopDungeon");

    SpriteModule idleSpriteModule("res/samurai/Sprites/IDLE.png", 10);
    SpriteModule runSpriteModule("res/samurai/Sprites/RUN.png", 16);
    RigidBody2D rbPlayer({ (float)screenWidth/2, (float)screenHeight/2 }, &idleSpriteModule);

    SetTargetFPS(60);

    rbPlayer.On("run", [&rbPlayer, &runSpriteModule]()
    {
        rbPlayer.setSpriteModule(&runSpriteModule);
    });

    rbPlayer.On("idle", [&rbPlayer, &idleSpriteModule]()
    {
        rbPlayer.setSpriteModule(&idleSpriteModule);
    });

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_A))
        {
            rbPlayer.m_pos.x -= 2.0f;
            rbPlayer.m_flipH = true;
        } else if (IsKeyDown(KEY_D))
        {
            rbPlayer.m_pos.x += 2.0f;
            rbPlayer.m_flipH = false;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        rbPlayer.Update();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}