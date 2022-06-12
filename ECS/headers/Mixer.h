//
// Created by Kyle Dougan on 6/8/22.
//

#pragma once

#include <map>
#include <SDL_mixer.h>

class Mixer
{
public:
    Mixer();

    ~Mixer();

    void playMusic(const std::string &name);

    void playSound(const std::string &name);

    void playSound(const std::string &name, float pan);

    void playSound(const std::string &name, float pan, int loops);

    void stopMusic();

    void stopSound();


private:
    int audio_rate = 22050;
    Uint16 audio_format = MIX_DEFAULT_FORMAT;
    int audio_channels = 2;
    int audio_buffers = 4096;

    std::string assetPath = "assets/";

    std::map<std::string, Mix_Music *> musicMap;
    std::map<std::string, Mix_Chunk *> soundMap;

    Mix_Music *currentMusic;
    Mix_Chunk *currentSound;

};
