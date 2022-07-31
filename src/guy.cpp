#include <stdlib.h>

#include "guy.hpp"
#include "game.hpp"
#include "utils.hpp"

Guy::Guy(glm::vec2 pos) : Entity(pos, glm::vec2(20.0f, 20.0f)) {}
Guy::~Guy() {}
void Guy::step(Game& game) {
    Entity::step_physics(game);
    const float width = game.graphics->dims.x;
    const float height = game.graphics->dims.y;

    // // bouncing
    bool bounce = false;
    if (this->pos.x < 0) {
        this->pos.x = 0;
        this->vel.x = 0.0;
        bounce = true;
    }
    else if (get_br().x > width) {
        this->pos.x = width - this->size.x - 1;
        this->vel.x = 0.0;
    }
    if (this->pos.y < 0) {
        this->pos.y = 0;
        this->vel.y = 0.0;
        bounce = true;
    }
    else if (get_br().y > height) {
        this->pos.y = height - this->size.y - 1;
        this->vel.y = 0.0;
    }

    if (bounce) {
        float pan = this->pos.x / float(game.graphics->dims.x);
        game.audio->sound_play_at(2, pan, 0.0);
    }

    // quick bounds check
    float too_far = 10.0;
    if (this->pos.x < -too_far ||
        this->pos.x > game.graphics->dims.x + too_far ||
        this->pos.y < -too_far ||
        this->pos.y > game.graphics->dims.y + too_far
    ) {
        this->set_inactive();
    }
}

void Guy::collide(Game& game, Entity* entity) {}
