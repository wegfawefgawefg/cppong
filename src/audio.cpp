#include <iostream>
#include <vector>

#include "audio.hpp"

Audio::Audio() {
    std::cout << "Audio created" << std::endl;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    int num_channels = Mix_AllocateChannels(2048);
    printf("num_channels: %d\n", num_channels);

    // vector of strings
    std::vector<std::string> sound_files = {
        "assets/sounds/player_score.wav",
        "assets/sounds/enemy_score.wav",
        "assets/sounds/ball_wall_bounce.wav",
        "assets/sounds/ball_ball_bounce_1.wav",
        "assets/sounds/ball_ball_bounce_2.wav",
        "assets/sounds/ball_ball_bounce_3.wav",
        "assets/sounds/ball_ball_bounce_4.wav",
        "assets/sounds/fireworks_shoot.wav",
        "assets/sounds/fireworks_explosion.wav",
    };

    // loop through vector and load each file
    for (auto& sound_file : sound_files) {
        Mix_Chunk* sound = Mix_LoadWAV(sound_file.c_str());
        if (sound == NULL) {
            printf("Mix_LoadWAV: %s\n", Mix_GetError());
            return;
        }
        sounds.push_back(sound);
    }

    // Mix_Chunk *fireworks_shoot = *Mix_LoadWAV("./assets/sounds/fireworks_shoot.wav");
    // Mix_Chunk *fireworks_explosion = *Mix_LoadWAV("./assets/sounds/fireworks_explosion.wav");
    // sounds.push_back();
}

Audio::~Audio() {
    std::cout << "Audio destroyed" << std::endl;
    for (auto& sound : sounds) {
        Mix_FreeChunk(sound);
    }
    Mix_HaltChannel(-1);
    Mix_CloseAudio();
    Mix_Quit();
}

void Audio::audio_pan(int channel, float pan) {
    pan = std::min(std::max(pan, 0.0f), 1.0f);
    int pan_int = int(pan * 255.0);
    Mix_SetPanning(channel, 255 - pan_int, pan_int);
};

void Audio::sound_play_at(int sound, float x, float y) {
    //x in range 0 to 1
    int channel = Mix_PlayChannel(-1, sounds[sound], 0);
    audio_pan(channel, x);
};

int Audio::sound_play(int sound) {
    return Mix_PlayChannel(-1, sounds[sound], 0);
};
