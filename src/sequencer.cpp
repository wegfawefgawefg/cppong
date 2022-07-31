#include <stdlib.h>

#include "game.hpp"
#include "audio.hpp"
#include "utils.hpp"

Sequencer::Sequencer() {
    // this->beats.push_back(new Beat(14, 19.3, 0.0)); // the horrible song
    // this->set_speed(4.0);
    // this->beats.push_back(new Beat(7, 4.0, 0.0));
    // this->beats.push_back(new Beat(8, 3.0, 0.0));
}
Sequencer::~Sequencer() {}
void Sequencer::step(Game& game) {
    for (auto beat : this->beats) {
        beat->step(game);
    }
}
void Sequencer::set_speed(double speed) {
    this->speed = std::max(0.1, speed);
}

Beat::Beat(int sound, float play_every, float offset) {
    this->sound = sound;
    this->play_every = play_every;
    this->time_since_last_play = offset;
}
Beat::~Beat() {}
void Beat::mute() {
    this->muted = true;
}
void Beat::unmute() {
    this->muted = false;
}
void Beat::step(Game& game) {
    this->time_since_last_play -= float(game.dt) * game.sequencer->speed;
    if (this->time_since_last_play <= 0) {
        float pan = 0.5;
        game.audio->sound_play_at(this->sound, pan, 0.0);
        this->time_since_last_play = this->play_every;
    }
}