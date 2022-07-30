#include <iostream>
#include <random>

#include "camera.hpp"

Camera::Camera(glm::vec2 pos, glm::vec2 size) {
    this->pos = pos;
    this->size = size;
    this->vel = glm::vec2(0.0, 0.0);
    this->acc = glm::vec2(0.0, 0.0);
}

Camera::~Camera() {}

void Camera::step(Game& game) {}

glm::vec2 Camera::get_br() {
    return this->pos + this->size;
}

glm::vec2 Camera::get_center() {
    return this->pos + this->size / 2.0f;
}

void Camera::set_center(glm::vec2 p) {
    this->pos = p - this->size / 2.0f;
}

bool Camera::contains_box(glm::vec2 tl, glm::vec2 br) {
    glm::vec2 a_br = this->get_br();

    if (a_br.x < tl.x || this->pos.x > br.x) { return false; }
    if (a_br.y < tl.y || this->pos.y > br.y) { return false; }
    return true;
}

bool Camera::contains(glm::vec2 p) {
    glm::vec2 a_br = this->get_br();

    if (a_br.x < p.x || this->pos.x > p.x) { return false; }
    if (a_br.y < p.y || this->pos.y > p.y) { return false; }
    return true;
}

void Camera::bounce_away_from_position(glm::vec2 p) {
    float bounce_impulse = 40000.0;
    glm::vec2 a_c = this->get_center();
    glm::vec2 dif = a_c - p;
    this->acc += glm::normalize(dif) * bounce_impulse;
}

void Camera::pin() {
    this->pinned = true;
}

void Camera::unpin() {
    this->pinned = false;
}

void Camera::pin_center_to_position(glm::vec2 p) {
    this->pin();
    this->pin_pos = p;
}