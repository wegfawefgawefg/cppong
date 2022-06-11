//
// Created by Kyle Dougan on 6/10/22.
//

#pragma once

#include <map>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include "flecs/flecs.h"

class Grid
{
public:
    Grid(glm::ivec2 cellSize);

    ~Grid() = default;

    void add(flecs::entity entity, glm::ivec2 position);

    void add(flecs::entity entity, glm::ivec2 position, glm::ivec2 volume);

    void remove(flecs::entity entity);

    void clear();

    std::vector<flecs::entity> query(glm::ivec2 position);

    std::vector<flecs::entity> query(glm::ivec2 position, glm::ivec2 volume);

    std::vector<flecs::entity> query(glm::ivec2 position, glm::ivec2 volume, flecs::entity exclude);

    std::vector<flecs::entity> query(glm::ivec2 position, glm::ivec2 volume, const std::vector<flecs::entity> &exclude);

    std::vector<flecs::entity> query_for(flecs::entity entity);

    std::vector<flecs::entity> query_for(flecs::entity entity, flecs::entity exclude);

    std::vector<flecs::entity> query_for(flecs::entity entity, std::vector<flecs::entity> exclude);

private:
    glm::ivec2 cellSize;
    std::map<std::string, std::vector<flecs::entity>> m_grid;
    std::map<flecs::entity, std::vector<glm::ivec2>> m_entities;

    std::vector<glm::ivec2> get_cells(glm::ivec2 position, glm::ivec2 volume);

    static std::string get_key(glm::ivec2 vec2);
};
