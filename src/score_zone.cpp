#include <cmath>
#include "score_zone.hpp"
#include "game.hpp"
#include "random.hpp"
#include "utils.hpp"
#include "ball.hpp"

ScoreZone::ScoreZone(glm::vec2 pos, glm::vec2 size, int team)
    : Entity::Entity(pos, size) {
    this->team = team;
}
ScoreZone::~ScoreZone() {}
void ScoreZone::step(Game& game) {}
void ScoreZone::collide(Game& game, Entity* entity, int direction) {
    Ball* ball = static_cast<Ball*>(entity);
    // i think paddle is somehow considered as a ball
    if (ball) {
        if (this->team == 0) {
            game.player_score += 1;
        }
        else if (this->team == 1) {
            game.enemy_score += 1;
        }
        entity->set_inactive(game);
        float pan = entity->pos.x / float(game.graphics->width);
        game.audio->sound_play_at(1, pan, 0.0);
    }
    // play a bonk sound of course
}