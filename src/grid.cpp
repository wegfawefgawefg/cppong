#include "grid.hpp"

Grid::Grid(glm::vec2 pos, glm::vec2 size, float cell_size){
    this->pos = pos;
    this->size = size;
    this->cell_size = cell_size;

    int w = static_cast<int>(ceil(size.x / cell_size));
    int h = static_cast<int>(ceil(size.y / cell_size));

    this->width = w;
    this->height = h;
    
    std::vector<std::vector<std::vector<Entity*>>> grid;
    for(auto ih = 0; ih <= h; ih++){
        std::vector<std::vector<Entity*>> row;
        for(auto iw = 0; iw <= w; iw++){
            std::vector<Entity*> cell;
            row.push_back(cell);
        }
        grid.push_back(row);
    }
}

// helper function to get the tl and br of a rect given coordinates

// helper function to get the x and y coordinates of a given rectangle

// function to clear the grid

Grid::~Grid() {
}

// void add_entity(Entity* entity);
// void remove_entity(Entity* entity);
// void query(glm::vec2 tl, glm::vec2 br);
// void square_query(glm::vec2 center, float width);
// void move(Entity* entity);
