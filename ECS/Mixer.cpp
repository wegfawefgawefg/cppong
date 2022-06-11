//
// Created by Kyle Dougan on 6/8/22.
//
#include <iostream>
#include "Mixer.h"
#include "Utilities.h"


Mixer::Mixer()
{
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        throw std::runtime_error("SDL_mixer could not initialize!");
    }
    Mix_AllocateChannels(16);
    musicMap = std::map<std::string, Mix_Music *>();
    soundMap = std::map<std::string, Mix_Chunk *>();
    currentMusic = nullptr;
    currentSound = nullptr;

    // load assets in the assetPath/music folder
    std::string musicPath = assetPath + "music/";
    std::vector<std::string> musicFiles = getFilesInDirectory(musicPath);

    for (auto &file: musicFiles)
    {
        std::string filePath = musicPath + file;
        // 24-bit samples
        Mix_Music *music = Mix_LoadMUS(filePath.c_str());
        std::string fileName = file.substr(0, file.find_last_of('.'));
        if (music == nullptr)
        {
            std::cout << "Failed to load music file: " << filePath << " SDL_mixer Error: " << Mix_GetError()
                      << std::endl;
            throw std::runtime_error("Failed to load music file: " + filePath);
        }
        musicMap[fileName] = music;
    }

    std::string soundPath = assetPath + "sounds/";
    std::vector<std::string> soundFiles = getFilesInDirectory(soundPath);
    for (auto &file: soundFiles)
    {
        std::string filePath = soundPath + file;
        std::string fileName = file.substr(0, file.find_last_of('.'));
        Mix_Chunk *sound = Mix_LoadWAV(filePath.c_str());
        if (sound == nullptr)
        {
            std::cout << "Failed to load sound file: " << filePath << " SDL_mixer Error: " << Mix_GetError()
                      << std::endl;
            throw std::runtime_error("Failed to load sound file: " + filePath);
        }
        soundMap[fileName] = sound;
    }
}


Mixer::~Mixer()
{
    for (auto &music: musicMap)
    {
        Mix_FreeMusic(music.second);
    }
    for (auto &sound: soundMap)
    {
        Mix_FreeChunk(sound.second);
    }
    Mix_CloseAudio();
}


void Mixer::playMusic(const std::string &name)
{
    if (currentMusic != nullptr)
    {
        Mix_HaltMusic();
    }
    currentMusic = musicMap[name];
    Mix_PlayMusic(currentMusic, -1);
}


void Mixer::playSound(const std::string &name)
{
    playSound(name, 0, 0);
}

void Mixer::playSound(const std::string &name, float pan)
{
    playSound(name, pan, 0);
}

void Mixer::playSound(const std::string &name, float pan, int loops)
{
    currentSound = soundMap[name];
    int channel = Mix_PlayChannel(-1, currentSound, loops);
    if (pan == 0)
        Mix_SetPanning(channel, 255, 255);
    else
        Mix_SetPanning(channel, (Uint8) (255 - pan * 255), (Uint8) (pan * 255));
}


void Mixer::stopMusic()
{
    Mix_HaltMusic();
}


void Mixer::stopSound()
{
    Mix_HaltChannel(-1);
}
