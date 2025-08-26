#include <iostream>
#include <__msvc_ostream.hpp>

#include "raylib.h"
#include "Scene.hpp"
#include "../include/KinematicBody2D.hpp"
#include "../include/SpriteModule.hpp"
#include "../include/GameObject.hpp"

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MopDungeon");

    SpriteModule idleSpriteModule("res/samurai/Sprites/IDLE.png", 10);
    SpriteModule runSpriteModule("res/samurai/Sprites/RUN.png", 16);
    KinematicBody2D player({ (float)screenWidth/2, (float)screenHeight/2 });
    player.AddSpriteModule("idle", &idleSpriteModule);
    player.AddSpriteModule("run", &runSpriteModule);
    player.SetPlaySpriteModule("idle");
    player.setScaleSize({2.0f, 2.0f});

    SetTargetFPS(60);

    Scene scene;
    scene.AddObject(&player);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_A))
        {
            player.m_pos.x -= 2.0f;
            player.m_flipH = true;
            player.SetPlaySpriteModule("run");
        } else if (IsKeyDown(KEY_D))
        {
            player.m_pos.x += 2.0f;
            player.m_flipH = false;
            player.SetPlaySpriteModule("run");
        } else
        {
            player.SetPlaySpriteModule("idle");
        }

        if (IsKeyDown(MOUSE_BUTTON_LEFT))
        {

        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        scene.DrawObjects();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}