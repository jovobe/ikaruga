#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Sound.hpp"

using std::string;

namespace ikaruga
{
    int Sound::NEXT_CHANNEL = 1;

    Sound::Sound(string filename, int type)
    {
        m_channel = -1;
        //NEXT_CHANNEL++;
        m_soundFile = filename;
        m_type = type;
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }
    }

    void Sound::play(int volume)
    {
        if (m_type == SoundType::SONG && !Mix_PlayingMusic())
        {
            Mix_Music* song = Mix_LoadMUS(m_soundFile.c_str());

            if (song == NULL)
            {
                std::cerr << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_VolumeMusic(volume);
            Mix_PlayMusic(song, 0);
        }
        else if (m_type == SoundType::SOUND)
        {
            Mix_Chunk* sound = Mix_LoadWAV(m_soundFile.c_str());

            if (sound == NULL)
            {
                std::cerr << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_Volume(m_channel, volume);
            Mix_PlayChannel(m_channel, sound, 0);
            Mix_FadeOutChannel(m_channel, sound->alen / 9 * 10);
        }
    }

    void Sound::play(int volume, int fadeout)
    {
        if (m_type == SoundType::SONG && !Mix_PlayingMusic())
        {
            Mix_Music* song = Mix_LoadMUS(m_soundFile.c_str());

            if (song == NULL)
            {
                std::cerr << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_VolumeMusic(volume);
            Mix_PlayMusic(song, 0);
            Mix_FadeOutMusic(fadeout);
        }
        else if (m_type == SoundType::SOUND)
        {
            Mix_Chunk* sound = Mix_LoadWAV(m_soundFile.c_str());

            if (sound == NULL)
            {
                std::cerr << "Couldnt open " + m_soundFile + "\n";
            }
            Mix_Volume(m_channel, volume);
            Mix_PlayChannel(m_channel, sound, 0);
            Mix_FadeOutChannel(m_channel, fadeout);
        }
    }

    void Sound::stop()
    {
        Mix_HaltMusic();
    }

    void Sound::pause()
    {
        Mix_PausedMusic();
    }

    void Sound::resume()
    {
        if (Mix_PausedMusic() == 1)
        {
            Mix_ResumeMusic();
        }
    }
} /* namespace ikaruga */
