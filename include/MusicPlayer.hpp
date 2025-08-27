#ifndef BGMUSICPLAYER_HPP
#define BGMUSICPLAYER_HPP

#include <optional>
#include <random>
#include <string>
#include <unordered_map>

#include "raylib.h"

class MusicPlayer
{
public:
    bool m_autoplay;
    bool m_shuffle;

    struct MusicData
    {
        Music music;
        std::string vibe;
        std::string name;
        std::string path;
    };

    MusicPlayer(bool autoplay, bool shuffle): m_autoplay(autoplay), m_shuffle(shuffle)
    {
    }

    ~MusicPlayer()
    {
        for (auto& it: m_musicStreams)
        {
            UnloadMusicStream(it.music);
        }
    }

    void AddMusicStream(const std::string & path, const std::string & name, const std::string & vibe)
    {
        Music music = LoadMusicStream(path.c_str());
        music.looping = false;

        MusicData musicData;
        musicData.music = music;
        musicData.vibe = vibe;
        musicData.name = name;
        musicData.path = path;

        m_musicStreams.emplace_back(musicData);
    }

    int GetRandomMusicIdx()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, m_musicStreams.size() - 1);
        return dist(gen);
    }

    MusicData GetRandomMusic()
    {
        int randomNum = GetRandomMusicIdx();
        return m_musicStreams[randomNum];
    }

    std::optional<MusicData> GetCurrentSelectedMusic()
    {
        if (m_currentMusicIdx >= m_musicStreams.size())
        {
            return std::nullopt;
        }
        return m_musicStreams.at(m_currentMusicIdx);
    }

    void PlayRandom()
    {
        int randomIdx = GetRandomMusicIdx();
        PlayIdx(randomIdx);
    }

    void PlayIdx(int index)
    {
        m_currentMusicIdx = index;
        PlayMusicStream(m_musicStreams[m_currentMusicIdx].music);
    }

    void Autoplay()
    {
        if (m_shuffle)
        {
            PlayRandom();
        } else
        {
            PlayNextInQueue();
        }
    }

    void PlayNextInQueue()
    {
        if (m_currentMusicIdx + 1 >= m_musicStreams.size())
        {
            if (!m_musicStreams.empty())
            {
                PlayIdx(0);
            }
        }
    }

    void Update()
    {
        if (auto currentMusic = GetCurrentSelectedMusic())
        {
            UpdateMusicStream(currentMusic->music);
            bool isPlaying = IsMusicStreamPlaying(currentMusic->music);
            if (!isPlaying && m_autoplay)
            {
                Autoplay();
            }
        } else if (m_autoplay)
        {
            Autoplay();
        }
    }

private:
    std::vector<MusicData> m_musicStreams;
    int m_currentMusicIdx;
};

#endif //BGMUSICPLAYER_HPP
