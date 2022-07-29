#include <cmath>
#include "paddle.hpp"
#include "game.hpp"
#include "random.hpp"
#include "utils.hpp"

Paddle::Paddle(glm::vec2 pos, glm::vec2 size) : Entity(pos, size) {
    this->target = pos;
}
Paddle::Paddle(glm::vec2 pos, glm::vec2 size, glm::vec2 vel) : Entity(pos, size, vel) {}
Paddle::~Paddle() {}
void Paddle::step(Game& game) {
    // std::cout << "position: ";
    // print_glm_vec2(this->pos);
    // std::cout << ", ";
    // std::cout << "target: ";
    // print_glm_vec2(this->target);
    // std::cout << std::endl;
    // float dif = std::abs(this->target.x - this->pos.x);
    // std::cout << "dif: " << dif << std::endl;
    float dif = std::abs(this->target.x - this->pos.x);
    if (dif > 10.0) {
        this->vel.x = std::copysign(200.0, this->target.x - this->pos.x);
    }
    else {
        this->target.x = frand(0, float(game.graphics->width) - this->size.x);
    }
    Entity::step_physics(game);
}
void Paddle::collide(Game& game, Entity* entity) {
    // play a bonk sound of course
    std::cout << "paddle collision" << std::endl;
}