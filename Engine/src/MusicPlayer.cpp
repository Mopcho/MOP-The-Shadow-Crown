#include "mopengine/MusicPlayer.hpp"

MusicPlayer::MusicPlayer(MusicOptions options): m_autoplay(options.autoplay), m_shuffle(options.shuffle)
{
}

MusicPlayer::~MusicPlayer()
{
    for (auto& it : m_musicStreams)
    {
        UnloadMusicStream(it.music);
    }
}

void MusicPlayer::AddMusicStream(const char* path, const char* name)
{
    Music music = LoadMusicStream(path);
    music.looping = false;

    MusicData musicData;
    musicData.music = music;
    musicData.name = name;
    musicData.path = path;

    m_musicStreams.emplace_back(musicData);
}

[[nodiscard]] int MusicPlayer::GetRandomMusicIdx() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_musicStreams.size() - 1);
    return dist(gen);
}

MusicPlayer::MusicData MusicPlayer::GetRandomMusic()
{
    int randomNum = GetRandomMusicIdx();
    return m_musicStreams[randomNum];
}

std::optional<MusicPlayer::MusicData> MusicPlayer::GetCurrentSelectedMusic()
{
    if (m_currentMusicIdx >= m_musicStreams.size())
    {
        return std::nullopt;
    }
    return m_musicStreams.at(m_currentMusicIdx);
}

void MusicPlayer::PlayRandom()
{
    int randomIdx = GetRandomMusicIdx();
    PlayIdx(randomIdx);
}

void MusicPlayer::PlayIdx(int index)
{
    m_currentMusicIdx = index;
    PlayMusicStream(m_musicStreams[m_currentMusicIdx].music);
}

void MusicPlayer::Autoplay()
{
    if (m_shuffle)
    {
        PlayRandom();
    }
    else
    {
        PlayNextInQueue();
    }
}

void MusicPlayer::PlayNextInQueue()
{
    if (m_currentMusicIdx + 1 >= m_musicStreams.size())
    {
        if (!m_musicStreams.empty())
        {
            PlayIdx(0);
        }
    }
}

void MusicPlayer::Process()
{
    if (auto currentMusic = GetCurrentSelectedMusic())
    {
        UpdateMusicStream(currentMusic->music);
        bool isPlaying = IsMusicStreamPlaying(currentMusic->music);
        if (!isPlaying && m_autoplay)
        {
            Autoplay();
        }
    }
    else if (m_autoplay)
    {
        Autoplay();
    }
}
