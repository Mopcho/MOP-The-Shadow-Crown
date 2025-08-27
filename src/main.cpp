#include <iostream>
#include <__msvc_ostream.hpp>

#include "MusicPlayer.hpp"
#include "raylib.h"
#include "Scene.hpp"
#include "../include/KinematicBody2D.hpp"
#include "../include/SpriteModule.hpp"
#include "../include/GameObject.hpp"

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "MopDungeon");

    InitAudioDevice();
    MusicPlayer peacefulMP(true, true);
    MusicPlayer fightMP(true, true);
    fightMP.AddMusicStream("res/sound/ost/DragonCastle.mp3", "dragon-castle");
    fightMP.AddMusicStream("res/sound/ost/IntoTheWilds.mp3", "into-the-wilds");
    peacefulMP.AddMusicStream("res/sound/ost/PerituneMistyHollow.mp3", "peritune-misty-hollow");
    peacefulMP.AddMusicStream("res/sound/ost/TheBardsTale.mp3", "the-bards-tale");
    // bgMusicPlayer.AddMusicStream("res/sound/ost/bruh.mp3", "the-bards-tale", "idk"); // 1 second track easy for testing

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

        BeginDrawing();
        ClearBackground(SKYBLUE);
        scene.DrawObjects();
        peacefulMP.Update();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}