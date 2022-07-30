#include <cmath>
#include "score_zone.hpp"
#include "game.hpp"
#include "random.hpp"
#include "utils.hpp"
#include "ball.hpp"
#include "paddle.hpp"

ScoreZone::ScoreZone(glm::vec2 pos, glm::vec2 size, int team)
    : Entity::Entity(pos, size) {
    this->team = team;
}
ScoreZone::~ScoreZone() {}
void ScoreZone::step(Game& game) {}
void ScoreZone::collide(Game& game, Entity* entity) {
    // Paddle* maybe_paddle = static_cast<Paddle*>(entity);
    // if (maybe_paddle) {
    //     std::cout << "it was a paddle" << std::endl;
    // }
    Ball* ball = dynamic_cast<Ball*>(entity);
    if (ball) {
        ball->set_inactive(game);
        if (this->team == 0) {
            game.player_score += 1;
        }
        else if (this->team == 1) {
            game.enemy_score += 1;
        }
        entity->set_inactive(game);


        float pan = entity->pos.x / float(game.graphics->width);
        if (this->team == 0) {
            game.audio->sound_play_at(0, pan, 0.0);
        }
        else {
            game.audio->sound_play_at(1, pan, 0.0);
        }

        glm::vec2 dir = this->get_center() - game.camera->get_center();
        glm::vec2 f = -dir * 200.0f;
        game.camera->add_force(f);
    }
    // play a bonk sound of course
}