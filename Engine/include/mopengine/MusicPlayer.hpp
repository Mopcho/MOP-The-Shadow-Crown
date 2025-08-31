#ifndef BGMUSICPLAYER_HPP
#define BGMUSICPLAYER_HPP

#include <optional>
#include <random>
#include <string>

#include "Constants.hpp"
#include "raylib.h"

class MOPENGINE_API MusicPlayer
{
public:
    bool m_autoplay;
    bool m_shuffle;

    struct MusicData
    {
        Music music;
        std::string name;
        std::string path;
    };

    struct MusicOptions
    {
        bool autoplay;
        bool shuffle;
    };

    MusicPlayer(MusicOptions options);
    ~MusicPlayer();
    void AddMusicStream(const char* path, const char* name);
    int GetRandomMusicIdx() const;
    MusicData GetRandomMusic();
    std::optional<MusicData> GetCurrentSelectedMusic();
    void PlayRandom();
    void PlayIdx(int index);
    void Autoplay();
    void PlayNextInQueue();
    void Process();

private:
    std::vector<MusicData> m_musicStreams;
    int m_currentMusicIdx;
};

#endif //BGMUSICPLAYER_HPP
