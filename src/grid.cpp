#include <iostream>
#include <algorithm>

#include "grid.hpp"
#include "utils.hpp"

Grid::Grid(glm::vec2 pos, glm::vec2 size, float cell_size) {
    this->pos = pos;
    this->size = size;
    this->cell_size = cell_size;

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

glm::vec2 Grid::get_br() {
    return this->pos + this->size;
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

    // get tl of entity, and br
    GridCoord tl = Grid::get_cell_coords(e_cl_tl);
    GridCoord br = Grid::get_cell_coords(e_cl_br);
    // clamp coords to grid bounds
    // tl.x = std::max(float(tl.x), this->pos.x);
    // tl.y = std::max(float(tl.y), this->pos.y);
    // br.x = std::min(float(br.x), int(this->pos.x + this->size.x));
    // br.y = std::min(float(br.y), int(this->pos.y + this->size.y));

    for (int y = tl.y; y <= br.y; y += 1) {
        for (int x = tl.x; x <= br.x; x += 1) {
            this->grid[y][x].push_back(e);
        }
    }
}

GridCoord Grid::get_cell_coords(glm::vec2 p) {
    glm::vec2 s = p - this->pos;
    GridCoord c;
    // c.x = fmod(s.x, this->cell_size);
    // c.y = fmod(s.y, this->cell_size);
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

// helper function to get the tl and br of a rect given coordinates

// helper function to get the x and y coordinates of a given rectangle

// function to clear the grid


// void add_entity(Entity* entity);
// void remove_entity(Entity* entity);
// void query(glm::vec2 tl, glm::vec2 br);
// void square_query(glm::vec2 center, float width);
// void move(Entity* entity);

