//
// Created by Kyle Dougan on 6/10/22.
//

#include "Grid.h"


Grid::Grid(glm::ivec2 cellSize)
{
    this->cellSize = cellSize;
}


std::vector<glm::ivec2> Grid::get_cells(glm::ivec2 position, glm::ivec2 volume)
{
    std::vector<glm::ivec2> cells;
    int lowerX = floor(position.x / cellSize.x);
    int lowerY = floor(position.y / cellSize.y);
    int upperX = ceil((position.x + volume.x) / cellSize.x);
    int upperY = ceil((position.y + volume.y) / cellSize.y);
    for (int x = lowerX; x < upperX; x++)
    {
        for (int y = lowerY; y < upperY; y++)
        {
            cells.emplace_back(glm::ivec2(x, y));
        }
    }
    return cells;
}


std::string Grid::get_key(glm::ivec2 vec2)
{
    return std::to_string(vec2.x) + "," + std::to_string(vec2.y);
}


void Grid::add(flecs::entity entity, glm::ivec2 position)
{
    add(entity, position, glm::ivec2(1, 1));
}


void Grid::add(flecs::entity entity, glm::ivec2 position, glm::ivec2 volume)
{
    std::vector<glm::ivec2> cells = get_cells(position, volume);
    for (glm::ivec2 cell: cells)
    {
        m_grid[get_key(cell)].emplace_back(entity);
        m_entities[entity].emplace_back(cell);
    }
}


void Grid::remove(flecs::entity entity)
{
    for (glm::ivec2 cell: m_entities[entity])
    {
        m_grid[get_key(cell)].erase(std::remove(m_grid[get_key(cell)].begin(), m_grid[get_key(cell)].end(), entity),
                                    m_grid[get_key(cell)].end());
    }
    m_entities.erase(entity);
}


void Grid::clear()
{
    m_grid.clear();
    m_entities.clear();
}


std::vector<flecs::entity> Grid::query(glm::ivec2 position)
{
    return query(position, glm::ivec2(1, 1));
}


std::vector<flecs::entity> Grid::query(glm::ivec2 position, glm::ivec2 volume)
{
    std::vector<flecs::entity> entities;
    std::vector<glm::ivec2> cells = get_cells(position, volume);
    for (glm::ivec2 cell: cells)
    {
        for (flecs::entity entity: m_grid[get_key(cell)])
        {
            entities.emplace_back(entity);
        }
    }
    return entities;
}


std::vector<flecs::entity> Grid::query(glm::ivec2 position, glm::ivec2 volume, flecs::entity exclude)
{
    std::vector<flecs::entity> entities = query(position, volume);
    entities.erase(std::remove(entities.begin(), entities.end(), exclude), entities.end());
    return entities;
}


std::vector<flecs::entity>
Grid::query(glm::ivec2 position, glm::ivec2 volume, const std::vector<flecs::entity> &exclude)
{
    std::vector<flecs::entity> entities = query(position, volume);
    for (flecs::entity entity: exclude)
    {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }
    return entities;
}


std::vector<flecs::entity> Grid::query_for(flecs::entity entity)
{
    std::vector<flecs::entity> entities;
    for (glm::ivec2 cell: m_entities[entity])
    {
        for (flecs::entity other: m_grid[get_key(cell)])
        {
            if (other != entity)
            {
                entities.emplace_back(other);
            }
        }
    }
    return entities;
}


std::vector<flecs::entity> Grid::query_for(flecs::entity entity, flecs::entity exclude)
{
    std::vector<flecs::entity> entities = query_for(entity);
    entities.erase(std::remove(entities.begin(), entities.end(), exclude), entities.end());
    return entities;
}


std::vector<flecs::entity> Grid::query_for(flecs::entity entity, std::vector<flecs::entity> exclude)
{
    std::vector<flecs::entity> entities = query_for(entity);
    for (flecs::entity other: exclude)
    {
        entities.erase(std::remove(entities.begin(), entities.end(), other), entities.end());
    }
    return entities;
}
