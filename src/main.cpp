#include "raylib.h"
#include <engine/MusicPlayer.hpp>
#include <engine/KinematicBody2D.hpp>
#include <engine/Scene.hpp>

#include "game/Player.hpp"

void ProcessMovement(Player & player);

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "MopDungeon");
    InitAudioDevice();
    SetTargetFPS(FPS);

    MusicPlayer peacefulMP(MusicPlayer::Options{true, true});
    MusicPlayer fightMP(MusicPlayer::Options{true, true});
    fightMP.AddMusicStream("res/sound/ost/DragonCastle.mp3", "dragon-castle");
    fightMP.AddMusicStream("res/sound/ost/IntoTheWilds.mp3", "into-the-wilds");
    peacefulMP.AddMusicStream("res/sound/ost/PerituneMistyHollow.mp3", "peritune-misty-hollow");
    peacefulMP.AddMusicStream("res/sound/ost/TheBardsTale.mp3", "the-bards-tale");
    // bgMusicPlayer.AddMusicStream("res/sound/ost/bruh.mp3", "the-bards-tale"); // 1 second track easy for testing

    Animation idleSpriteModule("res/Samurai/Sprites/IDLE.png", 10);
    Animation runSpriteModule("res/Samurai/Sprites/RUN.png", 16);
    Animation attackTwoSpriteModule("res/Samurai/Sprites/ATTACK 2.png", 7, 8, false);

    Player player({ (float)screenWidth/2, (float)screenHeight/2 });
    player.AddAnimation("idle", &idleSpriteModule);
    player.AddAnimation("run", &runSpriteModule);
    player.AddAnimation("attack-2", &attackTwoSpriteModule);
    player.PlayAnimation("idle");
    player.setScaleSize({2.0f, 2.0f});

    Scene scene;
    scene.AddObject(&player);

    while (!WindowShouldClose())
    {
        ProcessMovement(player);
        scene.ProcessObjects();
        peacefulMP.Process();

        BeginDrawing();
            ClearBackground(SKYBLUE);
            scene.DrawObjects();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ProcessMovement(Player & player)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        player.PlayAnimation("attack-2");
    } else if (IsKeyDown(KEY_D))
    {
        player.m_pos.x += 2.0f;
        player.m_flipH = false;
        player.PlayAnimationWhenReady("run");
    } else if (IsKeyDown(KEY_A))
    {
        player.m_pos.x -= 2.0f;
        player.m_flipH = true;
        player.PlayAnimationWhenReady("run");
    } else
    {
        player.PlayAnimationWhenReady("idle");
    }
}