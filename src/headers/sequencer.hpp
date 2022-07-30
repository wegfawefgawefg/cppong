#pragma once

#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <glm/glm.hpp>

class Beat {
public:
    int sound = 0;
    float play_every = 0;
    float time_since_last_play = 0;
    bool muted = true;

    Beat(int sound, float play_every, float offset);
    ~Beat();
    void step(Game& game);
    void mute();
    void unmute();
};

class Game;
class Sequencer {
public:
    float speed = 1.0;
    std::vector<Beat*> beats;

    Sequencer();
    ~Sequencer();
    void step(Game& game);
    void set_speed(double speed);
};
#endif