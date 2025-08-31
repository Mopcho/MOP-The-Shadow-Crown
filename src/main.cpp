#include <iostream>

#include "raylib.h"
#include "Player.hpp"
#include <mopengine/MusicPlayer.hpp>
#include <mopengine/Animation.hpp>
#include <mopengine/Scene.hpp>

#include "mopengine/AnimationPlayer.hpp"
#include "mopengine/Constants.hpp"
#include "mopengine/TileSet.hpp"

void ProcessMovement(Player & player);

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "MopDungeon");
    InitAudioDevice();
    SetTargetFPS(FPS);

    MusicPlayer peacefulMP(MusicPlayer::MusicOptions{true, true});
    MusicPlayer fightMP(MusicPlayer::MusicOptions{true, true});
    fightMP.AddMusicStream("res/sound/ost/DragonCastle.mp3", "dragon-castle");
    fightMP.AddMusicStream("res/sound/ost/IntoTheWilds.mp3", "into-the-wilds");
    peacefulMP.AddMusicStream("res/sound/ost/PerituneMistyHollow.mp3", "peritune-misty-hollow");
    peacefulMP.AddMusicStream("res/sound/ost/TheBardsTale.mp3", "the-bards-tale");
    // bgMusicPlayer.AddMusicStream("res/sound/ost/bruh.mp3", "bruh"); // 1 second track easy for testing

    Animation idleAnim("res/Samurai/Sprites/IDLE.png", 10);
    Animation runAnim("res/Samurai/Sprites/RUN.png", 16);
    Animation runAttackAnim("res/Samurai/Sprites/RUN ATTACK.png", 3, 8, false);
    Animation attackAnim("res/Samurai/Sprites/ATTACK 2.png", 7, 8, false);

    AnimationPlayer animationPlayer;
    animationPlayer.AddAnimation("idle", &idleAnim);
    animationPlayer.AddAnimation("run", &runAnim);
    animationPlayer.AddAnimation("run-attack", &runAttackAnim);
    animationPlayer.AddAnimation("attack-1", &attackAnim);
    animationPlayer.PlayAnimation("idle");

    Player player({ (float)screenWidth/2, (float)screenHeight/2 });
    player.SetAnimationPlayer(std::move(animationPlayer));
    player.setScaleSize({2.0f, 2.0f});

    TileMap tileMap(256, "res/MossyPack/Mossy Tileset/Mossy - TileSet.png");
    // TODO: SPecify columns
    int grid[] = { 0, 1, 1, 2 };
    int gridSize = sizeof(grid) / sizeof(grid[0]);
    SceneTiles sceneTiles(grid, gridSize , screenWidth, screenHeight, &tileMap);

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
            sceneTiles.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ProcessMovement(Player & player)
{
    // Play appropriate animation
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)))
    {
        player.m_animationPlayer.PlayAnimationWhenReady("run-attack");
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        player.m_animationPlayer.PlayAnimationWhenReady("attack-1");
    } else if (IsKeyDown(KEY_D))
    {
        player.m_animationPlayer.PlayAnimationWhenReady("run");
    } else if (IsKeyDown(KEY_A))
    {
        player.m_animationPlayer.PlayAnimationWhenReady("run");
    } else
    {
        player.m_animationPlayer.PlayAnimationWhenReady("idle");
    }

    // Move the player
    if (IsKeyDown(KEY_D))
    {
        player.Move({2.0f, 0.0f});
        player.m_flipH = false;
    } else if (IsKeyDown(KEY_A))
    {
        player.Move({-2.0f, 0.0f});
        player.m_flipH = true;
    }
}