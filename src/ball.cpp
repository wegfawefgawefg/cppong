#include "ball.hpp"

Ball::Ball(glm::vec2 pos, glm::vec2 size) : Entity(pos, size) {}
Ball::Ball(glm::vec2 pos, glm::vec2 size, glm::vec2 vel) : Entity(pos, size, vel) {}
Ball::~Ball() {}
void Ball::step(Game&) {}
void Ball::collide(Entity* entity) {
    this->vel *= -1.1f;
}