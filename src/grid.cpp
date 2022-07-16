#include <iostream>
#include <algorithm>
#include <vector>

#include "grid.hpp"
#include "utils.hpp"

Grid::Grid(glm::vec2 pos, glm::vec2 size, float cell_size) {
    this->pos = pos;
    this->size = size;
    this->cell_size = cell_size;
    this->br = pos + size;

    int w = static_cast<int>(ceil(size.x / cell_size));
    int h = static_cast<int>(ceil(size.y / cell_size));

    this->width = w;
    this->height = h;

    print_glm_vec2(pos);
    print_glm_vec2(size);
    std::cout <<
        "cell_size: " << cell_size << ", " <<
        "width: " << w << ", " <<
        "height: " << h << ", " <<
        std::endl;

    std::vector<std::vector<std::vector<Entity*>>> grid;
    for (auto ih = 0; ih <= h; ih++) {
        std::vector<std::vector<Entity*>> row;
        for (auto iw = 0; iw <= w; iw++) {
            std::vector<Entity*> cell;
            row.push_back(cell);
        }
        grid.push_back(row);
    }
    this->grid = grid;
}

Grid::~Grid() {}

inline glm::vec2 Grid::get_br() {
    // return this->pos + this->size;
    return this->br;
}

void Grid::insert_entity(Entity* e) {
    this->num_entities += 1;

    //  bounds checking
    //  //  out of bounds right or below
    glm::vec2 g_br = this->get_br();
    if (e->pos.x > g_br.x) {
        return;
    }
    if (e->pos.y > g_br.y) {
        return;
    }
    //  //  out of bounds, above or left
    glm::vec2 e_br = e->get_br();
    if (e_br.x < this->pos.x) {
        return;
    }
    if (e_br.y < this->pos.y) {
        return;
    }

    // clamp any entity out of bound corners to within grid space
    glm::vec2 e_cl_tl = glm::max(e->pos, this->pos);
    glm::vec2 e_cl_br = glm::min(e_br, g_br);

    GridCoord tl = Grid::get_cell_coords(e_cl_tl);
    GridCoord br = Grid::get_cell_coords(e_cl_br);

    for (int y = tl.y; y <= br.y; y += 1) {
        for (int x = tl.x; x <= br.x; x += 1) {
            this->grid[y][x].push_back(e);
        }
    }
}

GridCoord Grid::get_cell_coords(glm::vec2 p) {
    glm::vec2 s = p - this->pos;
    GridCoord c;
    c.x = s.x / this->cell_size;
    c.y = s.y / this->cell_size;
    return c;
}

bool Grid::has_entities(int x, int y) {
    std::vector<Entity*> cell = this->grid[y][x];
    if (cell.size() > 0) {
        return true;
    }
    else {
        return false;
    }
}

std::vector<Entity*> Grid::query(glm::vec2 qtl, glm::vec2 qbr) {
    glm::vec2 tlc = glm::max(qtl, this->pos);
    glm::vec2 brc = glm::min(qbr, this->get_br());

    GridCoord tl = Grid::get_cell_coords(tlc);
    GridCoord br = Grid::get_cell_coords(brc);

    std::vector<Entity*> hits;
    for (int y = tl.y; y <= br.y; y += 1) {
        for (int x = tl.x; x <= br.x; x += 1) {
            std::vector<Entity*> cell = this->grid[y][x];
            for (auto e : cell) {
                hits.push_back(e);
            }
        }
    }
    return hits;
}

// helper function to get the tl and br of a rect given coordinates

// helper function to get the x and y coordinates of a given rectangle

// function to clear the grid


// void add_entity(Entity* entity);
// void remove_entity(Entity* entity);
// void square_query(glm::vec2 center, float width);
// void move(Entity* entity);

