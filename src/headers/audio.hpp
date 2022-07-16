#pragma once

#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL_mixer.h>

// this is c way, please dont use this
enum SOUND
{
    SOUND_FIREWORKS_SHOOT,
    SOUND_FIREWORKS_EXPLOSION,
    SOUND_NUM_SOUNDS, // must be last
};

class Audio
{
public:
    std::vector<Mix_Chunk *> sounds;

    Audio();
    ~Audio();
    void audio_pan(int channel, float pan);
    void sound_play_at(int sound, float x, float y);
    int sound_play(int sound);
};

#endif
