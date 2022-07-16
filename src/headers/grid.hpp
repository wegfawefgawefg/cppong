#pragma once

#ifndef GRIDS_H
#define GRIDS_H

#include <math.h>
#include <vector>

#include <glm/glm.hpp>

#include "entity.hpp"

class Grid {
public:
    glm::vec2 pos;
    glm::vec2 size;
    float cell_size;
    int width, height;
    std::vector<std::vector<std::vector<Entity*>>> grid;

    Grid(glm::vec2 pos, glm::vec2 size, float square_size);
    ~Grid();
    // void add_entity(Entity* entity);
    // void remove_entity(Entity* entity);
    // void query(glm::vec2 tl, glm::vec2 br);
    // void square_query(glm::vec2 center, float width);
    // void move(Entity* entity);
};

#endif