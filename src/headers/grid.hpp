#pragma once

#ifndef GRIDS_H
#define GRIDS_H

#include <math.h>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "entity.hpp"

struct GridCoord { int x; int y; };

class Grid {
public:
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 br;
    float cell_size;
    int width, height;
    int num_entities = 0;
    std::vector<std::vector<std::vector<Entity*>>> grid;

    Grid(glm::vec2 pos, glm::vec2 size, float square_size);
    ~Grid();
    void insert_entity(Entity* entity);
    GridCoord get_cell_coords(glm::vec2 p);
    bool has_entities(int x, int y);
    glm::vec2 get_br();
    // void remove_entity(Entity* entity);
    std::vector<Entity*> query(glm::vec2 tl, glm::vec2 br);
    // void square_query(glm::vec2 center, float width);
    // void move(Entity* entity);
};
#endif