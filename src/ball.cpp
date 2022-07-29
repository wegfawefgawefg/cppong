#include "ball.hpp"
#include "paddle.hpp"
#include "game.hpp"
#include "utils.hpp"

Ball::Ball(glm::vec2 pos, glm::vec2 size) : Entity(pos, size) {}
Ball::Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 vel) : Entity(pos, size, vel) {}
Ball::~Ball() {}
void Ball::step(Game& game) {
    Entity::step_physics(game);
    // bounce of walls experimentally
    const float width = game.graphics->window_width;
    const float height = game.graphics->window_height;

    // // bouncing
    bool bounce = false;
    if (pos.x < 0) {
        pos.x = 0;
        vel.x *= -1;
        bounce = true;
    }
    else if (get_br().x > width) {
        vel.x *= -1;
        bounce = true;
    }

    if (pos.y < 0) {
        pos.y = 0;
        vel.y *= -1;
        bounce = true;
    }
    else if (get_br().y > height) {
        vel.y *= -1;
        bounce = true;
    }

    if (bounce) {
        float pan = this->pos.x / float(game.graphics->width);
        game.audio->sound_play_at(3, pan, 0.0);
    }
}
void Ball::collide(Game& game, Entity* entity) {
    if (dynamic_cast<Ball*>(entity)) {
        // std::cout << "ball col: " << this->id << std::endl;
        Entity::bounce_away_from(entity);
        float pan = entity->pos.x / float(game.graphics->width);
        game.audio->sound_play_at(2, pan, 0.0);
    }
    if (static_cast<Paddle*>(entity)) {
        // if (direction == Direction::Bottom || direction == Direction::Top) {
        //     this->vel.y *= -1;
        // }
        // else if (direction == Direction::Left || direction == Direction::Right) {
        //     this->vel.x *= -1;
        // }
        // float bounce_impulse = 10000.0;
        // glm::vec2 a_c = this->get_center();
        // glm::vec2 b_c = entity->get_center();
        // glm::vec2 dif = a_c - b_c;
        // this->acc += glm::normalize(dif) * bounce_impulse;
    }
    // this->acc += bounce_impulse * dif;
    // this->vel.x = std::min(Ball::MAX_SPEED, this->vel.x);
    // this->vel.y = std::min(Ball::MAX_SPEED, this->vel.y);
    // this->vel = glm::normalize(this->vel) * Ball::MAX_SPEED;

    // if (direction == Direction::Top) {
    //     this->vel.y = 0.0;
    //     this->acc.y -= bounce_impulse;
    // }
    // else if (direction == Direction::Bottom) {
    //     this->vel.y = 0.0;
    //     this->acc.y += bounce_impulse;
    // }
    // else if (direction == Direction::Left) {
    //     this->vel.x = 0.0;
    //     this->acc.x -= bounce_impulse;
    // }
    // else if (direction == Direction::Right) {
    //     this->vel.x = 0.0;
    //     this->acc.x += bounce_impulse;
    // }
}