#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Game;
class Camera;
class Camera {
public:
    static constexpr float MAX_SPEED = 2000.0f;

    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 acc;
    glm::vec2 size;

    glm::vec2 pin_pos;
    bool pinned = false;

    Camera();
    Camera(glm::vec2 center, glm::vec2 size);
    virtual ~Camera();
    void step(Game& game);

    glm::vec2 get_br();
    glm::vec2 get_center();
    void pin();
    void unpin();
    void pin_center_to_position(glm::vec2 p);
    void set_center(glm::vec2 p);

    bool contains(glm::vec2 p);
    bool contains_box(glm::vec2 tl, glm::vec2 br);
    void bounce_away_from_position(glm::vec2 p);

};
#endif